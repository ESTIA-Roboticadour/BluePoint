#pragma once
#include "RobotConfig.h"
#include <QObject>
#include <QVector3D>
#include <QMatrix4x4>

class RobotKuka : public QObject
{
    Q_OBJECT

public:
    explicit RobotKuka(QObject* parent = nullptr);
    virtual ~RobotKuka();

    // Connexion / déconnexion
    virtual void connectToRobot(const RobotConfig& config);
    virtual void disconnectFromRobot();
    virtual bool isConnected() const;

    // Démarrage / arrêt
    virtual void start();
    virtual void stop();
    virtual bool isRunning() const;

    // Déplacement manuel
    virtual void move(const QString& direction);
    virtual void stopMovement();

    // Pose et position
    virtual QMatrix4x4 getCurrentPose() const;
    virtual QVector3D getCurrentPosition() const;
    virtual QVector3D getCurrentOrientationEuler() const;

signals:
    void connected();
    void disconnected();
    void started();
    void stopped();
    void poseUpdated(const QMatrix4x4& pose);
    void errorOccurred(const QString& message);

protected:
    bool m_connected = false;
    bool m_running = false;
    QMatrix4x4 m_pose;
};
