#pragma once

#include "ui_MainWindow.h"
#include "WindowBase.h"
#include "NavigationTree.h"
#include "LayeredWidget.h"
#include "LogoWidget.h"
#include "LogWidget.h"

#include <QWidget>
#include <QtWidgets/QMainWindow>
#include <QCloseEvent>
#include <QColor>
#include <QSplitter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; };
QT_END_NAMESPACE

class MainWindow : public WindowBase
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    NavigationTree* getTree() const;

    void setCentralWidget(QWidget* widget, bool deleteOld=true) const;
    void clearCentralWidget(bool deleteOld = true) const;

    void hideBackground();
    void showBackground();
    void setBackgroundVisibility(bool visible);

    qreal backgroundOpacity() const;
    void  setBackgroundOpacity(qreal alpha);  // 0..1

    void clearFilter();
	void setFilterColor(const QColor& c, qreal alpha);

private:
    Ui::MainWindowClass *m_ui;
	LayeredWidget* m_layeredWidget;
	LogoWidget* m_logoWidget;
    LogWidget* m_logWidget;
    QSplitter* m_splitter;
};
