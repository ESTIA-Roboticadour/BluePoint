#include "RobotKuka.h"

RobotKuka::RobotKuka(QObject* parent)
    : QObject(parent),
    m_connected(false),
    m_running(false),
    m_pose()
{
}

RobotKuka::~RobotKuka()
{
}

void RobotKuka::connectToRobot(const RobotConfig& config)
{
    // TODO : Implémenter la connexion
}

void RobotKuka::disconnectFromRobot()
{
    // TODO : Implémenter la déconnexion
}

bool RobotKuka::isConnected() const
{
    return m_connected;
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
    return m_running;
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

QMatrix4x4 RobotKuka::getCurrentPose() const
{
    return m_pose;
}

QVector3D RobotKuka::getCurrentPosition() const
{
    return m_pose.column(3).toVector3D();
}

QVector3D RobotKuka::getCurrentOrientationEuler() const
{
    // TODO : Convertir m_pose en angles d'Euler
    return QVector3D(); // temporaire
}
