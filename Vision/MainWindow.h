#pragma once

#include "ui_MainWindow.h"
#include "WindowBase.h"
#include "NavigationTree.h"

#include <QWidget>
#include <QtWidgets/QMainWindow>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; };
QT_END_NAMESPACE

class MainWindow : public WindowBase
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    NavigationTree* getTree() const;
    void setCentralWidget(QWidget* widget) const;

private:
    Ui::MainWindowClass *m_ui;
};
