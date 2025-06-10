#include "LightControlConfig.h"
#include "LightControl.h"
#include "ListParameterBase.h"
#include <QStringList>

LightControlConfig::LightControlConfig(QObject* parent) :
	Config(parent),
	m_comPort("COM Port", this),
	m_relay("Relay", 1, this)
{
	QStringList ports = LightControl::getAvailablePorts();
	for (auto& port : ports)
		m_comPort.addItem(port, port);

	defineBounds();
	addParameters();
}

LightControlConfig::LightControlConfig(const QString& comPort, int relay, QObject* parent) :
	Config(parent),
	m_comPort("COM Port", this),
	m_relay("Relay", relay, this)
{
	QStringList ports = LightControl::getAvailablePorts();
	for (auto& port : ports)
		m_comPort.addItem(port, port);

	if (m_comPort.containsKey(comPort))
		m_comPort.selectByKey(comPort);

	defineBounds();
	addParameters();
}

LightControlConfig::LightControlConfig(const LightControlConfig& config, QObject* parent) :
	Config(parent),
	m_comPort("COM Port", this),
	m_relay("Relay", config.m_relay, this)
{
	QStringList ports = LightControl::getAvailablePorts();
	for (auto& port : ports)
		m_comPort.addItem(port, port);
	
	QString otherSelectedPort = config.m_comPort.getSelectedKey();
	if (m_comPort.containsKey(otherSelectedPort))
		m_comPort.selectByKey(otherSelectedPort);

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
	return m_comPort.getSelectedKey();
}

int LightControlConfig::getRelay() const
{
	return m_relay.getValue();
}

void LightControlConfig::setComPort(const QString& comPort)
{
	if (m_comPort.containsKey(comPort))
		m_comPort.selectByKey(comPort);
}

void LightControlConfig::setRelay(const int relay)
{
	m_relay.setValue(relay);
}

void LightControlConfig::reset()
{
	LightControlConfig newConfig;
	setFromConfig(&newConfig, false);
}

Config* LightControlConfig::copy(QObject* parent) const
{
	LightControlConfig* newConfig = new LightControlConfig(parent);
	newConfig->setFromConfig(this, true);
	return newConfig;
}

bool LightControlConfig::setFromConfig(const Config* src, bool copyPath)
{
	int numberOfParametersToSet = 2;
	int numberOfParametersSet = 0;

	Config::setFromConfig(src, copyPath);
	if (src)
	{
		if (ListParameterBase* portList = qobject_cast<ListParameterBase*>(src->getParameter("COM Port")))
		{
			m_comPort.clear();
			QStringList ports = LightControl::getAvailablePorts();
			for (auto& port : ports)
				m_comPort.addItem(port, port);

			QString otherSelection = portList->getSelectedKey();
			if (m_comPort.containsKey(otherSelection))
				m_comPort.selectByKey(otherSelection);
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
