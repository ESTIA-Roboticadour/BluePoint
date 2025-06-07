#pragma once
#include "ModelBase.h"
#include "RobotKuka.h"
#include "RobotConfig.h"

#include <QObject>

class AppModel : public ModelBase
{
    Q_OBJECT

public:
    AppModel(RobotKuka* robot, const RobotConfig& config, QObject* parent = nullptr);
    ~AppModel();

    RobotKuka* robot() const;
    const RobotConfig& config() const;

    // Méthodes utilitaires
    void connectToRobot();
    void disconnectFromRobot();
    void startRobot();
    void stopRobot();

    void release() override;

signals:
    void robotStateChanged();
    void robotPoseChanged(const QMatrix4x4& pose);
    void errorOccurred(const QString& message);

private:
    RobotKuka* m_robot;
    RobotConfig m_config;

private slots:
    void onPoseUpdated(const QMatrix4x4& pose);
    void onErrorOccurred(const QString& message);
};
