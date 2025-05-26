#include "MainController.h"
#include "NavigationTree.h"
#include "NavigationNode.h"
#include <QLabel>

MainController::MainController(MainModel* model, MainWindow* view, QObject* parent) :
	WindowControllerBase(model, view, parent),
	m_view(view),
	m_model(model),
	m_tree(nullptr),
	m_rootNode(nullptr),
	m_deviceNode(nullptr),
	m_configurationNode(nullptr),
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

	m_workspaceNode = m_configurationNode->getChild(0);
	m_roiNode = m_configurationNode->getChild(1);
}

void MainController::setupConnections()
{
	connect(m_model, &MainModel::released, this, &MainController::onModelReleased);

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

void MainController::onNavigationDone(NavigationNode* node)
{
	updateCentralWidget(node);
}

void MainController::updateCentralWidget(NavigationNode* node)
{
	if (node == m_configurationNode)
	{
		m_view->setBackgroundOpacity(0.5);
		m_view->setCentralWidget(new QLabel("Configuration"));
	}
	else if (node == m_deviceNode)
	{
		m_view->setBackgroundOpacity(0.5);
		m_view->setCentralWidget(new QLabel("Device"));
	}
	else if (node == m_workspaceNode)
	{
		m_view->setBackgroundOpacity(0.5);
		m_view->setCentralWidget(new QLabel("Workspace"));
	}
	else if (node == m_roiNode)
	{
		m_view->setBackgroundOpacity(0.5);
		m_view->setCentralWidget(new QLabel("ROI"));
	}
	else
		// root
		// app
	{
		m_view->setBackgroundOpacity(1);
		m_view->clearFilter();
		m_view->clearCentralWidget();
	}
}
