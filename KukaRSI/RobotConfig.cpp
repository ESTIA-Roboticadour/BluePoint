#include "RobotConfig.h"

RobotConfig::RobotConfig(QObject* parent) :
	Config(parent),
	m_address("Address", "192.168.1.xxx", StringParameter::Kind::Plain, this),
	m_port("Port", 12345, this),
	m_maxSpeed("Max. Speed (deg/s)", 0, this),
	m_maxAccel("Max. Accel (deg/s^2)", 0, this),
	m_matrix("Tool Matrix", QMatrix4x4(), this)
{
	QMatrix4x4 matrix;
	matrix.setToIdentity();
	m_matrix.setMatrix(matrix);

	defineBounds();
	addParameters();
}

RobotConfig::RobotConfig(const RobotConfig& config, QObject* parent) :
	Config(parent),
	m_address("Address", config.m_address, this),
	m_port("Port", config.m_port, this),
	m_maxSpeed("Max. speed (deg/s)", config.m_maxSpeed, this),
	m_maxAccel("Max. accel (deg/s^2)", config.m_maxAccel, this),
	m_matrix("Tool matrix", config.m_matrix, this)
{
	m_address.setKind(StringParameter::Kind::Plain);
	
	defineBounds();
	addParameters();
}

void RobotConfig::defineBounds()
{
	m_port.setMinimum(0);
	m_port.setMinimum(65535);

	m_maxSpeed.setMaximum(200);
	m_maxAccel.setMaximum(200);
}

void RobotConfig::addParameters()
{
	addParameter(&m_address);
	addParameter(&m_port);
	addParameter(&m_maxSpeed);
	addParameter(&m_maxAccel);
	addParameter(&m_matrix);
}

QString RobotConfig::getAddress() const
{
	return m_address.getValue();
}

int RobotConfig::getPort() const
{
	return m_port.getValue();
}

int RobotConfig::getMaxSpeed() const
{
	return m_maxSpeed.getValue();
}

int RobotConfig::getMaxAccel() const
{
	return m_maxAccel.getValue();
}

QMatrix4x4 RobotConfig::getMatrix() const
{
	return m_matrix.getMatrix();
}

void RobotConfig::setAddress(const QString& address)
{
	m_address.setValue(address);
}

void RobotConfig::setPort(const int port)
{
	m_port.setValue(port);
}

void RobotConfig::setMaxSpeed(const int maxSpeed)
{
	m_maxSpeed.setValue(maxSpeed);
}

void RobotConfig::setMaxAccel(const int maxAccel)
{
	m_maxAccel.setValue(maxAccel);
}

void RobotConfig::setMatrix(const QMatrix4x4& matrix) 
{
	m_matrix.setMatrix(matrix);
}

void RobotConfig::reset()
{
	RobotConfig newConfig;
	setFromConfig(&newConfig, false);
}

Config* RobotConfig::copy(QObject* parent)
{
	RobotConfig* newConfig = new RobotConfig(parent);
	newConfig->setFromConfig(this, true);
	return newConfig;
}

bool RobotConfig::setFromConfig(const Config* src, bool copyPath)
{
	int numberOfParametersToSet = 5;
	int numberOfParametersSet = 0;

	Config::setFromConfig(src, copyPath);
	if (src)
	{
		if (StringParameter* address = qobject_cast<StringParameter*>(src->getParameter("Address")))
		{
			m_address.setValue(address->getValue());
			numberOfParametersSet++;
		}
		if (NumericalParameter* port = qobject_cast<NumericalParameter*>(src->getParameter("Port")))
		{
			m_port.setValue(port->getValue());
			numberOfParametersSet++;
		}
		if (NumericalParameter* maxSpeed = qobject_cast<NumericalParameter*>(src->getParameter("Max. Speed (deg/s)")))
		{
			m_maxSpeed.setValue(maxSpeed->getValue());
			numberOfParametersSet++;
		}
		if (NumericalParameter* maxAccel = qobject_cast<NumericalParameter*>(src->getParameter("Max. Accel (deg/s^2)")))
		{
			m_maxAccel.setValue(maxAccel->getValue());
			numberOfParametersSet++;
		}
		if (Matrix4x4Parameter* matrix = qobject_cast<Matrix4x4Parameter*>(src->getParameter("Tool Matrix")))
		{
			m_matrix.setMatrix(matrix->getMatrix());
			numberOfParametersSet++;
		}
	}
	return numberOfParametersSet == numberOfParametersToSet;
}
