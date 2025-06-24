#include "RobotKuka.h"
#include <memory>

#include <cstring> // memcpy

#define ARRAY_6_DOUBLE_SIZE    6 * sizeof(double)

RobotKuka::RobotKuka(QObject* parent) :
	QObject(parent),
	m_status(Status::Ready),
	m_robotRequestState(RobotState::None),
	m_robotState(RobotState::None),
	m_isConnected(false),
	m_disconnectRequest(false),
	m_udpClient(nullptr),
	m_connectionTimeout(5),
	m_connectionTimeRemaining(5),
	m_connectionTimer(nullptr),
	m_abortConnectionRequest(false),
	m_initialDatagramReceived(false),
	m_robotAddress(),
	m_robotPort(0),
	m_watchdogTimer(nullptr),
	m_currentPose(),
	m_currentJoint(),
	m_currentDelta(),
	m_deltaStepCartesianTranslation(0.25), // Default delta step cartesian (mm)
	m_deltaStepCartesianRotation(0.25), // Default delta step cartesian (°)
	m_deltaStepJoint(0.025), // Default delta step joint (degrees)
	m_joggingAxisIndex(0),
	m_joggingAxis(Axis::X), // Default axis
	m_joggingJoint(Joint::J1), // Default joint
	m_isMovePositive(true), // Default to positive movement
	m_isMovingInRobotBase(true), // Default to BASE mode
	m_digin(), // Digital inputs
	m_digout(), // Digital outputs
	m_requestDigout(),
	m_startIndex(0),
	m_endIndex(0),
	m_iTrame(0),
	m_ioTrame(0),
	m_ioMask(0),
	m_rsiTrame(),
	m_trameTagContent(),
	m_trameTagKey(),
	m_lastIPOC()
{
	for (int i = 0; i < 16; ++i) {
		m_digin[i] = false;
		m_digout[i] = false;
		m_requestDigout[i] = false;
	}
	std::memcpy(m_currentPose, m_ZEROS, ARRAY_6_DOUBLE_SIZE);
	std::memcpy(m_currentJoint, m_ZEROS, ARRAY_6_DOUBLE_SIZE);
	std::memcpy(m_currentDelta, m_ZEROS, ARRAY_6_DOUBLE_SIZE);

	m_trameTagContent.reserve(1024); // Reserve space for the trame content
	m_trameTagKey.reserve(16); // Reserve space for the tag key
}

RobotKuka::~RobotKuka()
{
	if (m_isConnected)
	{
		disconnectFromRobot(); // envoyer une trame de stop directement ? et fermer la thread + le client
	}
}

void RobotKuka::setRobotBase(bool isInRobotBase)
{
	m_isMovingInRobotBase = isInRobotBase;
}

void RobotKuka::connectToRobot(const QHostAddress& hostAddress, quint16 port, quint32 timeout)
{
	if (!m_udpClient)
	{
		m_isConnected = false;
		m_disconnectRequest = false;
		m_abortConnectionRequest = false;
		m_initialDatagramReceived = false;
		setRobotState(RobotState::None);
		m_udpClient = new UdpClient(hostAddress, port, this);
		connect(m_udpClient, &UdpClient::opened, this, &RobotKuka::onUdpOpened);
		connect(m_udpClient, &UdpClient::failedToOpen, this, &RobotKuka::onUdpFailedToOpen);
		connect(m_udpClient, &UdpClient::closed, this, &RobotKuka::onUdpClosed);
		m_connectionTimeout = timeout;
		m_udpClient->open();
	}
}

void RobotKuka::disconnectFromRobot()
{
	if (!m_isConnected)
		return;
	if (m_watchdogTimer)
		m_watchdogTimer->stop();

	setRequestState(RobotState::None);

	closeUdpClient();
}

