#include "GotoWindow.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>

GotoWindow::GotoWindow(QWidget* parent) : WindowBase(parent)
{
	setWindowTitle("GO TO");
	resize(400, 300);
	setupUI();
}

void GotoWindow::setupUI()
{
    // Create a central widget
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    /* ---- vue des paramètres ---- */
    QGroupBox* box = new QGroupBox("Parameters", central);
    box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    auto* boxLayout = new QVBoxLayout(box);

	m_parametersView = new ParametersView(box);
	//m_parametersView->setReadOnly(true); // Set to false to allow editing
	m_parametersView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	m_parametersView->setAlignment(ParametersView::Alignment::All);
	boxLayout->addWidget(m_parametersView);

    QFrame* horizontalLine = new QFrame(central);
    horizontalLine->setFrameShape(QFrame::HLine);
    horizontalLine->setFrameShadow(QFrame::Sunken);

    QPushButton* gotoButton = new QPushButton("GO TO", central);

    mainLayout->addWidget(box);
    mainLayout->addWidget(horizontalLine);
    mainLayout->addWidget(gotoButton);
    mainLayout->addStretch();

    setCentralWidget(central); // This is the key line!
}

void GotoWindow::setConfig(const Config* config)
{
	if (config)
	{
		m_parametersView->setParameters(config->getParameters());
	}
	else
	{
		m_parametersView->clear();
	}
}
