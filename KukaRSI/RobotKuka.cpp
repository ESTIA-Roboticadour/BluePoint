#include "RobotKuka.h"
#include <memory>

#include <cstring> // memcpy

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
	m_currentDelta(),
	m_currentMovement(MovementFlags::fromInt(MovementDirection::None)),
	m_deltaStep(0.5), // Default delta step
	m_rsiTrame(),
	m_lastIPOC(),
	m_startInCartesian(true) // Default to Cartesian mode
{
	std::memcpy(m_currentPose, m_ZEROS, 6 * sizeof(double));
	std::memcpy(m_currentDelta, m_ZEROS, 6 * sizeof(double));
}

RobotKuka::~RobotKuka()
{
	if (m_isConnected) 
	{
		disconnectFromRobot(); // envoyer une trame de stop directement ? et fermer la thread + le client
	}
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

	stopMovement();
	m_disconnectRequest = true;
	//closeUdpClient();
}

void RobotKuka::onUdpOpened(const QHostAddress& hostAddress, quint16 port)
{
	qInfo() << "UDP client opened at" << hostAddress.toString() << ":" << port;
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

bool RobotKuka::isConnected() const
{
	return m_isConnected;
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
	//qDebug() << "RECV: " + data;

	m_lastIPOC = ipocFromTrame(data);
	positionFromTrame(data, m_currentPose);

	// to implement
	//m_currentPose[0] += 0.1;
	//m_currentPose[1] += 0.1;
	//m_currentPose[2] += 0.1;
	//m_currentPose[3] += 0.1;
	//m_currentPose[4] += 0.1;
	//m_currentPose[5] += 0.1;
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

void RobotKuka::positionFromTrame(const QString& trame, double pos[6])
{
	static const QString tag = "<RIst";
	int start = trame.indexOf(tag);

	if (start == -1)
		return;

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

		m_currentMovement = MovementFlags::fromInt(MovementDirection::None);
	}
}

void RobotKuka::stateAutomate()
{
	switch (m_robotState)
	{
	case RobotState::None:
		m_robotRequestState = RobotState::DoNothing;
		m_currentMovement = MovementFlags::fromInt(MovementDirection::None);
		break;
	case RobotState::DoNothing:
		m_currentMovement = MovementFlags::fromInt(MovementDirection::None);
		break;
	case RobotState::MoveCartesianLIN:
		// Base
		if (m_currentMovement & MovementDirection::Forward) // X+
			m_currentDelta[0] += m_deltaStep;
		if (m_currentMovement & MovementDirection::Backward) // X-
			m_currentDelta[0] -= m_deltaStep;

		if (m_currentMovement & MovementDirection::Left) // Y+
			m_currentDelta[1] += m_deltaStep;
		if (m_currentMovement & MovementDirection::Right) // Y-
			m_currentDelta[1] -= m_deltaStep;
		
		if (m_currentMovement & MovementDirection::Up) // Z+
			m_currentDelta[2] += m_deltaStep;
		if (m_currentMovement & MovementDirection::Down) // Z-
			m_currentDelta[2] -= m_deltaStep;

		// Tool
		//if (m_currentMovement & MovementDirection::Left) // X+
		//	m_currentDelta[0] += m_deltaStep;
		//if (m_currentMovement & MovementDirection::Right) // X-
		//	m_currentDelta[0] -= m_deltaStep;
		//if (m_currentMovement & MovementDirection::Up) // Y+
		//	m_currentDelta[1] += m_deltaStep;
		//if (m_currentMovement & MovementDirection::Down) // Y-
		//	m_currentDelta[1] -= m_deltaStep;
		//if (m_currentMovement & MovementDirection::Forward) // Z+
		//	m_currentDelta[2] += m_deltaStep;
		//if (m_currentMovement & MovementDirection::Backward) // Z-
		//	m_currentDelta[2] -= m_deltaStep;
		break;
	case RobotState::MoveJoint:
		break;
	case RobotState::StopMove:
		m_currentMovement = MovementFlags::fromInt(MovementDirection::None);
		break;
	default:
		break;
	}

	m_rsiTrame.setPose(m_robotState == RobotState::MoveCartesianLIN, m_currentDelta);
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
		m_robotRequestState = m_startInCartesian ? RobotState::MoveCartesianLIN : RobotState::MoveJoint;
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

void RobotKuka::addMovement(MovementDirection direction)
{
	m_currentMovement |= direction;
	//qDebug() << "Movement:" << m_currentMovement.toInt() << " " + QString("%1").arg(m_currentMovement.toInt(), 8, 2, QChar('0'));
}

void RobotKuka::removeMovement(MovementDirection direction)
{
	m_currentMovement &= ~direction;
	//qDebug() << "Movement:" << m_currentMovement.toInt() << " " + QString("%1").arg(m_currentMovement.toInt(), 8, 2, QChar('0'));
}

void RobotKuka::moveJoint(Joint joint, bool positive)
{
}

void RobotKuka::stopMovement()
{
	m_robotRequestState = RobotState::StopMove;
	m_currentMovement = MovementDirection::None;
	//qDebug() << "Movement:" << m_currentMovement.toInt() << " " + QString("%1").arg(m_currentMovement.toInt(), 8, 2, QChar('0'));
	//std::memcpy(m_currentDelta, m_ZEROS, 6 * sizeof(double));
}

void RobotKuka::setJoggingMode(bool isCartesian)
{
	if (m_status == Status::ReadyToMove)
	{
		m_robotRequestState = isCartesian ? RobotState::MoveCartesianLIN : RobotState::MoveJoint;
	}
	else
	{
		m_startInCartesian = isCartesian;
	}
}

void RobotKuka::setInput(IOInput input, bool enabled)
{
}

void RobotKuka::setOutput(IOOutput output, bool enabled)
{
}

void RobotKuka::getCurrentPose(double currentPose[6]) const
{
	std::memcpy(currentPose, m_currentPose, 6 * sizeof(double));
}

void RobotKuka::getCurrentDelta(double currentDelta[6]) const
{
	std::memcpy(currentDelta, m_currentDelta, 6 * sizeof(double));
}

void RobotKuka::resetCurrentDelta()
{
	std::memcpy(m_currentDelta, m_ZEROS, 6 * sizeof(double));
}
