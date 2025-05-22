#pragma once

#include "ui_LightControlWindow.h"
#include <QtWidgets/QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QStringList>
#include <QString>
#include <QCloseEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class LightControlWindowClass; };
QT_END_NAMESPACE

class LightControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LightControlWindow(QWidget* parent = nullptr);
    ~LightControlWindow();

    void setAvailablePorts(const QStringList& ports);
    void setModuleInfo(int id, int version);
    void setRelayState(int relayIndex, bool on);
    void setSelectedPort(int index);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onPortSelectedChanged(int index);

private:
    void clearModuleInfo() const;
	void setButtonsEnabled(bool enabled);

signals:
    void portSelectedChanged(const QString& portName);
    void relayButtonPressed(int index);
    void closeRequest();

private:
    Ui::LightControlWindowClass* m_ui;

    QVector<QPushButton*> m_relayButtons;
    QVector<QLabel*> m_ledIndicators;
};