void RobotKuka::onUdpOpened(const QHostAddress& hostAddress, quint16 port)
{
	qInfo() << QString("UDP client opened at %1:%2").arg(hostAddress.toString()).arg(port);
	disconnect(m_udpClient, &UdpClient::opened, this, &RobotKuka::onUdpOpened);
	setStatus(Status::WaitingRobotConnection);

	// Connexion à la réception du datagramme
	connect(m_udpClient, &UdpClient::datagramReceived, this, &RobotKuka::onInitialDatagramReceived);

	// Timer de compte à rebours
	if (!m_connectionTimer)
	{
		m_connectionTimer = new QTimer(this);
		m_connectionTimer->setInterval(1000); // 1 seconde
		m_connectionTimer->setTimerType(Qt::PreciseTimer);
		connect(m_connectionTimer, &QTimer::timeout, this, &RobotKuka::onConnectionTimeoutTick);
	}

	m_connectionTimeRemaining = m_connectionTimeout;
	m_connectionTimer->start();
}

void RobotKuka::onUdpFailedToOpen(const QHostAddress& hostAddress, quint16 port)
{
	QString errorMessage = QString("Failed to connect UDP to %1:%2").arg(hostAddress.toString()).arg(port);
	m_udpClient->close();
	setStatus(Status::Error);
	emit errorOccurred(errorMessage);
}

void RobotKuka::onUdpClosed()
{
	delete m_udpClient;
	m_udpClient = nullptr;
	m_isConnected = false;
	setStatus(Status::Ready);
	emit disconnected();
}

void RobotKuka::onInitialDatagramReceived(const QByteArray& data, const QHostAddress& sender, quint16 senderPort)
{
	if (m_initialDatagramReceived)
		return;

	m_initialDatagramReceived = true;
	m_connectionTimer->stop();
	m_connectionTimer->deleteLater();
	m_connectionTimer = nullptr;

	disconnect(m_udpClient, &UdpClient::datagramReceived, this, &RobotKuka::onInitialDatagramReceived);

	// Démarre le watchdog
	if (!m_watchdogTimer)
	{
		m_watchdogTimer = new QTimer(this);
		m_watchdogTimer->setInterval(WATCHDOG_TIMEOUT_MS);
		m_watchdogTimer->setTimerType(Qt::PreciseTimer);
		m_watchdogTimer->setSingleShot(true);
		connect(m_watchdogTimer, &QTimer::timeout, this, &RobotKuka::onWatchdogTimeout, Qt::DirectConnection);
	}

	m_robotAddress = QHostAddress(sender); // make sure it's a copy
	m_robotPort = senderPort;
	parseReceivedData(data);
	std::memcpy(m_requestDigout, m_digout, 16 * sizeof(bool));
	m_isConnected = true;
	qInfo() << QString("Connection established from %1:%2").arg(m_robotAddress.toString()).arg(m_robotPort);
	setStatus(Status::Connected);
	connect(m_udpClient, &UdpClient::datagramReceived, this, &RobotKuka::onDatagramReceived, Qt::DirectConnection);
	emit connected();

	m_watchdogTimer->start();
}

void RobotKuka::onConnectionTimeoutTick()
{
	emit connectionTimeRemainingChanged(--m_connectionTimeRemaining);
	if (m_abortConnectionRequest || m_connectionTimeRemaining <= 0)
	{
		m_connectionTimer->stop();
		m_connectionTimer->deleteLater();
		m_connectionTimer = nullptr;

		disconnect(m_udpClient, &UdpClient::datagramReceived, this, &RobotKuka::onInitialDatagramReceived);
		setStatus(m_abortConnectionRequest ? Status::Ready : Status::Error);
		m_udpClient->close();
		if (!m_abortConnectionRequest)
			emit errorOccurred("Connection timeout");
		failedToConnect();
	}
}

void RobotKuka::onDatagramReceived(const QByteArray& data, const QHostAddress& sender, quint16 senderPort)
{
	if (!m_isConnected)
		return;

	m_rsiTrame.reset();
	resetCurrentDelta();
	m_watchdogTimer->start(); // Reset watchdog

	// 1. Parse la trame reçue
	parseReceivedData(data);

	// 2. Met à jour les requêtes (RequestAutomate)
	requestAutomate();

	// 3. Applique la logique d’état (StateAutomate)
	stateAutomate();

	// 4. Envoie de la trame
	sendTrame();
}

