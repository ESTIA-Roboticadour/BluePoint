#include "MainWindow.h"
#include "NavigationTree.h"

MainWindow::MainWindow(QWidget* parent) :
	WindowBase(parent),
	m_ui(new Ui::MainWindowClass()),
	m_layeredWidget(new LayeredWidget(this)),
	m_logoWidget(new LogoWidget()),
	m_logWidget(new LogWidget(this)),
	m_splitter(new QSplitter(Qt::Vertical, this))
{
	m_ui->setupUi(this);

	// --- 1) préparation du LayeredWidget de fond ---
	m_layeredWidget->setBackgroundWidget(m_logoWidget);

	m_logoWidget->setLogoPath(":/VisionWindow/Resources/icon.png");

	// --- 2) construction du splitter (haut : layered, bas : logs) ---
	m_splitter->addWidget(m_layeredWidget);
	m_splitter->addWidget(m_logWidget);

	const int h = height() > 0 ? height() : 800;   // valeur de secours
	m_splitter->setSizes({ int(h * 0.8), int(h * 0.2) });

	// (facultatif) rendre le panneau log repliable :
	m_splitter->setCollapsible(1, true);

	// ratios initiaux : 80 % / 20 % (ajustez à votre goût)
	m_splitter->setStretchFactor(0, 4);   // index 0 = 4 parts
	m_splitter->setStretchFactor(1, 1);   // index 1 = 1 part

	// --- 3) place le splitter dans la zone centrale du NavigationLayoutWidget ---
	m_ui->navigationLayoutWidget->setCentralWidget(m_splitter);
}

MainWindow::~MainWindow()
{
	m_logoWidget->deleteLater();
	delete m_ui;
}

NavigationTree* MainWindow::getTree() const
{
	return m_ui->navigationLayoutWidget->getTree();
}

void MainWindow::setCentralWidget(QWidget* widget, bool deleteOld) const
{
	m_layeredWidget->setForegroundWidget(widget, deleteOld);
}

void MainWindow::clearCentralWidget(bool deleteOld) const
{
	m_layeredWidget->setForegroundWidget(nullptr, deleteOld);
}

void MainWindow::hideBackground()
{
	m_logoWidget->hide();
}

void MainWindow::showBackground()
{
	m_logoWidget->show();
}

void MainWindow::setBackgroundVisibility(bool visible)
{
	if (visible)
		m_layeredWidget->show();
	else
		m_layeredWidget->hide();
}

qreal MainWindow::backgroundOpacity() const
{
	return m_layeredWidget->backgroundOpacity();
}

void MainWindow::setBackgroundOpacity(qreal alpha)
{
	m_layeredWidget->setBackgroundOpacity(alpha);
}

void MainWindow::clearFilter()
{
	m_layeredWidget->clearFilter();
}

void MainWindow::setFilterColor(const QColor& c, qreal alpha)
{
	m_layeredWidget->setFilter(c, alpha);
}
