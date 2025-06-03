#include "MainController.h"
#include "NavigationTree.h"
#include "NavigationNode.h"
#include "AppStore.h"
#include "ViewFactory.h"
#include "AppConfig.h"
#include "CameraConfig.h"
#include "BaslerCameraConfig.h"
#include "RealSenseCameraConfig.h"
#include "LightControlConfig.h"
#include "StringParameter.h"
#include "ListParameter.h"

#include <QLabel>
#include <QMessageBox>
#include <functional> // std::bind
#include <memory>

MainController::MainController(MainModel* model, MainWindow* view, QObject* parent) :
	WindowControllerBase(model, view, parent),
	m_view(view),
	m_model(model),
	m_tempConfig(nullptr),
	m_mockConfig(this),
	m_tree(nullptr),
	m_rootNode(nullptr),
	m_deviceNode(nullptr),
	m_configurationNode(nullptr),
	m_lightNode(nullptr),
	m_cameraNode(nullptr),
	m_roiNode(nullptr),
	m_appNode(nullptr)
{
	setupTreeNodes();
	setupConnections();

	updateCentralWidget(m_tree->currentNode());
}

MainController::~MainController()
{
	if (m_tempConfig)
		m_tempConfig->deleteLater();
	if (m_model)
		m_model->deleteLater();
	if (m_view)
		m_view->deleteLater();
}

void MainController::setupTreeNodes()
{
	m_tree = m_view->getTree();

	m_rootNode = m_tree->root();
	m_deviceNode = m_rootNode->getChild(0);
	m_configurationNode = m_rootNode->getChild(1);
	m_appNode = m_rootNode->getChild(2);

	m_lightNode = m_configurationNode->getChild(0);
	m_cameraNode = m_configurationNode->getChild(1);
	m_roiNode = m_configurationNode->getChild(2);
}

void MainController::setupConnections()
{
	connect(m_model, &MainModel::released, this, &MainController::onModelReleased);

	connect(m_tree, &NavigationTree::navigationRequest, this, &MainController::onNavigationRequest);
	connect(m_tree, &NavigationTree::currentNodeChanged, this, &MainController::onNavigationDone);

	connect(AppStore::getAppConfig(), &AppConfig::pathChanged, this, &MainController::appConfigPathChanged);
	connect(AppStore::getAppConfig(), &AppConfig::parameterChanged, this, &MainController::appConfigParameterChanged);
	connect(AppStore::getAppConfig(), &Config::saved, this, &MainController::appConfigSaved, Qt::UniqueConnection);
}

void MainController::onViewCloseRequested()
{
	m_model->release();
}

void MainController::onModelReleased()
{
	deleteLater();
}

void MainController::onNavigationRequest(NavigationNode* newNode, NavigationNode* currentNode, bool* accept)
{
	if (AppStore::isInEdition())
	{
		// Prevent navigation if in edition mode and not on root or app node
		*accept = QMessageBox::question(m_view, "File not saved!", "You're still editing a file! Are you sure to quit the page? Modifications will be lost.",
			QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes;
		if (*accept)
			AppStore::setIsInEdition(false);
	}
}

void MainController::onNavigationDone(NavigationNode* node)
{
	if (m_tempConfig)
	{
		m_tempConfig->deleteLater();
		m_tempConfig = nullptr;
	}
	updateCentralWidget(node);
}

void MainController::updateCentralWidget(NavigationNode* node)
{
	qreal opacity = 0.5;
	if (node == m_deviceNode)
		navigateDeviceNode();

	else if (node == m_configurationNode)
		navigateConfigurationNode();

	else if (node == m_lightNode)
		navigateLightNode();

	else if (node == m_cameraNode)
		navigateCameraNode();

	else if (node == m_roiNode)
		navigateRoiNode();

	else
		// root
		// app
	{
		opacity = 1.0;
		m_view->clearCentralWidget();
	}
	//m_view->setFilter(QColor(255, 0, 0), 0.3);
	m_view->setBackgroundOpacity(opacity);
}

void MainController::appConfigValidator(const ParameterBase* parameterChanged, Config* config)
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
			QMessageBox::warning(m_view, "Invalid light control configuration", "The light control configuration file is incompatible.\nConfig file:"
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
			QMessageBox::warning(m_view, "Invalid camera configuration", "The camera type and the camera configuration file are incompatible.\nCamera type:" + appConfig->getCameraType() +
				"\nConfig file:" + appConfig->getCameraConfigPath() + "\n\nConfig file selection will be erased.");

			settingConfig = true;
			appConfig->setCameraConfigPath("");
			settingConfig = false;
		}
	}
	else if (parameterChanged == pRoiConfigPath)
	{
		QMessageBox::warning(m_view, "Invalid roi configuration", "The roi configuration file is incompatible.\nConfig file:"
			+ appConfig->getRoiConfigPath() + "\n\nConfig file selection will be erased.");
		settingConfig = true;
		appConfig->setRoiConfigPath("");
		settingConfig = false;
	}
}

