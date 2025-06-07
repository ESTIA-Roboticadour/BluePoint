#include "MainModel.h"
#include "AppStore.h"
#include "ViewFactory.h"
#include "Config.h"
#include "RobotConfig.h"
#include "Helper.h"

#include <QFile>
#include <memory>

MainModel::MainModel(NavigationTree* tree, QObject* parent) :
	ModelBase(parent),
	m_tree(tree),
	m_tempConfig(nullptr),
	m_rootNode(nullptr),
	m_configurationNode(nullptr),
	m_appNode(nullptr)
{
	setupTreeNodes();
	tryOpenRobotConfig();
}

MainModel::~MainModel()
{
	if (m_tempConfig)
		m_tempConfig->deleteLater();
}

NavigationTree* MainModel::tree() const
{
	return m_tree;
}

void MainModel::release()
{
	if (m_tempConfig)
	{
		m_tempConfig->deleteLater();
		m_tempConfig = nullptr;
	}
	ModelBase::release();
}

void MainModel::setupTreeNodes()
{
	m_rootNode = m_tree->root();
	m_configurationNode = m_rootNode->getChild(0);
	m_appNode = m_rootNode->getChild(1);
}

void MainModel::tryOpenRobotConfig() const
{
	QString defaultPath = Helper::makePathAbsolute("Config/default.json");
	if (QFile::exists(defaultPath))
	{
		bool fullyLoaded;
		std::unique_ptr<RobotConfig> config = RobotConfig::loadFromFile<RobotConfig>(defaultPath, fullyLoaded);
		if (config)
		{
			qInfo() << "Config loaded: " + defaultPath;
			AppStore::setRobotConfig(config.get());
		}
	}
}

QWidget* MainModel::buildCentralWidget(const NavigationNode* node, QWidget* parent)
{
	if (m_tempConfig)
	{
		m_tempConfig->deleteLater();
		m_tempConfig = nullptr;
	}

	if (node == m_configurationNode)
		return navigateConfigurationNode(parent);
	else if (node == m_appNode)
		return navigateAppNode(parent);
	else
		return nullptr;
}

QWidget* MainModel::navigateConfigurationNode(QWidget* parent)
{
	RobotConfig* config = AppStore::getRobotConfig();
	if (!config)
	{
		config = new RobotConfig();
		m_tempConfig = config;
	}
	connect(config, &Config::saved, this, &MainModel::robotConfigSaved, Qt::UniqueConnection);
	return ViewFactory::createConfigurationView("Robot configuration", config, parent);
}

QWidget* MainModel::navigateAppNode(QWidget* parent)
{
	return ViewFactory::createAppView(AppStore::getRobotConfig(), parent);
}

void MainModel::robotConfigSaved(const Config* config)
{
	if (!AppStore::getRobotConfig())
	{
		if (RobotConfig* lightConfig = (RobotConfig*)dynamic_cast<const RobotConfig*>(config))
		{
			AppStore::setRobotConfig(lightConfig);
		}
	}
}