void RobotKuka::onWatchdogTimeout()
{
	setStatus(Status::Error);
	emit errorOccurred(QString("Communication lost with robot (%1:%2)").arg(m_robotAddress.toString()).arg(m_robotPort));
	setRequestState(RobotState::None);
	closeUdpClient();
}

void RobotKuka::abortConnection()
{
	m_abortConnectionRequest = m_status == Status::WaitingRobotConnection;
}

void RobotKuka::closeUdpClient()
{
	if (m_udpClient)
	{
		disconnect(m_udpClient, &UdpClient::datagramReceived, this, &RobotKuka::onDatagramReceived);
		if (m_udpClient->isOpened())
			m_udpClient->close();
	}
}

void RobotKuka::setStatus(Status status)
{
	if (m_status != status) {
		m_status = status;
		emit statusChanged(m_status);
	}
}

void RobotKuka::setRobotState(RobotState state)
{
	if (m_robotState != state)
	{
		m_robotState = state;
		emit robotStateChanged(m_robotState);
	}
}

void RobotKuka::parseReceivedData(const QString& data)
{
	ipocFromTrame(data, m_lastIPOC);
	cartesianPositionFromTrame(data, m_currentPose);
	jointPositionFromTrame(data, m_currentJoint);
	getDigitalInputsFromTrame(data, m_digin);
	getDigitalOutputsFromTrame(data, m_digout);
}

void RobotKuka::ipocFromTrame(const QString& trame, QString& ipoc)
{
	static const QString tag = "<IPOC>";
	m_startIndex = trame.lastIndexOf(tag);
	if (m_startIndex == -1)
	{
		qWarning() << "IPOC not found in trame. Missing tag: IPOC";
		return;
	}
	m_endIndex = trame.lastIndexOf("</IPOC>");
	if (m_endIndex == -1)
	{
		qWarning() << "Malformed <IPOC> tag: missing '</IPOC>'";
		return;
	}
	m_startIndex += tag.length();
	ipoc = trame.mid(m_startIndex, m_endIndex - m_startIndex);
}

void RobotKuka::cartesianPositionFromTrame(const QString& trame, double pos[6])
{
	static const QString tag = "<RIst";
	const static QMap<QString, int> indexMap = { {"X", 0}, {"Y", 1}, {"Z", 2}, {"A", 3}, {"B", 4}, {"C", 5} };
	m_startIndex = trame.indexOf(tag);
	if (m_startIndex == -1)
	{
		qWarning() << "Cartesian position not found in trame. Missing tag: RIst";
		return;
	}
	m_endIndex = trame.indexOf("/>", m_startIndex);
	if (m_endIndex == -1)
	{
		qWarning() << "Malformed <RIst> tag: missing '/>'";
		return;
	}

	m_trameTagContent = trame.mid(m_startIndex, m_endIndex - m_startIndex); // extrait la sous-chaîne "<RIst ..."

	for (auto it = indexMap.constBegin(); it != indexMap.constEnd(); ++it) {
		m_trameTagKey = it.key() + "=\"";
		m_startIndex = m_trameTagContent.indexOf(m_trameTagKey);
		if (m_startIndex != -1) {
			m_startIndex += m_trameTagKey.length();
			m_endIndex = m_trameTagContent.indexOf("\"", m_startIndex);
			if (m_endIndex != -1) {
				pos[it.value()] = m_trameTagContent.mid(m_startIndex, m_endIndex - m_startIndex).toDouble();
			}
		}
	}
}

