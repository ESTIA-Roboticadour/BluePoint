#include "MainModel.h"
#include "AppStore.h"
#include "ViewFactory.h"
#include "AppConfig.h"
#include "CameraConfig.h"
#include "BaslerCameraConfig.h"
#include "RealSenseCameraConfig.h"
#include "LightControlConfig.h"
#include "StringParameter.h"
#include "ListParameter.h"

#include <functional> // std::bind
#include <memory>

MainModel::MainModel(NavigationTree* tree, QObject* parent) :
	ModelBase(parent),
	m_tree(tree),
	m_rootNode(nullptr),
	m_deviceNode(nullptr),
	m_configurationNode(nullptr),
	m_lightNode(nullptr),
	m_cameraNode(nullptr),
	m_roiNode(nullptr),
	m_appNode(nullptr),
	m_tempConfig(nullptr),
	m_mockConfig(nullptr)
{
	setupTreeNodes();
	setupConnections();
}

MainModel::~MainModel()
{
	if (!isReleased())
		release();
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
	m_deviceNode = m_rootNode->getChild(0);
	m_configurationNode = m_rootNode->getChild(1);
	m_appNode = m_rootNode->getChild(2);

	m_lightNode = m_configurationNode->getChild(0);
	m_cameraNode = m_configurationNode->getChild(1);
	m_roiNode = m_configurationNode->getChild(2);
}

void MainModel::setupConnections()
{
	connect(AppStore::getAppConfig(), &AppConfig::pathChanged, this, &MainModel::appConfigPathChanged);
	connect(AppStore::getAppConfig(), &AppConfig::parameterChanged, this, &MainModel::appConfigParameterChanged);
	connect(AppStore::getAppConfig(), &Config::saved, this, &MainModel::appConfigSaved, Qt::UniqueConnection);
}

QWidget* MainModel::buildCentralWidget(const NavigationNode* node, QWidget* parent)
{
	if (node == m_deviceNode)
		return navigateDeviceNode(parent);

	else if (node == m_configurationNode)
		return navigateConfigurationNode(parent);

	else if (node == m_lightNode)
		return navigateLightNode(parent);

	else if (node == m_cameraNode)
		return navigateCameraNode(parent);

	else if (node == m_roiNode)
		return navigateRoiNode(parent);

	else
		// root
		// app
	{
		return nullptr;
	}
}

void MainModel::appConfigValidator(const ParameterBase* parameterChanged, Config* config)
{
	static bool settingConfig = false;

	if (settingConfig)
		return;

	AppConfig* appConfig = (AppConfig*)config;

	GroupParameter* path = (GroupParameter*)appConfig->getParameter("Paths");

	ParameterBase* pLightControlConfigPath = path->getParameter("Light Control Config Path");
	ParameterBase* pCameraConfigPath = path->getParameter("Camera Config Path");
	ParameterBase* pRoiConfigPath = path->getParameter("ROI Config Path");

	ParameterBase* pCameraType = ((GroupParameter*)appConfig->getParameter("Devices"))->getParameter("Camera Type");

	if (parameterChanged == pLightControlConfigPath)
	{
		if (!appConfig->isLightControlConfigValid())
		{
			emit warning("Invalid light control configuration", "The light control configuration file is incompatible.\nConfig file:"
				+ appConfig->getLightControlConfigPath() + "\n\nConfig file selection will be erased.");

			settingConfig = true;
			appConfig->setLightControlConfigPath("");
			settingConfig = false;
		}
	}
	else if (parameterChanged == pCameraType || parameterChanged == pCameraConfigPath)
	{
		if (!appConfig->areCameraTypeAndCameraConfigValid())
		{
			emit warning("Invalid camera configuration", "The camera type and the camera configuration file are incompatible.\nCamera type:" + appConfig->getCameraType() +
				"\nConfig file:" + appConfig->getCameraConfigPath() + "\n\nConfig file selection will be erased.");

			settingConfig = true;
			appConfig->setCameraConfigPath("");
			settingConfig = false;
		}
	}
	else if (parameterChanged == pRoiConfigPath)
	{
		emit warning("Invalid roi configuration", "The roi configuration file is incompatible.\nConfig file:"
			+ appConfig->getRoiConfigPath() + "\n\nConfig file selection will be erased.");
		settingConfig = true;
		appConfig->setRoiConfigPath("");
		settingConfig = false;
	}
}


void MainModel::appConfigPathChanged(const QString& path)
{
	AppStore::setAppConfigPath(path);
}

