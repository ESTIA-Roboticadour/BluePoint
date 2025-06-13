#include "AppModel.h"

AppModel::AppModel(const RobotConfig* config, QObject* parent) :
	ModelBase(parent),
	m_robot(nullptr),
	m_config(Config(this)),
	m_hostAddress(),
	m_robotGroup(GroupParameter("Robot", this)),
	m_addressParameter(StringParameter("Address", "", StringParameter::Kind::Plain, this)),
	m_portParameter(NumericalParameter("Port", 0, this)),
	m_speedParameter(NumericalParameter("Max. Speed. (%)", 10, this)),
	m_accelParameter(NumericalParameter("Max. Accel. (%)", 50, this)),
	m_toolParameter(EulerFrameParameter("Tool", EulerFrameParameter::XYZ, this)),
	m_connectionGroup(GroupParameter("Connection", this)),
	m_connectionTimeoutParameter(NumericalParameter("Connection Timeout (s)", 60, this)),
	m_uiGroup(GroupParameter("UI", this)),
	m_freshRateParameter(NumericalParameter("Fresh Rate (Hz)", 20, this))
{
	setupConfig(config);
	if (config && setupAddress(config))
	{
		m_robot = new RobotKuka(this);

		connect(m_robot, &RobotKuka::errorOccurred, this, &AppModel::onErrorOccurred);
		connect(m_robot, &RobotKuka::statusChanged, this, &AppModel::robotStateChanged);
		connect(m_robot, &RobotKuka::connected, this, &AppModel::onRobotConnected);
		connect(m_robot, &RobotKuka::disconnected, this, &AppModel::onRobotDisconnected);
		connect(m_robot, &RobotKuka::started, this, &AppModel::robotStarted);
		connect(m_robot, &RobotKuka::stopped, this, &AppModel::robotStopped);

		connect(m_robot, &RobotKuka::connectionTimeRemainingChanged, this, &AppModel::connectionTimeRemainingChanged);
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

void AppModel::getCurrentPose(double currentPose[6]) const
{
	m_robot->getCurrentPose(currentPose);
}

void AppModel::getCurrentDelta(double currentDelta[6]) const
{
	m_robot->getCurrentDelta(currentDelta);
}

void AppModel::setupConfig(const RobotConfig* config)
{
	m_portParameter.setMaximum(65535);
	m_freshRateParameter.setMinimum(1);
	m_freshRateParameter.setMaximum(60);
	m_connectionTimeoutParameter.setMaximum(300);

	m_robotGroup.addParameter(&m_addressParameter);
	m_robotGroup.addParameter(&m_portParameter);
	m_robotGroup.addParameter(&m_speedParameter);
	m_robotGroup.addParameter(&m_accelParameter);
	m_robotGroup.addParameter(&m_toolParameter);

	m_connectionGroup.addParameter(&m_connectionTimeoutParameter);

	m_uiGroup.addParameter(&m_freshRateParameter);

	m_config.addParameter(&m_robotGroup);
	m_config.addParameter(&m_connectionGroup);
	m_config.addParameter(&m_uiGroup);

	if (config)
	{
		m_addressParameter.setValue(config->getAddress());
		m_portParameter.setValue(config->getPort());
		m_speedParameter.setValue(config->getMaxSpeed());
		m_accelParameter.setValue(config->getMaxAccel());
		m_toolParameter.setConvention(config->getTool()->getConvention());
		m_toolParameter.setPosition(config->getTool()->getPosition());
		m_toolParameter.setAngles(config->getTool()->getAngles());
	}

	m_addressParameter.lock();
	m_portParameter.lock();
	m_speedParameter.lock();
	m_accelParameter.lock();
	m_toolParameter.lock();

	connect(&m_freshRateParameter, &NumericalParameter::valueChanged, this, &AppModel::freshRateChanged);
}

bool AppModel::setupAddress(const RobotConfig* config)
{
	bool result = false;
	QString address = config->getAddress();
	int port = config->getPort();

	if (m_hostAddress.setAddress(address))
	{
		if (port > 0 && port <= 65535)
		{
			m_port = port;
			result = true;
		}
		else
			qWarning() << "Invalide port:" << port;
	}
	else
		qWarning() << "Invalide address:" << address;
	return result;
}

void AppModel::onMovementPressed(RobotKuka::MovementDirection direction)
{
}

void AppModel::onMovementReleased(RobotKuka::MovementDirection direction)
{
}

void AppModel::onRobotConnected()
{
	m_speedParameter.unlock();
	m_accelParameter.unlock();
	emit robotConnected();
}

void AppModel::onRobotDisconnected()
{
	m_speedParameter.lock();
	m_accelParameter.lock();
	m_connectionTimeoutParameter.unlock();
	emit robotDisconnected();
}

const Config* AppModel::getConfig() const
{
	return &m_config;
}

void AppModel::connectToRobot()
{
	if (m_robot)
	{
		m_connectionTimeoutParameter.lock();
		m_robot->connectToRobot(m_hostAddress, m_port, (int)m_connectionTimeoutParameter.getValue());
	}
}

void AppModel::disconnectFromRobot()
{
	if (m_robot)
	{
		m_robot->disconnectFromRobot();
		m_connectionTimeoutParameter.unlock();
	}
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

void AppModel::onErrorOccurred(const QString& message)
{
	emit errorOccurred(message);
}
