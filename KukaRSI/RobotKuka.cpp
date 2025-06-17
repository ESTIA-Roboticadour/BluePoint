#include "RobotKuka.h"
#include <memory>

#include <cstring> // pour memcpy

RobotKuka::RobotKuka(QObject* parent) :
	QObject(parent),
	m_status(Status::None),
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
	m_trameStack()
{
	std::memcpy(m_currentPose, m_ZEROS, sizeof(m_ZEROS));
	std::memcpy(m_currentDelta, m_ZEROS, sizeof(m_ZEROS));
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
	disconnect(m_udpClient, &UdpClient::opened, this, &RobotKuka::onUdpOpened);
	setStatus(Status::WaitingRobotConnection);

	// Connexion à la réception du datagramme
	connect(m_udpClient, &UdpClient::datagramReceived, this, &RobotKuka::onInitialDatagramReceived);

	// Timer de compte à rebours
	if (!m_connectionTimer)
	{
		m_connectionTimer = new QTimer(this);
		m_connectionTimer->setInterval(1000); // 1 seconde
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
		m_watchdogTimer->setSingleShot(true);
		connect(m_watchdogTimer, &QTimer::timeout, this, &RobotKuka::onWatchdogTimeout);
	}

	m_isConnected = true;
	setStatus(Status::Connected);
	connect(m_udpClient, &UdpClient::datagramReceived, this, &RobotKuka::onDatagramReceived);
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
	emit errorOccurred(QString("Communication lost with robot (%1:%2").arg(m_robotAddress.toString()).arg(m_robotPort));
	setRequestState(RobotState::None);
	m_udpClient->close();
}

bool RobotKuka::isConnected() const
{
	return m_isConnected;
}

void RobotKuka::abortConnection()
{
	m_abortConnectionRequest = m_status == RobotKuka::Status::WaitingRobotConnection;
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
		m_robotState = state;
		emit robotStateChanged(m_robotState);
	}
}

void RobotKuka::parseReceivedData(const QString& data)
{
	// to implement
}

void RobotKuka::requestAutomate()
{
	if (m_robotRequestState != m_robotState)
	{
		switch (m_robotRequestState)
		{
		case RobotKuka::RobotState::None:
			m_robotState = m_robotRequestState;
			break;
		case RobotKuka::RobotState::MoveCartesian:
			m_robotState = m_robotRequestState;
			break;
		case RobotKuka::RobotState::MoveJoint:
			m_robotState = m_robotRequestState;
			break;
		case RobotKuka::RobotState::StopMove:
			m_robotState = m_robotRequestState;
			break;
		case RobotKuka::RobotState::DoNothing:
		default:
			m_robotState = RobotState::DoNothing;
			break;
		}

		m_currentMovement = MovementFlags::fromInt(MovementDirection::None);
	}
}

void RobotKuka::stateAutomate()
{
	switch (m_robotState)
	{
	case RobotKuka::RobotState::None:
		m_robotRequestState = RobotState::DoNothing;
		m_currentMovement = MovementFlags::fromInt(MovementDirection::None);
		break;
	case RobotKuka::RobotState::DoNothing:
		m_currentMovement = MovementFlags::fromInt(MovementDirection::None);
		break;
	case RobotKuka::RobotState::MoveCartesian:
		break;
	case RobotKuka::RobotState::MoveJoint:
		break;
	case RobotKuka::RobotState::StopMove:
		m_currentMovement = MovementFlags::fromInt(MovementDirection::None);
		break;
	default:
		break;
	}
}

void RobotKuka::sendTrame()
{
	if (m_udpClient)
		m_udpClient->sendData(m_trameStack.buildTrame(), m_robotAddress, m_robotPort);
}

void RobotKuka::start()
{
	if (true || m_isConnected)
		setStatus(RobotKuka::Status::ReadyToMove);
}

void RobotKuka::stop()
{
	// TODO : Implémenter l'arrêt
	// stoper la tâche de surveillance de com ?
	setStatus(RobotKuka::Status::Connected);
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
	m_currentMovement = MovementDirection::None;
	//qDebug() << "Movement:" << m_currentMovement.toInt() << " " + QString("%1").arg(m_currentMovement.toInt(), 8, 2, QChar('0'));
	//std::memcpy(m_currentDelta, m_ZEROS, sizeof(m_ZEROS));
	m_robotState = RobotKuka::RobotState::StopMove;
}

void RobotKuka::setInput(IOInput input, bool enabled)
{
}

void RobotKuka::setOutput(IOOutput output, bool enabled)
{
}

void RobotKuka::getCurrentPose(double currentPose[6]) const
{
	std::memcpy(currentPose, m_currentPose, sizeof(m_currentPose));
}

void RobotKuka::getCurrentDelta(double currentDelta[6]) const
{
	std::memcpy(currentDelta, m_currentDelta, sizeof(m_currentDelta));
}