void MainModel::appConfigParameterChanged(const ParameterBase* sender)
{
	AppStore::getAppConfig()->save();
}

void MainModel::appConfigSaved(const Config* config)
{
	AppConfig* appConfig = AppStore::getAppConfig();
	if (!appConfig->isLightControlConfigValid())
	{
		emit warning("Invalid light controll configuration", "The light control configuration file is incompatible.\nConfig file:"
			+ appConfig->getLightControlConfigPath() + "\n\nConfig file selection will be erased.");
		appConfig->setLightControlConfigPath("");
	}
	if (!appConfig->areCameraTypeAndCameraConfigValid())
	{
		emit warning("Invalid camera configuration", "The camera type and the camera configuration file are incompatible.\nCamera type:" + appConfig->getCameraType() +
			"\nConfig file:" + appConfig->getCameraConfigPath() + "\n\nConfig file selection will be erased.");
		appConfig->setCameraConfigPath("");

		AppStore::eraseCameraConfig();
	}
	if (!appConfig->isRoiConfigValid())
	{
		emit warning("Invalid roi configuration", "The roi configuration file is incompatible.\nConfig file:"
			+ appConfig->getRoiConfigPath() + "\n\nConfig file selection will be erased.");
		appConfig->setRoiConfigPath("");
	}
}

void MainModel::lightControlConfigSaved(const Config* config)
{
	if (!AppStore::getLightControlConfig())
	{
		if (LightControlConfig* lightConfig = (LightControlConfig*)dynamic_cast<const LightControlConfig*>(config))
		{
			AppStore::setLightControlConfig(lightConfig);
		}
	}
	AppStore::getAppConfig()->setLightControlConfigPath(config->getPath());
}

void MainModel::cameraConfigSaved(const Config* config)
{
	// @Todo: Verifier le type de la camera pour voir si ça correspond avec la config sélectionnée
	if (!AppStore::getCameraConfig())
	{
		if (CameraConfig* cameraConfig = (CameraConfig*)dynamic_cast<const CameraConfig*>(config))
		{
			AppStore::setCameraConfig(cameraConfig);
		}
	}
	AppStore::getAppConfig()->setCameraConfigPath(config->getPath());
}

void MainModel::roiConfigSaved(const Config* config)
{
	if (!AppStore::getRoiConfig())
	{
		if (RoiConfig* roiConfig = (RoiConfig*)dynamic_cast<const RoiConfig*>(config))
		{
			AppStore::setRoiConfig(roiConfig);
		}
	}
	AppStore::getAppConfig()->setRoiConfigPath(config->getPath());
}

QWidget* MainModel::navigateDeviceNode(QWidget* parent)
{
	return ViewFactory::createDeviceView(AppStore::getAppConfig()->getCameraType(), AppStore::getCameraConfig(), AppStore::getLightControlConfig(), parent);
}

QWidget* MainModel::navigateConfigurationNode(QWidget* parent)
{
	return ViewFactory::createConfigurationView("Configuration", AppStore::getAppConfig(), parent, std::bind(&MainModel::appConfigValidator, this, std::placeholders::_1, std::placeholders::_2));
}

QWidget* MainModel::navigateLightNode(QWidget* parent)
{
	LightControlConfig* config = AppStore::getLightControlConfig();
	if (!config)
	{
		config = new LightControlConfig();
		m_tempConfig = config;
	}
	connect(config, &Config::saved, this, &MainModel::lightControlConfigSaved, Qt::UniqueConnection);
	return ViewFactory::createConfigurationView("Light configuration", config, parent);
}

QWidget* MainModel::navigateCameraNode(QWidget* parent)
{
	CameraConfig* config = AppStore::getCameraConfig();
	if (!config)
	{
		QString cameraType = AppStore::getAppConfig()->getCameraType();
		if (cameraType == "Basler")
			config = new BaslerCameraConfig();
		else if (cameraType == "RealSense")
			config = new RealSenseCameraConfig();

		m_tempConfig = config;
	}
	connect(config, &Config::saved, this, &MainModel::cameraConfigSaved, Qt::UniqueConnection);
	return ViewFactory::createConfigurationView("Camera configuration", config, parent);
}

QWidget* MainModel::navigateRoiNode(QWidget* parent)
{
	RoiConfig* config = AppStore::getRoiConfig();
	if (!config)
	{
		config = new RoiConfig();
		m_tempConfig = config;
	}
	connect(config, &Config::saved, this, &MainModel::roiConfigSaved, Qt::UniqueConnection);
	return ViewFactory::createConfigurationView("ROI configuration", config, parent);
}
