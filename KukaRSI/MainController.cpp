#include "MainController.h"
#include "AppStore.h"

#include <QMessageBox>

MainController::MainController(MainModel* model, MainWindow* view, QObject* parent) :
	WindowControllerBase(model, view, parent),
	m_view(view),
	m_model(model),
	m_tempConfig(nullptr),
	m_tree(nullptr),
	m_rootNode(nullptr),
	m_configurationNode(nullptr),
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
	m_configurationNode = m_rootNode->getChild(0);
	m_appNode = m_rootNode->getChild(1);
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
	if (node == m_configurationNode)
		navigateConfigurationNode();

	if (node == m_appNode)
		navigateAppNode();

	else
		// root
		// app
	{
		opacity = 1.0;
		m_view->clearCentralWidget();
	}
	m_view->setBackgroundOpacity(opacity);
}


void MainController::navigateConfigurationNode() 
{
}

void MainController::navigateAppNode() 
{
}
