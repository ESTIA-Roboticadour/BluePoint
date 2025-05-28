#include "LightControlConfig.h"

LightControlConfig::LightControlConfig(QObject* parent) :
	Config(parent),
	m_comPort("COM Port", "", StringParameter::Kind::Plain, this),
	m_relay("Relay", 1, this)
{
	defineBounds();
	addParameters();
}

LightControlConfig::LightControlConfig(const QString& comPort, int relay, QObject* parent) :
	Config(parent),
	m_comPort("COM Port", comPort, StringParameter::Kind::Plain, this),
	m_relay("Relay", relay, this)
{
	defineBounds();
	addParameters();
}

LightControlConfig::LightControlConfig(const LightControlConfig& config, QObject* parent) :
	Config(parent),
	m_comPort("COM Port", config.m_comPort, this),
	m_relay("Relay", config.m_relay, this)
{
	m_comPort.setKind(StringParameter::Kind::Plain);
	defineBounds();
	addParameters();
}

void LightControlConfig::defineBounds()
{
	m_relay.setMinimum(1);
	m_relay.setMaximum(4);
	m_relay.setIncrement(1);
}

void LightControlConfig::addParameters()
{
	addParameter(&m_comPort);
	addParameter(&m_relay);
}

QString LightControlConfig::getComPort() const
{
	return m_comPort.getValue();
}

int LightControlConfig::getRelay() const
{
	return m_relay.getValue();
}

void LightControlConfig::setComPort(const QString& comPort)
{
	m_comPort.setValue(comPort);
}

void LightControlConfig::setRelay(const int relay)
{
	m_relay.setValue(relay);
}

bool LightControlConfig::setFromConfig(const Config* src)
{
	int numberOfParametersToSet = 2;
	int numberOfParametersSet = 0;

	if (src)
	{
		if (StringParameter* com = qobject_cast<StringParameter*>(src->getParameter("COM Port")))
		{
			m_comPort.setValue(com->getValue());
			numberOfParametersSet++;
		}

		if (NumericalParameter* relay = qobject_cast<NumericalParameter*>(src->getParameter("Relay")))
		{
			m_relay.setValue(relay->getValue());
			numberOfParametersSet++;
		}
	}
	return numberOfParametersSet == numberOfParametersToSet;
}
