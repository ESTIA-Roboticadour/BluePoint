#include "VisionWindow.h"

VisionWindow::VisionWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::VisionWindowClass())
{
    m_ui->setupUi(this);
}

VisionWindow::~VisionWindow()
{
    delete m_ui;
}
