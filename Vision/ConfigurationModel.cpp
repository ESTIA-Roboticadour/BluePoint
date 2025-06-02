#include "ConfigurationModel.h"
#include "AppStore.h"

#include <QFile>
#include <memory>

ConfigurationModel::ConfigurationModel(Config* srcConfig, QObject* parent, ConfigValidatorCallback validator) :
	ModelBase(parent),
	m_srcConfig(srcConfig),
	m_editableConfig(nullptr),
	m_validator{ std::move(validator) }
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

	// Appel de la callback si elle existe
	if (m_validator)              // std::function bool-convertible
		m_validator(sender, m_editableConfig);
}

void ConfigurationModel::cancel()
{
	if (m_srcConfig)
	{
		disconnect(m_editableConfig, &Config::parameterChanged, this, &ConfigurationModel::onConfigChanged);
		m_editableConfig->setFromConfig(m_srcConfig, true);
		connect(m_editableConfig, &Config::parameterChanged, this, &ConfigurationModel::onConfigChanged);

		AppStore::setIsInEdition(false);
		emit canceled();
	}
}

void ConfigurationModel::reset()
{
	if (m_editableConfig)
	{
		AppStore::setIsInEdition(true);
		disconnect(m_editableConfig, &Config::parameterChanged, this, &ConfigurationModel::onConfigChanged);
		m_editableConfig->reset();
		connect(m_editableConfig, &Config::parameterChanged, this, &ConfigurationModel::onConfigChanged);
	}
}

void ConfigurationModel::save(const QString& path)
{
	if (m_editableConfig)
	{
		Config* backup = m_srcConfig->copy();

		m_srcConfig->setFromConfig(m_editableConfig, true);

		if (m_srcConfig->save(path))
		{
			AppStore::setIsInEdition(false);
			m_editableConfig->setFromConfig(m_srcConfig, true); // be sure of config path
			emit saved(m_editableConfig);
		}
		else
		{
			m_srcConfig->setFromConfig(backup, true);
		}
		
		delete backup;
	}
}

void ConfigurationModel::open(const QString& path)
{
	if (QFile::exists(path))
	{
		std::unique_ptr<Config> pConfig = Config::loadFromFile(path);
		if (pConfig)
		{
			AppStore::setIsInEdition(true);
			disconnect(m_editableConfig, &Config::parameterChanged, this, &ConfigurationModel::onConfigChanged);
			m_editableConfig->setFromConfig(pConfig.get(), false);
			connect(m_editableConfig, &Config::parameterChanged, this, &ConfigurationModel::onConfigChanged);
			qInfo() << "Config loaded:" << path;
			emit changed();
		}
		else
			qWarning() << "Can not load the config";
	}
	else
		qWarning() << "File not found:" << path;
}
