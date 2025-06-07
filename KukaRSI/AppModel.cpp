#include "AppModel.h"

AppModel::AppModel(RobotKuka* robot, const RobotConfig& config, QObject* parent)
    : ModelBase(parent),
    m_robot(robot),
    m_config(config)
{
    connect(m_robot, &RobotKuka::poseUpdated, this, &AppModel::onPoseUpdated);
    connect(m_robot, &RobotKuka::errorOccurred, this, &AppModel::onErrorOccurred);
    connect(m_robot, &RobotKuka::connected, this, &AppModel::robotStateChanged);
    connect(m_robot, &RobotKuka::disconnected, this, &AppModel::robotStateChanged);
    connect(m_robot, &RobotKuka::started, this, &AppModel::robotStateChanged);
    connect(m_robot, &RobotKuka::stopped, this, &AppModel::robotStateChanged);
}

AppModel::~AppModel()
{
}

RobotKuka* AppModel::robot() const
{
    return m_robot;
}

const RobotConfig& AppModel::config() const
{
    return m_config;
}

void AppModel::connectToRobot()
{
    if (m_robot)
        m_robot->connectToRobot(m_config);
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

void AppModel::release()
{
    //stopRobot();
    //disconnectFromRobot();
}

void AppModel::onPoseUpdated(const QMatrix4x4& pose)
{
    emit robotPoseChanged(pose);
}

void AppModel::onErrorOccurred(const QString& message)
{
    emit errorOccurred(message);
}
