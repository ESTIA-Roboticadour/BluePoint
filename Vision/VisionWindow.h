#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VisionWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VisionWindowClass; };
QT_END_NAMESPACE

class VisionWindow : public QMainWindow
{
    Q_OBJECT

public:
    VisionWindow(QWidget *parent = nullptr);
    ~VisionWindow();

private:
    Ui::VisionWindowClass *m_ui;
};
