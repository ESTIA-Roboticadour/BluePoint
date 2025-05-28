#include "MainController.h"
#include "NavigationTree.h"
#include "NavigationNode.h"
#include "AppStore.h"
#include "ViewFactory.h"
#include "AppConfig.h"
#include "CameraConfig.h"
#include "LightControlConfig.h"

#include <QLabel>
#include <QMessageBox>

MainController::MainController(MainModel* model, MainWindow* view, QObject* parent) :
	WindowControllerBase(model, view, parent),
	m_view(view),
	m_model(model),
	m_tree(nullptr),
	m_rootNode(nullptr),
	m_deviceNode(nullptr),
	m_configurationNode(nullptr),
	m_lightNode(nullptr),
	m_workspaceNode(nullptr),
	m_roiNode(nullptr),
	m_appNode(nullptr)
{
	setupTreeNodes();
	setupConnections();

	updateCentralWidget(m_tree->currentNode());
}

MainController::~MainController()
{
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
	m_workspaceNode = m_configurationNode->getChild(1);
	m_roiNode = m_configurationNode->getChild(2);
}

void MainController::setupConnections()
{
	connect(m_model, &MainModel::released, this, &MainController::onModelReleased);

	connect(m_tree, &NavigationTree::navigationRequest, this, &MainController::onNavigationRequest);
	connect(m_tree, &NavigationTree::currentNodeChanged, this, &MainController::onNavigationDone);

	AppConfig* appConfig = AppStore::getAppConfig();
	connect(appConfig, &Config::pathChanged, this, &MainController::appConfigPathChanged);
	connect(appConfig, &Config::parameterChanged, this, &MainController::appConfigChanged);

	if (LightControlConfig* lightControlConfig = AppStore::getLightControlConfig())
		connect(lightControlConfig, &Config::pathChanged, this, &MainController::lightControlConfigPathChanged);

	if (CameraConfig* cameraConfig = AppStore::getCameraConfig())
		connect(cameraConfig, &Config::pathChanged, this, &MainController::cameraConfigPathChanged);

	if (RoiConfig* roiConfig = AppStore::getRoiConfig())
		connect(roiConfig, &Config::pathChanged, this, &MainController::roiConfigPathChanged);
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
	}
}

void MainController::onNavigationDone(NavigationNode* node)
{
	updateCentralWidget(node);
}

void MainController::appConfigChanged(const ParameterBase* sender)
{
	bool saved = AppStore::getAppConfig()->save();
}

void MainController::appConfigPathChanged(const QString& path)
{
	AppStore::setAppConfigPath(path);
}

void MainController::lightControlConfigPathChanged(const QString& path)
{
	AppStore::getAppConfig()->setLightControlConfigPath(path);
}

void MainController::cameraConfigPathChanged(const QString& path)
{
	AppStore::getAppConfig()->setCameraConfigPath(path);
}

void MainController::roiConfigPathChanged(const QString& path)
{
	AppStore::getAppConfig()->setRoiConfigPath(path);
}

void MainController::updateCentralWidget(NavigationNode* node)
{
	qreal opacity = 0.5;
	if (node == m_deviceNode)
	{
		AppConfig* config = AppStore::getAppConfig();
		CameraConfig* cameraConfig = AppStore::getCameraConfig();
		LightControlConfig* lightConfig = AppStore::getLightControlConfig();

		m_view->setCentralWidget(ViewFactory::createDeviceView(config->getCameraType(), cameraConfig, lightConfig, m_view));
	}
	else if (node == m_configurationNode)
	{
		m_view->setCentralWidget(ViewFactory::createConfigurationView("Configuration", AppStore::getAppConfig(), m_view));
	}
	else if (node == m_lightNode)
	{
		m_view->setCentralWidget(ViewFactory::createConfigurationView("Light configuratoin", AppStore::getLightControlConfig(), m_view));
	}
	else if (node == m_workspaceNode)
	{
		m_view->setCentralWidget(ViewFactory::createConfigurationView("Camera workspace configuratoin", AppStore::getCameraConfig(), m_view));
	}
	else if (node == m_roiNode)
	{
		m_view->setCentralWidget(ViewFactory::createConfigurationView("ROI configuratoin", AppStore::getRoiConfig(), m_view));
	}
	else
		// root
		// app
	{
		opacity = 1.0;
		//m_view->clearFilter();
		m_view->clearCentralWidget();
	}
	m_view->setBackgroundOpacity(opacity);
}
