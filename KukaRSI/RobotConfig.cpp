#include "RobotConfig.h"

RobotConfig::RobotConfig(QObject* parent) :
	Config(parent),
	m_address("Address", "172.31.2.100", StringParameter::Kind::Plain, this),
	m_port("Port", 12345, this),
	m_maxSpeed("Max. Speed (%)", 10, this),
	m_maxAccel("Max. Accel (%)", 50, this),
	m_matrix("Tool Matrix", QMatrix4x4(), this)
{
	defineBounds();
	addParameters();
}

RobotConfig::RobotConfig(const RobotConfig& config, QObject* parent) :
	Config(parent),
	m_address("Address", config.m_address, this),
	m_port("Port", config.m_port, this),
	m_maxSpeed("Max. Speed (%)", config.m_maxSpeed, this),
	m_maxAccel("Max. Accel (%)", config.m_maxAccel, this),
	m_matrix("Tool Matrix", config.m_matrix, this)
{
	m_address.setKind(StringParameter::Kind::Plain);
	
	defineBounds();
	addParameters();
}

void RobotConfig::defineBounds()
{
	m_port.setMaximum(65535);
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
	return m_matrix.getValue();
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
	m_matrix.setValue(matrix);
}

void RobotConfig::reset()
{
	RobotConfig newConfig;
	setFromConfig(&newConfig, false);
}

Config* RobotConfig::copy(QObject* parent) const
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
		if (NumericalParameter* maxSpeed = qobject_cast<NumericalParameter*>(src->getParameter("Max. Speed (%)")))
		{
			m_maxSpeed.setValue(maxSpeed->getValue());
			numberOfParametersSet++;
		}
		if (NumericalParameter* maxAccel = qobject_cast<NumericalParameter*>(src->getParameter("Max. Accel (%)")))
		{
			m_maxAccel.setValue(maxAccel->getValue());
			numberOfParametersSet++;
		}
		if (Matrix4x4Parameter* matrix = qobject_cast<Matrix4x4Parameter*>(src->getParameter("Tool Matrix")))
		{
			m_matrix.setValue(matrix->getValue());
			numberOfParametersSet++;
		}
	}
	return numberOfParametersSet == numberOfParametersToSet;
}
