#pragma once
#include "TransparentScrollArea.h"
#include "ParametersView.h"
#include "Config.h"
#include "RobotKuka.h"

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QMap>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>

class AppView : public TransparentScrollArea
{
    Q_OBJECT

public:
    explicit AppView(QWidget* parent = nullptr);

    void setConfig(const Config* config);

public slots:
    void updatePose(double positions[6]);
    void updateDelta(double positions[6]);

    void onRobotStateChanged(RobotKuka::Status status);
    void onRobotConnected();
    void onRobotDisconnected();
    void onRobotStarted();
    void onRobotStopped();
    void onConnectionTimeRemainingChanged(int seconds);
    void onFreshRateChanged(double freshRateHz);

private slots:
    void onConnectButtonClicked();
	void onDisconnectButtonClicked();
	void onStartButtonClicked();
	void onStopButtonClicked();

    void handleMovementPressed();
    void handleMovementReleased();

    void refreshUI();

private:
    void setupUI();
    void createMovementButtons(QGridLayout* layout);
    void setupMovementSignals(QPushButton* button, RobotKuka::MovementDirection direction) const;
    QGroupBox* createPoseGroup(const QString& title, QList<QLineEdit*>& listToFeed);
    void setConnectionLabelText(const QString& text);
    void clearConnectionLabelText();
    void setTimerIntervale(int freshRateHz);

signals:
    void connectButtonClicked();
    void disconnectButtonClicked();
    void startButtonClicked();
    void stopButtonClicked();

    void movementPressed(RobotKuka::MovementDirection direction);
    void movementReleased(RobotKuka::MovementDirection direction);

    void requestNewPose();
    void requestNewDelta();

private:
    QPushButton* m_connectButton{ nullptr };
    QPushButton* m_disconnectButton{ nullptr };
    QPushButton* m_startButton{ nullptr };
    QPushButton* m_stopButton{ nullptr };
    ParametersView* m_parametersView{ nullptr };
    QVBoxLayout* m_connectionLayout{ nullptr };
    QList<QLineEdit*> m_poseLineEdits;
    QList<QLineEdit*> m_deltaLineEdits;
    QMap<RobotKuka::MovementDirection, QPushButton*> m_movementButtons;
    QLabel* m_statusLabel{ nullptr };
    QLabel* m_connectionLabel{ nullptr };

    QTimer m_uiTimer;
    double m_freshRateHz;
};
