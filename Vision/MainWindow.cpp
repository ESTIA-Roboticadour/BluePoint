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
	return m_ui->navigationLayoutWidget->getTree();
}

void MainWindow::setCentralWidget(QWidget* widget) const
{
	m_ui->navigationLayoutWidget->setCentralWidget(widget);
}
