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
	m_deltaStepCartesianTranslation(0.5), // Default delta step cartesian (mm)
	m_deltaStepCartesianRotation(0.25), // Default delta step cartesian (°)
	m_deltaStepJoint(0.05), // Default delta step joint (degrees)
	m_joggingAxis(Axis::X), // Default axis
	m_joggingJoint(Joint::J1), // Default joint
	m_isMovePositive(true), // Default to positive movement
	m_isMovingInRobotBase(true), // Default to BASE mode
	m_rsiTrame(),
	m_lastIPOC()
{
	std::memcpy(m_currentPose, m_ZEROS, ARRAY_6_DOUBLE_SIZE);
	std::memcpy(m_currentJoint, m_ZEROS, ARRAY_6_DOUBLE_SIZE);
	std::memcpy(m_currentDelta, m_ZEROS, ARRAY_6_DOUBLE_SIZE);
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
	m_udpClient->close();
}

void RobotKuka::abortConnection()
{
	m_abortConnectionRequest = m_status == Status::WaitingRobotConnection;
}

void RobotKuka::closeUdpClient()
{
	if (m_udpClient && m_udpClient->isOpened()) {
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
		//qDebug() << "Robot state: " + toString(state);
		m_robotState = state;
		emit robotStateChanged(m_robotState);
	}
}

void RobotKuka::parseReceivedData(const QString& data)
{
	m_lastIPOC = ipocFromTrame(data);
	cartesianPositionFromTrame(data, m_currentPose);
	jointPositionFromTrame(data, m_currentJoint);
}

QString RobotKuka::ipocFromTrame(const QString& trame)
{
	static const QString etiquette = "<IPOC>";
	static int startIPOC;
	static int endIPOC;
	startIPOC = trame.lastIndexOf(etiquette) + etiquette.length();
	endIPOC = trame.lastIndexOf("</IPOC");
	return trame.mid(startIPOC, endIPOC - startIPOC);
}

void RobotKuka::cartesianPositionFromTrame(const QString& trame, double pos[6])
{
	static const QString tag = "<RIst";
	int start = trame.indexOf(tag);

	if (start == -1)
	{
		qWarning() << "Cartesian position not found in trame. Missing tag: RIst";
		return;
	}

	int end = trame.indexOf("/>", start);
	if (end == -1)
		return;

	QString rist = trame.mid(start, end - start); // extrait la sous-chaîne "<RIst ..."

	QMap<QString, int> indexMap = { {"X", 0}, {"Y", 1}, {"Z", 2}, {"A", 3}, {"B", 4}, {"C", 5} };

	for (auto it = indexMap.constBegin(); it != indexMap.constEnd(); ++it) {
		QString key = it.key() + "=\"";
		int idx = rist.indexOf(key);
		if (idx != -1) {
			idx += key.length();
			int endIdx = rist.indexOf("\"", idx);
			if (endIdx != -1) {
				QString valueStr = rist.mid(idx, endIdx - idx);
				pos[it.value()] = valueStr.toDouble();
			}
		}
	}
}

void RobotKuka::jointPositionFromTrame(const QString& trame, double pos[6])
{
	static const QString tag = "<AIPos";
	int start = trame.indexOf(tag);

	if (start == -1)
	{
		qWarning() << "Joint position not found in trame. Missing tag: AIPos";
		return;
	}

	int end = trame.indexOf("/>", start);
	if (end == -1)
		return;

	QString aipos = trame.mid(start, end - start); // extrait la sous-chaîne "<AIPos ..."

	QMap<QString, int> indexMap = { {"A1", 0}, {"A2", 1}, {"A3", 2}, {"A4", 3}, {"A5", 4}, {"A6", 5} };

	for (auto it = indexMap.constBegin(); it != indexMap.constEnd(); ++it) {
		QString key = it.key() + "=\"";
		int idx = aipos.indexOf(key);
		if (idx != -1) {
			idx += key.length();
			int endIdx = aipos.indexOf("\"", idx);
			if (endIdx != -1) {
				QString valueStr = aipos.mid(idx, endIdx - idx);
				pos[it.value()] = valueStr.toDouble();
			}
		}
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
		m_currentDelta[static_cast<int>(m_joggingAxis)] = (m_joggingAxis < 3 ? m_deltaStepCartesianTranslation : m_deltaStepCartesianRotation) * (m_isMovePositive ? 1. : -1.);
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
	m_rsiTrame.setIPOC(m_lastIPOC);
}

void RobotKuka::sendTrame()
{
	if (m_udpClient)
	{
		QString trame = m_rsiTrame.build();
		m_udpClient->sendData(trame, m_robotAddress, m_robotPort);
		//qDebug() << "SEND: " + trame;
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

void RobotKuka::setInput(IOInput input, bool enabled)
{
}

void RobotKuka::setOutput(IOOutput output, bool enabled)
{
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
