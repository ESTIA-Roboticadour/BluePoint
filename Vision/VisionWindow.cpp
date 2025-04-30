#include "VisionWindow.h"

VisionWindow::VisionWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::VisionWindowClass()),
    m_boolParameter("beau gosse", true, this)
{
    m_ui->setupUi(this);

    m_ui->boolParameterWidget->setFrom(&m_boolParameter);
}

VisionWindow::~VisionWindow()
{
    delete m_ui;
}
