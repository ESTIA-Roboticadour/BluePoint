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
    void synchronizeIO(bool inputs[16], bool outputs[16]);

    void onRobotStateChanged(RobotKuka::Status status);
    void onRobotBehaviourChanged(RobotKuka::Behaviour behaviour);
    void onRobotConnected();
    void onRobotDisconnected();
    void onRobotStarted();
    void onRobotStopped();
    void onConnectionTimeRemainingChanged(quint16 seconds);
    void onFreshRateChanged(double freshRateHz);

private slots:
    void onConnectButtonClicked();
	void onDisconnectButtonClicked();
	void onStartButtonClicked();
	void onStopButtonClicked();

    void refreshUI();

private:
    void setupUI();
    void createMovementButtons(QGridLayout* layout);
    void createJointControlButtons(QGridLayout* layout);
    void createIOBtns(QGridLayout* layout);
    QGroupBox* createPoseGroup(const QString& title, QList<QLineEdit*>& listToFeed);
    void switchConnectBtnToCancelBtn();
    void switchCancelBtnToConnectBtn();
    void setConnectionLabelText(const QString& text);
    void clearConnectionLabelText();
    void setTimerIntervale(double freshRateHz);

signals:
    void connectButtonClicked();
    void cancelConnectButtonClicked();
    void disconnectButtonClicked();
    void startButtonClicked();
    void stopButtonClicked();

    void cartesianMovementPressed(RobotKuka::MovementDirection direction);
    void cartesianMovementReleased(RobotKuka::MovementDirection direction);
    void articularMovementPressed(RobotKuka::Joint joint, bool positive);
    void articularMovementReleased(RobotKuka::Joint joint);
    void inputToggled(RobotKuka::IOInput input, bool enabled);
    void outputToggled(RobotKuka::IOOutput output, bool enabled);

    void requestNewPose();
    void requestNewDelta();

private:
    QPushButton* m_connectButton{ nullptr };
    QPushButton* m_disconnectButton{ nullptr };
    QPushButton* m_startButton{ nullptr };
    QPushButton* m_stopButton{ nullptr };
    ParametersView* m_parametersView{ nullptr };
    QVBoxLayout* m_connectionLayout{ nullptr };
    QLabel* m_statusLabel{ nullptr };
    QLabel* m_behaviourLabel{ nullptr };
    QLabel* m_connectionLabel{ nullptr };
    QList<QLineEdit*> m_poseLineEdits;
    QList<QLineEdit*> m_deltaLineEdits;
    QMap<RobotKuka::MovementDirection, QPushButton*> m_movementButtons;
    QList<QPushButton*> m_jointButtons;
    QList<QPushButton*> m_ioButtons;

    QTimer m_uiTimer;
    double m_freshRateHz;
};
