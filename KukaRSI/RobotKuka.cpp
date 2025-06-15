#include "RobotKuka.h"

#include <cstring> // pour memcpy

RobotKuka::RobotKuka(QObject* parent) :
	QObject(parent),
	m_status(Status::Ready),
	m_behaviour(Behaviour::None),
	m_isConnected(false),
	m_disconnectRequest(false),
	m_udpClient(nullptr),
	m_connectionTimeout(5),
	m_connectionTimeRemaining(5),
	m_connectionTimer(nullptr),
	m_abortConnectionRequest(false),
	m_initialDatagramReceived(false),
	m_currentPose(),
	m_currentDelta(),
	m_currentMovement(MovementFlags::fromInt(MovementDirection::None))
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
		setBehaviour(Behaviour::None);
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

	m_isConnected = true;
	setStatus(Status::Connected);
	emit connected();
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

void RobotKuka::setBehaviour(Behaviour behaviour)
{
	if (m_behaviour != behaviour)
	{
		m_behaviour = behaviour;
		emit behaviourChanged(m_behaviour);
	}
}

void RobotKuka::start()
{
	// TODO : Implémenter le démarrage
	// démarrer une tâche de surveillance de com ?
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
	m_behaviour = RobotKuka::Behaviour::StopMove;
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