void RobotKuka::jointPositionFromTrame(const QString& trame, double pos[6])
{
	static const QString tag = "<AIPos";
	m_startIndex = trame.indexOf(tag);
	if (m_startIndex == -1)
	{
		qWarning() << "Joint position not found in trame. Missing tag: AIPos";
		return;
	}
	m_endIndex = trame.indexOf("/>", m_startIndex);
	if (m_endIndex == -1)
	{
		qWarning() << "Malformed <AIPos> tag: missing '/>'";
		return;
	}

	m_trameTagContent = trame.mid(m_startIndex, m_endIndex - m_startIndex); // extrait la sous-chaîne "<AIPos ..."

	for (m_iTrame = 0; m_iTrame < 6; ++m_iTrame)
	{
		m_trameTagKey = QString("A%1=\"").arg(m_iTrame + 1);
		m_startIndex = m_trameTagKey.indexOf(m_trameTagKey);
		if (m_startIndex != -1)
		{
			m_startIndex += m_trameTagKey.length();
			m_endIndex = m_trameTagKey.indexOf('\"', m_startIndex);
			if (m_endIndex != -1)
				pos[m_iTrame] = m_trameTagKey.mid(m_startIndex, m_endIndex - m_startIndex).toDouble();
		}
	}
}

void RobotKuka::getDigitalInputsFromTrame(const QString& trame, bool digin[16])
{
	static const QString tag = "<Digin>";
	m_startIndex = trame.lastIndexOf(tag);
	if (m_startIndex == -1)
	{
		qWarning() << "Digital inputs not found in trame. Missing tag: Digin";
		return;
	}
	m_endIndex = trame.lastIndexOf("</Digin>");
	if (m_endIndex == -1)
	{
		qWarning() << "Malformed <Digin> tag: missing '</Digin>'";
		return;
	}
	m_startIndex += tag.length();
	m_ioTrame = trame.mid(m_startIndex, m_endIndex - m_startIndex).toShort();

	m_ioMask = 0x0001; //  0000 0000 0000 0001 
	for (m_iTrame = 0; m_iTrame < 16; m_iTrame++)
	{
		digin[m_iTrame++] = (bool)(m_ioTrame & m_ioMask);
		m_ioMask = (ushort)(m_ioMask << 1);
	}
}

void RobotKuka::getDigitalOutputsFromTrame(const QString& trame, bool digout[16])
{
	static const QString tag = "<Digout>";
	m_startIndex = trame.lastIndexOf(tag);
	if (m_startIndex == -1)
	{
		qWarning() << "Digital inputs not found in trame. Missing tag: Digout";
		return;
	}
	m_endIndex = trame.lastIndexOf("</Digout>");
	if (m_endIndex == -1)
	{
		qWarning() << "Malformed <Digout> tag: missing '</Digout>'";
		return;
	}
	m_startIndex += tag.length();
	m_ioTrame = trame.mid(m_startIndex, m_endIndex - m_startIndex).toUShort(); // extrait la sous-chaîne "<Digout ..."

	m_ioMask = 0x0001;
	for (m_iTrame = 0; m_iTrame < 16; m_iTrame++)
	{
		digout[m_iTrame] = (bool)(m_ioTrame & m_ioMask);
		m_ioMask = (ushort)(m_ioMask << 1);
	}
}

void RobotKuka::requestAutomate()
{
	if (m_robotRequestState != m_robotState)
	{
		switch (m_robotRequestState)
		{
		case RobotState::None:
			setRobotState(m_robotRequestState);
			break;
		case RobotState::MoveCartesianLIN:
			setRobotState(m_robotRequestState);
			break;
		case RobotState::MoveJoint:
			setRobotState(m_robotRequestState);
			break;
		case RobotState::StopMove:
			setRobotState(m_robotRequestState);
			break;
		case RobotState::DoNothing:
		default:
			setRobotState(RobotState::DoNothing);
			break;
		}
	}
}

