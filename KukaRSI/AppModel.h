#pragma once
#include "ModelBase.h"
#include "RobotKuka.h"
#include "RobotConfig.h"
#include "Config.h"
#include "GroupParameter.h"
#include "NumericalParameter.h"
#include "StringParameter.h"
#include "Matrix4x4Parameter.h"

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
    void disconnectFromRobot();
    void startRobot();
    void stopRobot();
    void stopMove();

    void release() override;

    void getCurrentPose(double currentPose[6]) const;
    void getCurrentDelta(double currentDelta[6]) const;

public slots:
    void onMovementPressed(RobotKuka::MovementDirection direction);
    void onMovementReleased(RobotKuka::MovementDirection direction);

private slots:
    void onErrorOccurred(const QString& message);
    void onRobotConnected();
    void onRobotDisconnected();
    
private:
    void setupConfig(const RobotConfig* config);
    bool setupAddress(const RobotConfig* config);

signals:
	void connectionTimeRemainingChanged(int seconds);
    void robotStateChanged(RobotKuka::Status status);
    void robotConnected();
    void robotDisconnected();
    void robotStarted();
    void robotStopped();
    void errorOccurred(const QString& message);

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
    Matrix4x4Parameter m_toolParameter;
    GroupParameter m_connectionGroup;
    NumericalParameter m_connectionTimeoutParameter;
    GroupParameter m_uiGroup;
    NumericalParameter m_freshRateParameter;
};
