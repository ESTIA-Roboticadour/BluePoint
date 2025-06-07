#include "MainController.h"
#include "AppStore.h"

#include <QMessageBox>

MainController::MainController(MainModel* model, MainWindow* view, QObject* parent) :
	WindowControllerBase(model, view, parent),
	m_view(view),
	m_model(model)
{
	setupConnections();
	updateCentralWidget(m_model->tree()->currentNode());
}

MainController::~MainController()
{
	if (m_model)
		m_model->deleteLater();
	if (m_view)
		m_view->deleteLater();
}

void MainController::setupConnections()
{
	connect(m_model, &MainModel::released, this, &MainController::onModelReleased);
	connect(m_model, &MainModel::warning, this, &MainController::onModelWarning);

	connect(m_model->tree(), &NavigationTree::navigationRequest, this, &MainController::onNavigationRequest);
	connect(m_model->tree(), &NavigationTree::currentNodeChanged, this, &MainController::onNavigationDone);
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

void MainController::onModelWarning(const QString& title, const QString& message)
{
	QMessageBox::warning(m_view, title, message);
}

void MainController::onNavigationDone(NavigationNode* node)
{
	updateCentralWidget(node);
}

void MainController::updateCentralWidget(NavigationNode* node)
{
	QWidget* w = m_model->buildCentralWidget(node, m_view);
	if (w)
	{
		m_view->setBackgroundOpacity(0.5);
		m_view->setCentralWidget(w);
	}
	else
	{
		m_view->setBackgroundOpacity(1);
		m_view->clearCentralWidget();
	}
}
