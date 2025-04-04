#pragma once

#include "ui_CameraHeightWindowUI.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QString>

class CameraHeightWindow : public QMainWindow
{
    Q_OBJECT

public:
    CameraHeightWindow(QWidget *parent = nullptr);
    ~CameraHeightWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

public slots:
    void setFovText(const QString& text);
    void setWidthText(const QString& text);
    void setHeightText(const QString& text);

    void onErrorThrowed(const QString& error, const QString& errorMessage);

signals:
    void closing();
    void fovLabelTextChanged(const QString& text);
    void widthLabelTextChanged(const QString& text);

private:
    Ui::CameraHeightWindowClass *m_ui;
};
