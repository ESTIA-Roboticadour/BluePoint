#pragma once
#include "ModelBase.h"
#include "RobotKuka.h"
#include "RobotConfig.h"

#include <QObject>

class AppModel : public ModelBase
{
    Q_OBJECT

public:
    AppModel(const RobotConfig* config, QObject* parent = nullptr);
    ~AppModel();

    const Config* getConfig() const;
    const Config* getUiConfig() const;

    // Méthodes utilitaires
    void connectToRobot();
    void disconnectFromRobot();
    void startRobot();
    void stopRobot();
    void stopMove();

    void release() override;

signals:
    void robotStateChanged();
    void robotPoseChanged(const QMatrix4x4& pose);
    void errorOccurred(const QString& message);

private slots:
    void onPoseUpdated(const QMatrix4x4& pose);
    void onErrorOccurred(const QString& message);

private:
    RobotKuka* m_robot;
    Config m_config;
    Config m_uiConfig;
};
