#include "CameraHeightWindow.h"

CameraHeightWindow::CameraHeightWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::CameraHeightWindowClass())
{
    m_ui->setupUi(this);

    setFovText("0.0");
    setWidthText("0.0");

    connect(m_ui->fovLineEdit, &QLineEdit::textEdited, this, &CameraHeightWindow::fovLabelTextChanged);
    connect(m_ui->widthLineEdit, &QLineEdit::textEdited, this, &CameraHeightWindow::widthLabelTextChanged);
}

CameraHeightWindow::~CameraHeightWindow()
{
    delete m_ui;
}

void CameraHeightWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();
    emit closing();
}

void CameraHeightWindow::setFovText(const QString& text)
{
    m_ui->fovLineEdit->setText(text);
}

void CameraHeightWindow::setWidthText(const QString& text)
{
    m_ui->widthLineEdit->setText(text);
}

void CameraHeightWindow::setHeightText(const QString& text)
{
    m_ui->heightLabel->setText(text);
}

void CameraHeightWindow::onErrorThrowed(const QString& error, const QString& errorMessage)
{
    m_ui->statusBar->showMessage(error + ": " + errorMessage, 4000);
}
