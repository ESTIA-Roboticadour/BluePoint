#include "AppModel.h"
#include "EulerFrameParameter.h"

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
	m_freshRateParameter(NumericalParameter("Fresh Rate (Hz)", 20, this)),
	m_cartesianTranslationStep(NumericalParameter("Cartesian Translation Step (mm)", 0.25, this)),
	m_cartesianRotationStep(NumericalParameter("Cartesian Rotation Step (deg)", 0.25, this)),
	m_jointStep(NumericalParameter("Joint Step (deg)", 0.025, this))
{
	setupConfig(config);
	if (config && setupAddress(config))
	{
		m_robot = new RobotKuka(this);
		m_robot->setCartesianTranslationStep(m_cartesianTranslationStep.getValue());
		m_robot->setCartesianRotationStep(m_cartesianRotationStep.getValue());
		m_robot->setJointStep(m_jointStep.getValue());

		connect(m_robot, &RobotKuka::statusChanged, this, &AppModel::robotStatusChanged);
		connect(m_robot, &RobotKuka::robotStateChanged, this, &AppModel::robotStateChanged);
		connect(m_robot, &RobotKuka::connected, this, &AppModel::onRobotConnected);
		connect(m_robot, &RobotKuka::disconnected, this, &AppModel::onRobotDisconnected);
		connect(m_robot, &RobotKuka::started, this, &AppModel::robotStarted);
		connect(m_robot, &RobotKuka::stopped, this, &AppModel::robotStopped);
		connect(m_robot, &RobotKuka::failedToConnect, this, &AppModel::onRobotFailedToConnect);
		connect(m_robot, &RobotKuka::errorOccurred, this, &AppModel::onErrorOccurred);
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
	if (m_robot)
		m_robot->getCurrentPose(currentPose);
}

void AppModel::getCurrentJoint(double currentJoint[6]) const
{
	if (m_robot)
		m_robot->getCurrentJoint(currentJoint);
}

void AppModel::getCurrentDelta(double currentDelta[6]) const
{
	if (m_robot)
		m_robot->getCurrentDelta(currentDelta);
}

void AppModel::setupConfig(const RobotConfig* config)
{
	m_portParameter.setMaximum(65535);
	m_freshRateParameter.setMinimum(1);
	m_freshRateParameter.setMaximum(60);
	m_connectionTimeoutParameter.setMaximum(300);

	m_cartesianTranslationStep.setIncrement(0.001);
	m_cartesianTranslationStep.setMinimum(0.001);
	m_cartesianTranslationStep.setMaximum(0.5);
	m_cartesianTranslationStep.setValue(0.25);

	m_cartesianRotationStep.setIncrement(0.001);
	m_cartesianRotationStep.setMinimum(0.001);
	m_cartesianRotationStep.setMaximum(0.25);
	m_cartesianRotationStep.setValue(0.125);

	m_jointStep.setIncrement(0.001);
	m_jointStep.setMinimum(0.001);
	m_jointStep.setMaximum(0.05);
	m_jointStep.setValue(0.01);

	m_robotGroup.addParameter(&m_addressParameter);
	m_robotGroup.addParameter(&m_portParameter);
	m_robotGroup.addParameter(&m_speedParameter);
	m_robotGroup.addParameter(&m_accelParameter);
	m_robotGroup.addParameter(&m_toolParameter);
	m_robotGroup.addParameter(&m_cartesianTranslationStep);
	m_robotGroup.addParameter(&m_cartesianRotationStep);
	m_robotGroup.addParameter(&m_jointStep);

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
		m_toolParameter.setEulerFrame(config->getTool()->getPosition(), config->getTool()->getAngles());
		if (m_toolParameter.getConvention() != EulerFrameParameter::Convention::ZYX)
			m_toolParameter.setConvention(EulerFrameParameter::Convention::ZYX);
	}

	m_addressParameter.lock();
	m_portParameter.lock();
	m_speedParameter.lock();
	m_accelParameter.lock();
	m_toolParameter.lock();

	connect(&m_freshRateParameter, &NumericalParameter::valueChanged, this, &AppModel::freshRateChanged);
	connect(&m_cartesianTranslationStep, &NumericalParameter::valueChanged, this, &AppModel::onCartesianTranslationStepChanged);
	connect(&m_cartesianRotationStep, &NumericalParameter::valueChanged, this, &AppModel::onCartesianRotationStepChanged);
	connect(&m_jointStep, &NumericalParameter::valueChanged, this, &AppModel::onJointStepChanged);
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

void AppModel::onCartesianMovementPressed(RobotKuka::Axis axis, bool positive)
{
	if (m_robot)
		m_robot->moveAxis(axis, positive);
}

void AppModel::onCartesianMovementReleased(RobotKuka::Axis axis)
{
	Q_UNUSED(axis);
	if (m_robot)
		m_robot->stopMove();
}

void AppModel::onArticularMovementPressed(RobotKuka::Joint joint, bool positive)
{
	if (m_robot)
		m_robot->moveJoint(joint, positive);
}

void AppModel::onArticularMovementReleased(RobotKuka::Joint joint)
{
	Q_UNUSED(joint);
	if (m_robot)
		m_robot->stopMove();
}

void AppModel::onInputToggled(RobotKuka::IOInput input, bool enabled)
{
}

void AppModel::onOutputToggled(RobotKuka::IOOutput output, bool enabled)
{
}

void AppModel::onIsInRobotBaseChanged(bool isInRobotBase)
{
	if (m_robot)
		m_robot->setRobotBase(isInRobotBase);
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

void AppModel::onRobotFailedToConnect()
{
	m_connectionTimeoutParameter.unlock();
}

void AppModel::onCartesianTranslationStepChanged(double value)
{
	if (m_robot)
		m_robot->setCartesianTranslationStep(value);
}

void AppModel::onCartesianRotationStepChanged(double value)
{
	if (m_robot)
		m_robot->setCartesianRotationStep(value);
}

void AppModel::onJointStepChanged(double value)
{
	if (m_robot)
		m_robot->setJointStep(value);
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

void AppModel::cancelConnectToRobot()
{
	if (m_robot)
		m_robot->abortConnection();
}

void AppModel::disconnectFromRobot()
{
	if (m_robot)
	{
		m_robot->disconnectFromRobot();
		m_connectionTimeoutParameter.unlock();
	}
	onRobotDisconnected(); // TODO : to delete
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

RobotKuka::Status AppModel::getRobotStatus() const
{
	return m_robot ? m_robot->getStatus() : RobotKuka::Status::None;
}

RobotKuka::RobotState AppModel::getRobotState() const
{
	return m_robot ? m_robot->getRobotState() : RobotKuka::RobotState::None;
}

void AppModel::onErrorOccurred(const QString& message)
{
	emit errorOccurred(message);
}
