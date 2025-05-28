#include "ConfigurationModel.h"
#include "AppStore.h"

ConfigurationModel::ConfigurationModel(const Config* config, QObject* parent) :
	ModelBase(parent),
	m_srcConfig(config),
	m_editableConfig(nullptr)
{
	if (m_srcConfig)
	{
		m_editableConfig = new Config(*config, this);
		connect(m_editableConfig, &Config::parameterChanged, this, &ConfigurationModel::configChanged);
	}
	else
		qWarning() << "Source configuration is empty.";
}

const Config* ConfigurationModel::getConfig() const
{
	return m_editableConfig;
}

bool ConfigurationModel::save(const QString& path) const
{
	bool saved = m_editableConfig && m_editableConfig->save(path);
	if (saved)
	{
		AppStore::setIsInEdition(false);
		// mets à jour la sauvegarde de la configuration source
		//m_srcConfig->setFromConfig(m_editableConfig);
		// Question : pb si sauvegarde dans un autre fichier ? -> La AppConfig devrait mettre à jour le fichier
		// designer une callback de sauvegarde à fournir dans le ctor ?
	}
	return saved;
}

void ConfigurationModel::configChanged(const ParameterBase* sender)
{
	AppStore::setIsInEdition(true);
}
