#pragma once
#include "RobotConfig.h"
#include <QObject>
#include <QVector3D>
#include <QMatrix4x4>
#include <QUdpSocket>
#include <QHostAddress>

class RobotKuka : public QObject
{
    Q_OBJECT

public:
    enum Status
    {
        Ready,
        WaitingRobotConnection,
        Connected,
        Moving,
        Error
    };
    Q_ENUM(Status)

    enum MovementDirection {
        Up,
        Down,
        Left,
        Right,
        Forward,
        Backward
    };
    Q_ENUM(MovementDirection)

    inline static QString toQString(MovementDirection direction) {
        switch (direction) {
        case MovementDirection::Up: return "UP";
        case MovementDirection::Down: return "DOWN";
        case MovementDirection::Left: return "LEFT";
        case MovementDirection::Right: return "RIGHT";
        case MovementDirection::Forward: return "FORWARD";
        case MovementDirection::Backward: return "BACKWARD";
        default: return "";
        }
    }

    inline static QString toQString(Status status) {
        switch (status) {
        case Status::Ready: return "Ready";
        case Status::WaitingRobotConnection: return "Waiting Robot Connection";
        case Status::Connected: return "Connected";
        case Status::Moving: return "Moving";
        case Status::Error: return "Error";
        default: return "";
        }
    }

    explicit RobotKuka(QObject* parent = nullptr);
    ~RobotKuka();

	Status getStatus() const { return m_status; };

    // Connexion / déconnexion
    
    // Open an udp client to the given address and port. When data are received from the robot, connected() signal is emitted. Timeout is in seconds.
    void connectToRobot(const QHostAddress& hostAddress, int port, int timeout);
    void disconnectFromRobot();
    bool isConnected() const;

    // Démarrage / arrêt
    void start();
    void stop();
    bool isRunning() const;

    // Déplacement manuel
    void move(const QString& direction);
    void stopMovement();

    // Pose & Delta
    void getCurrentPose(double currentPose[6]) const;
    void getCurrentDelta(double currentDelta[6]) const;

private:
	void deleteUdpClient();
	void setStatus(Status status);

signals:
	void statusChanged(Status status);
    void connected();
    void disconnected();
    void started();
    void stopped();
    void errorOccurred(const QString& message);
    void connectionTimeRemainingChanged(int seconds);

private:
	Status m_status;
    bool m_isConnected = false;
    bool m_isRunning = false;
    QMatrix4x4 m_pose;
	QHostAddress m_hostAddress;
    int m_port;
    QUdpSocket* m_udpClient;

    double m_currentPose[6]; // Positions X, Y, Z, A, B, C
	double m_currentDelta[6]; // Positions dX, dY, dZ, dA, dB, dC
};