void MainController::appConfigPathChanged(const QString& path)
{
	AppStore::setAppConfigPath(path);
}

void MainController::appConfigParameterChanged(const ParameterBase* sender)
{
	AppStore::getAppConfig()->save();
}

void MainController::appConfigSaved(const Config* config)
{
	AppConfig* appConfig = AppStore::getAppConfig();
	if (!appConfig->isLightControlConfigValid())
	{
		QMessageBox::warning(m_view, "Invalid light controll configuration", "The light control configuration file is incompatible.\nConfig file:"
			+ appConfig->getLightControlConfigPath() + "\n\nConfig file selection will be erased.");
		appConfig->setLightControlConfigPath("");
	}
	if (!appConfig->areCameraTypeAndCameraConfigValid())
	{
		QMessageBox::warning(m_view, "Invalid camera configuration", "The camera type and the camera configuration file are incompatible.\nCamera type:" + appConfig->getCameraType() +
			"\nConfig file:" + appConfig->getCameraConfigPath() + "\n\nConfig file selection will be erased.");
		appConfig->setCameraConfigPath("");

		AppStore::eraseCameraConfig();
	}
	if (!appConfig->isRoiConfigValid())
	{
		QMessageBox::warning(m_view, "Invalid roi configuration", "The roi configuration file is incompatible.\nConfig file:" 
			+ appConfig->getRoiConfigPath() + "\n\nConfig file selection will be erased.");
		appConfig->setRoiConfigPath("");
	}
}

void MainController::lightControlConfigSaved(const Config* config)
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

void MainController::cameraConfigSaved(const Config* config)
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

void MainController::roiConfigSaved(const Config* config)
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

void MainController::navigateDeviceNode()
{
	AppConfig* config = AppStore::getAppConfig();
	CameraConfig* cameraConfig = AppStore::getCameraConfig();
	LightControlConfig* lightConfig = AppStore::getLightControlConfig();

	m_view->setCentralWidget(ViewFactory::createDeviceView(config->getCameraType(), cameraConfig, lightConfig, m_view));
}

void MainController::navigateConfigurationNode()
{
	m_view->setCentralWidget(ViewFactory::createConfigurationView("Configuration", AppStore::getAppConfig(), m_view, std::bind(&MainController::appConfigValidator, this, std::placeholders::_1, std::placeholders::_2)));
}

void MainController::navigateLightNode()
{
	LightControlConfig* config = AppStore::getLightControlConfig();
	if (!config)
	{
		config = new LightControlConfig();
		m_tempConfig = config;
	}
	connect(config, &Config::saved, this, &MainController::lightControlConfigSaved, Qt::UniqueConnection);
	m_view->setCentralWidget(ViewFactory::createConfigurationView("Light configuration", config, m_view));
}

void MainController::navigateCameraNode()
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
	connect(config, &Config::saved, this, &MainController::cameraConfigSaved, Qt::UniqueConnection);
	m_view->setCentralWidget(ViewFactory::createConfigurationView("Camera configuration", config, m_view));
}

void MainController::navigateRoiNode()
{
	RoiConfig* config = AppStore::getRoiConfig();
	if (!config)
	{
		config = new RoiConfig();
		m_tempConfig = config;
	}
	connect(config, &Config::saved, this, &MainController::roiConfigSaved, Qt::UniqueConnection);
	m_view->setCentralWidget(ViewFactory::createConfigurationView("ROI configuration", config, m_view));
}
