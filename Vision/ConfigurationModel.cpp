#include "ConfigurationModel.h"
#include "AppStore.h"

ConfigurationModel::ConfigurationModel(Config* srcConfig, QObject* parent) :
	ModelBase(parent),
	m_srcConfig(srcConfig),
	m_editableConfig(nullptr)
{
	if (m_srcConfig)
	{
		m_editableConfig = m_srcConfig->copy(this);
		connect(m_editableConfig, &Config::parameterChanged, this, &ConfigurationModel::onConfigChanged);
	}
	else
		qCritical() << "Source config is null";
}

Config* ConfigurationModel::getEditableConfig() const
{
	return m_editableConfig;
}

void ConfigurationModel::onConfigChanged(const ParameterBase* sender)
{
	AppStore::setIsInEdition(true);
	emit changed();
}

void ConfigurationModel::cancel()
{
	if (m_srcConfig)
	{
		m_editableConfig->setFromConfig(m_srcConfig, true);
		emit canceled();
	}
}

void ConfigurationModel::reset()
{
	if (m_editableConfig)
	{
		AppStore::setIsInEdition(true);
		m_editableConfig->reset();
	}
}

void ConfigurationModel::save(const QString& path)
{
	if (m_editableConfig && m_editableConfig->save(path))
	{
		AppStore::setIsInEdition(false);
		m_srcConfig->setFromConfig(m_editableConfig, true);
		emit saved(m_srcConfig);
	}
}

void ConfigurationModel::open(const QString& path)
{
	if (false)
	{
		AppStore::setIsInEdition(false);
		emit opened(path);
	}
}