void RobotKuka::stateAutomate()
{
	switch (m_robotState)
	{
	case RobotState::None:
		m_robotRequestState = RobotState::DoNothing;
		break;

	case RobotState::DoNothing:
		break;

	case RobotState::MoveCartesianLIN:
		m_joggingAxisIndex = static_cast<int>(m_joggingAxis);
		m_currentDelta[m_joggingAxisIndex] = (m_joggingAxisIndex < 3 ? m_deltaStepCartesianTranslation : m_deltaStepCartesianRotation) * (m_isMovePositive ? 1. : -1.);
		break;

	case RobotState::MoveJoint:
		m_currentDelta[static_cast<int>(m_joggingJoint)] = m_isMovePositive ? m_deltaStepJoint : -m_deltaStepJoint;
		break;

	case RobotState::StopMove:
		m_robotRequestState = RobotState::DoNothing;
		break;

	default:
		break;
	}

	m_rsiTrame.setPose(
		m_robotState == RobotState::MoveCartesianLIN,
		m_currentDelta,
		m_isMovingInRobotBase);
	m_rsiTrame.setOutputs(m_requestDigout);
	m_rsiTrame.setIPOC(m_lastIPOC);
}

void RobotKuka::sendTrame()
{
	if (m_udpClient)
	{
		QString trame = m_rsiTrame.build();
		m_udpClient->sendData(trame, m_robotAddress, m_robotPort);
	}
}

void RobotKuka::start()
{
	if (m_status == Status::Connected)
	{
		setStatus(Status::ReadyToMove);
		m_robotRequestState = RobotState::DoNothing; // Reset request state
		emit started();
	}
}

void RobotKuka::stop()
{
	if (m_status == Status::ReadyToMove)
	{
		setStatus(Status::Connected);
		m_robotRequestState = RobotState::DoNothing;
		stopped();
	}
}

void RobotKuka::moveAxis(Axis axis, bool positive)
{
	if (isReadyToMove())
	{
		m_joggingAxis = axis;
		m_isMovePositive = positive;
		m_robotRequestState = RobotState::MoveCartesianLIN; // at the end
	}
}

void RobotKuka::moveJoint(Joint joint, bool positive)
{
	if (isReadyToMove())
	{
		m_joggingJoint = joint;
		m_isMovePositive = positive;
		m_robotRequestState = RobotState::MoveJoint; // at the end
	}
}

void RobotKuka::stopMove()
{
	m_robotRequestState = RobotState::StopMove;
}

void RobotKuka::setOutput(IOOutput output, bool enabled)
{
	m_requestDigout[output] = enabled;
}

void RobotKuka::getCurrentIO(bool inputs[16], bool outputs[16])
{
	std::memcpy(inputs, m_digin, 16 * sizeof(bool));
	std::memcpy(outputs, m_digout, 16 * sizeof(bool));
}

void RobotKuka::getCurrentPose(double currentPose[6]) const
{
	std::memcpy(currentPose, m_currentPose, ARRAY_6_DOUBLE_SIZE);
}

void RobotKuka::getCurrentJoint(double currentJoint[6]) const
{
	std::memcpy(currentJoint, m_currentJoint, ARRAY_6_DOUBLE_SIZE);
}

void RobotKuka::getCurrentDelta(double currentDelta[6]) const
{
	std::memcpy(currentDelta, m_currentDelta, ARRAY_6_DOUBLE_SIZE);
}

void RobotKuka::resetCurrentDelta()
{
	std::memcpy(m_currentDelta, m_ZEROS, ARRAY_6_DOUBLE_SIZE);
}

void RobotKuka::setCartesianTranslationStep(double step)
{
	if (step < 0.001)
		step = 0.001;
	else if (step > 0.5)
		step = 0.5;

	m_deltaStepCartesianTranslation = step;
}

void RobotKuka::setCartesianRotationStep(double step)
{
	if (step < 0.001)
		step = 0.001;
	else if (step > 0.25)
		step = 0.25;

	m_deltaStepCartesianRotation = step;
}

void RobotKuka::setJointStep(double step)
{
	if (step < 0.001)
		step = 0.001;
	else if (step > 0.05)
		step = 0.05;

	m_deltaStepJoint = step;
}
