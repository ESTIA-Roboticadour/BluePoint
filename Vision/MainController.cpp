#include "MainController.h"
#include "NavigationTree.h"
#include "NavigationNode.h"
#include "AppStore.h"
#include "ViewFactory.h"
#include "AppConfig.h"
#include "CameraConfig.h"
#include "LightControlConfig.h"
#include "Camera.h"

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

void MainController::updateCentralWidget(NavigationNode* node)
{
	qreal opacity = 0.5;
	if (node == m_deviceNode)
	{
		AppConfig* config = AppStore::getAppConfig();
		CameraConfig* cameraConfig = AppStore::getCameraConfig();
		LightControlConfig* lightConfig = AppStore::getLightControlConfig();
		Camera* camera = AppStore::getCamera();

		auto* view = ViewFactory::createDeviceView(cameraConfig, lightConfig, camera, m_view);
		m_view->setCentralWidget(view);
	}
	else if (node == m_configurationNode)
	{
		m_view->setCentralWidget(new QLabel("Configuration"));
	}
	else if (node == m_lightNode)
	{
		m_view->setCentralWidget(new QLabel("Light"));
	}
	else if (node == m_workspaceNode)
	{
		m_view->setCentralWidget(new QLabel("Workspace"));
	}
	else if (node == m_roiNode)
	{
		m_view->setCentralWidget(new QLabel("ROI"));
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
