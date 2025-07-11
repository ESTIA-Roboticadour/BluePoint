#pragma once
#include "TransparentScrollArea.h"
#include "ParametersView.h"
#include "Config.h"
#include "RobotKuka.h"
#include "GotoWindow.h"
#include "GroupParameter.h"
#include "ListParameter.h"
#include "EulerFrameParameter.h"
#include "NumericalParameter.h"
#include "BoolParameter.h"
#include "StringParameter.h"

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QTabWidget>
#include <QMap>
#include <QTimer>
#include <QKeyEvent>
#include <QSet>

class AppView : public TransparentScrollArea
{
    Q_OBJECT

public:
    explicit AppView(QWidget* parent = nullptr);

    void setConfig(const Config* config);

public slots:
    void updatePose(double positions[6]);
    void updateDelta(double positions[6]);
    void updateIO(bool inputs[16], bool outputs[16]);
    void updateJoggingMode(bool isJoggingCartesian);
    void updateIsInRobotBase(bool isInRobotBase);

    void onRobotStatusChanged(RobotKuka::Status status);
    void onRobotStateChanged(RobotKuka::RobotState state);
    void onRobotConnected();
    void onRobotDisconnected();
    void onRobotStarted();
    void onRobotStopped();
    void onConnectionTimeRemainingChanged(quint16 seconds);
    void onFreshRateChanged(double freshRateHz);

private slots:
    void onConnectButtonClicked();
    void onCancelButtonClicked();
	void onDisconnectButtonClicked();
	void onStartButtonClicked();
	void onStopButtonClicked();
    void onBaseComboBoxChanged(int index);
    void onMoveTabChanged(int index);
    void onGotoButtonClicked();

    void refreshUI();

    void onMinChanged(double value);
    void onMaxChanged(double value);
    void onNumChanged(double value);

private:
    void setupUI();
    void createMovementButtons(QGridLayout* layout);
    void createJointControlButtons(QGridLayout* layout);
    void createIOBtns(QGridLayout* layout);
    QGroupBox* createPoseGroup(const QString& title, QList<QLabel*>& labelsToFeed, QList<QLineEdit*>& lineEditsToFeed);
    void switchConnectBtnToCancelBtn();
    void switchCancelBtnToConnectBtn();
    void setConnectionLabelText(const QString& text);
    void clearConnectionLabelText();
    void setMoveAndIOButtonsEnabled(bool enabled) const;
    void setMoveAndIOButtonsChecked(bool checked) const;
    void setTimerIntervale(double freshRateHz);
	void setIsJoggingInCartesian(bool isJoggingInCartesian);
	void setIsMovingInRobotBase(bool isMovingInRobotBase);

signals:
    void connectButtonClicked();
    void cancelConnectButtonClicked();
    void disconnectButtonClicked();
    void startButtonClicked();
    void stopButtonClicked();

    void cartesianMovementPressed(RobotKuka::Axis axis, bool positive);
    void cartesianMovementReleased(RobotKuka::Axis axis);
    void articularMovementPressed(RobotKuka::Joint joint, bool positive);
    void articularMovementReleased(RobotKuka::Joint joint);
    void outputClicked(RobotKuka::IOOutput output, bool checked);

    void refreshUiRequest(bool isCartesian);

    void joggingCartesianRequest();
    void joggingArticularRequest();

    void joggingInRobotBaseRequest();
    void joggingInRobotToolRequest();

private:
    QPushButton* m_connectButton{ nullptr };
    QPushButton* m_disconnectButton{ nullptr };
    QPushButton* m_startButton{ nullptr };
    QPushButton* m_stopButton{ nullptr };
    ParametersView* m_parametersView{ nullptr };
    QVBoxLayout* m_connectionLayout{ nullptr };
    QLabel* m_statusLabel{ nullptr };
    QLabel* m_robotStateLabel{ nullptr };
    QLabel* m_connectionLabel{ nullptr };
    QComboBox* m_robotBaseComboBox;
    QTabWidget* m_joggingTab;
    QPushButton* m_gotoButton;
    QList<QLabel*> m_poseLabels;
    QList<QLabel*> m_deltaLabels;
    QList<QLineEdit*> m_poseLineEdits;
    QList<QLineEdit*> m_deltaLineEdits;
    QList<QPushButton*> m_axisButtons;
    QList<QPushButton*> m_jointButtons;
    QList<QPushButton*> m_ioButtons;
    GotoWindow* m_gotoWindow{ nullptr };

    QTimer m_uiTimer;
    double m_freshRateHz;
    bool m_isReadyToMove;
    bool m_isJoggingCartesian;
    bool m_isMovingInRobotBase;
    int  m_previousJoggingTabsSelected;
    int m_previousBaseSelected;

    Config m_gotoConfig;
    GroupParameter m_movementGroupParameter;
    GroupParameter m_positionGroupParameter;
    ListParameter<QString> m_movementTypesParameter;
    ListParameter<QString> m_movementAbsoluteRelativeParameter;
    ListParameter<QString> m_movementBaseParameter;
	EulerFrameParameter m_eulerFrameParameter;
    NumericalParameter m_numParamMin;
    NumericalParameter m_numParamMax;
    NumericalParameter m_numParam;
	BoolParameter m_boolParam;
	StringParameter m_stringParam;
};
