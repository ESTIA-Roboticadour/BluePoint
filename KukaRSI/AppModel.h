#pragma once
#include "ModelBase.h"
#include "RobotKuka.h"
#include "RobotConfig.h"
#include "Config.h"
#include "GroupParameter.h"
#include "NumericalParameter.h"
#include "StringParameter.h"
#include "EulerFrameParameter.h"

#include <QObject>
#include <QHostAddress>

class AppModel : public ModelBase
{
    Q_OBJECT

public:
    AppModel(const RobotConfig* config, QObject* parent = nullptr);
    ~AppModel();

    const Config* getConfig() const;

    // Méthodes utilitaires
    void connectToRobot();
    void cancelConnectToRobot();
    void disconnectFromRobot();
    void startRobot();
    void stopRobot();
    void stopMove();
    RobotKuka::Status getRobotStatus() const;
    RobotKuka::RobotState getRobotState() const;

    void release() override;

    void getCurrentPose(double currentPose[6]) const;
    void getCurrentDelta(double currentDelta[6]) const;

public slots:
    void onCartesianMovementPressed(RobotKuka::MovementDirection direction);
    void onCartesianMovementReleased(RobotKuka::MovementDirection direction);
    void onArticularMovementPressed(RobotKuka::Joint joint, bool positive);
    void onArticularMovementReleased(RobotKuka::Joint joint);
    void onInputToggled(RobotKuka::IOInput input, bool enabled);
    void onOutputToggled(RobotKuka::IOOutput output, bool enabled);
    void onJoggingModeChanged(bool isCartesian);

private slots:
    void onErrorOccurred(const QString& message);
    void onRobotConnected();
    void onRobotDisconnected();
    void onRobotFailedToConnect();
    
private:
    void setupConfig(const RobotConfig* config);
    bool setupAddress(const RobotConfig* config);

signals:
    void robotStatusChanged(RobotKuka::Status status);
    void robotStateChanged(RobotKuka::RobotState state);
    void robotConnected();
    void robotDisconnected();
    void robotStarted();
    void robotStopped();
    void errorOccurred(const QString& message);
	void connectionTimeRemainingChanged(quint16 seconds);

	void freshRateChanged(double freshRate);

private:
    RobotKuka* m_robot;
    Config m_config;
    QHostAddress m_hostAddress;
    int m_port;

    GroupParameter m_robotGroup;
	StringParameter m_addressParameter;
	NumericalParameter m_portParameter;
    NumericalParameter m_speedParameter;
    NumericalParameter m_accelParameter;
    EulerFrameParameter m_toolParameter;
    GroupParameter m_connectionGroup;
    NumericalParameter m_connectionTimeoutParameter;
    GroupParameter m_uiGroup;
    NumericalParameter m_freshRateParameter;
};
