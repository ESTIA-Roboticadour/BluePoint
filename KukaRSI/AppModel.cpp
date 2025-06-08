#include "AppModel.h"

AppModel::AppModel(const RobotConfig* config, QObject* parent) :
    ModelBase(parent),
    m_robot(nullptr),
    m_config()
{
    if (m_robot)
    {
        connect(m_robot, &RobotKuka::poseUpdated, this, &AppModel::onPoseUpdated);
        connect(m_robot, &RobotKuka::errorOccurred, this, &AppModel::onErrorOccurred);
        connect(m_robot, &RobotKuka::connected, this, &AppModel::robotStateChanged);
        connect(m_robot, &RobotKuka::disconnected, this, &AppModel::robotStateChanged);
        connect(m_robot, &RobotKuka::started, this, &AppModel::robotStateChanged);
        connect(m_robot, &RobotKuka::stopped, this, &AppModel::robotStateChanged);
    }
}

AppModel::~AppModel()
{
    if (!isReleased())
    {
        release();
    }
}

void AppModel::release()
{
    if (m_robot)
    {
        disconnectFromRobot();
        ModelBase::release();
    }
}

void AppModel::onMovementPressed(MovementDirection direction)
{
}

void AppModel::onMovementReleased(MovementDirection direction)
{
}

const Config* AppModel::getConfig() const
{
    return &m_config;
}

void AppModel::connectToRobot()
{
    if (m_robot)
        m_robot->connectToRobot();
}

void AppModel::disconnectFromRobot()
{
    if (m_robot)
        m_robot->disconnectFromRobot();
}

void AppModel::startRobot()
{
    if (m_robot)
        m_robot->start();
}

void AppModel::stopRobot()
{
    if (m_robot)
        m_robot->stop();
}

void AppModel::stopMove()
{
}

void AppModel::onPoseUpdated(const QMatrix4x4& pose)
{
    emit robotPoseChanged(pose);
}

void AppModel::onErrorOccurred(const QString& message)
{
    emit errorOccurred(message);
}
