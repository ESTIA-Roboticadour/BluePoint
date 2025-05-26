#include "MainWindow.h"
#include "NavigationTree.h"

MainWindow::MainWindow(QWidget* parent) :
	WindowBase(parent),
	m_ui(new Ui::MainWindowClass())
{
	m_ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete m_ui;
}

NavigationTree* MainWindow::getTree() const
{
	return m_ui->appLayoutWidget->getTree();
}

void MainWindow::setCentralWidget(QWidget* widget, bool deleteOld) const
{
	m_ui->appLayoutWidget->setCentralWidget(widget, deleteOld);
}

void MainWindow::clearCentralWidget(bool deleteOld) const
{
	m_ui->appLayoutWidget->clearCentralWidget( deleteOld);
}

void MainWindow::hideBackground()
{
	m_ui->appLayoutWidget->hideBackground();
}

void MainWindow::showBackground()
{
	m_ui->appLayoutWidget->showBackground();
}

void MainWindow::setBackgroundVisibility(bool visible)
{
	if (visible)
		showBackground();
	else
		hideBackground();
}

qreal MainWindow::backgroundOpacity() const
{
	return m_ui->appLayoutWidget->backgroundOpacity();
}

void MainWindow::setBackgroundOpacity(qreal alpha)
{
	m_ui->appLayoutWidget->setBackgroundOpacity(alpha);
}

void MainWindow::clearFilter()
{
	m_ui->appLayoutWidget->clearFilter();
}

void MainWindow::setFilter(const QColor& c, qreal alpha)
{
	m_ui->appLayoutWidget->setFilter(c, alpha);
}
