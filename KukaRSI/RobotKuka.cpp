#include "RobotKuka.h"

RobotKuka::RobotKuka(QObject* parent) :
	QObject(parent),
	m_status(RobotKuka::Status::Ready),
	m_isConnected(false),
	m_isRunning(false),
	m_pose(),
	m_hostAddress(),
	m_port(0),
	m_udpClient(nullptr),
	m_currentPose(),
	m_currentDelta()
{
	for (int i = 0; i < 6; ++i) {
		m_currentPose[i] = 0.0; // Initialisation des positions X, Y, Z, A, B, C
		m_currentDelta[i] = 0.0;   // Initialisation des deltas dX, dY, dZ, dA, dB, dC
	}
}

RobotKuka::~RobotKuka()
{
	if (m_isConnected)
		disconnect();
}

void RobotKuka::connectToRobot(const QHostAddress& hostAddress, int port, int timeout)
{
	if (!m_isConnected)
	{
		m_hostAddress = hostAddress;
		m_port = port;

		m_udpClient = new QUdpSocket(this);
		if (m_udpClient->bind(m_hostAddress, m_port)) {
			m_isConnected = true;
			setStatus(Status::WaitingRobotConnection);
		}
		else 
		{
			m_status = Status::Error;
			emit errorOccurred(QString("Failed to bind to %1:%2").arg(m_hostAddress.toString()).arg(m_port));
		}
	}
	// TODO : Implémenter la connexion
}

void RobotKuka::disconnectFromRobot()
{
	if (!m_isConnected)
		return;

	for (int i = 0; i < 6; ++i) {
		m_currentDelta[i] = 0.0;
	}
	// send 0
	m_udpClient->close();
	deleteUdpClient();
}

bool RobotKuka::isConnected() const
{
	return m_isConnected;
}

void RobotKuka::start()
{
	// TODO : Implémenter le démarrage
}

void RobotKuka::stop()
{
	// TODO : Implémenter l'arrêt
}

bool RobotKuka::isRunning() const
{
	return m_isRunning;
}

void RobotKuka::move(const QString& direction)
{
	// TODO : Implémenter le mouvement dans la direction spécifiée
	Q_UNUSED(direction);
}

void RobotKuka::stopMovement()
{
	// TODO : Implémenter l'arrêt du mouvement
}

void RobotKuka::getCurrentPose(double currentPose[6]) const
{
	for (int i = 0; i < 6; i++)
		currentPose[i] = m_currentPose[i];
}

void RobotKuka::getCurrentDelta(double currentDelta[6]) const
{
	for (int i = 0; i < 6; i++)
		currentDelta[i] = m_currentDelta[i];
}

void RobotKuka::deleteUdpClient()
{
	if (m_udpClient) {
		m_udpClient->close();
		delete m_udpClient;
		m_udpClient = nullptr;
	}
}

void RobotKuka::setStatus(Status status)
{
	if (m_status != status) {
		m_status = status;
		emit statusChanged(m_status);
	}
}
