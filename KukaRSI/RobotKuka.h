#pragma once
#include "RobotConfig.h"
#include "UdpClient.h"
#include "RsiTrame.h"

#include <QObject>
#include <QHostAddress>
#include <QTimer>
#include <memory>

class RobotKuka : public QObject
{
    Q_OBJECT

#pragma region enums
public:
    enum class Status
    {
        None,
        Ready,
        WaitingRobotConnection,
        Connected,
        ReadyToMove,
        Error
    };
    Q_ENUM(Status)

    enum class RobotState
    {
        None,
        DoNothing,
        MoveCartesianLIN,
        MoveJoint,
        StopMove
    };
    Q_ENUM(RobotState)

    enum Axis
    {
		X,
		Y,
		Z,
		A,
		B,
		C
    };
    Q_ENUM(Axis)

    enum Joint
    {
        J1,
        J2,
        J3,
        J4,
        J5,
        J6,
    };
    Q_ENUM(Joint)

    //enum MovementDirection {
    //    None = 0x00,        // 0000 0000  |   0
    //    Up = 0x01,          // 0000 0001  |   1
    //    Down = 0x02,        // 0000 0010  |   2
    //    Left = 0x04,        // 0000 0100  |   4
    //    Right = 0x08,       // 0000 1000  |   8
    //    Forward = 0x10,     // 0001 0000  |  16
    //    Backward = 0x20     // 0010 0000  |  32
    //};
    //Q_ENUM(MovementDirection)
    //Q_DECLARE_FLAGS(MovementFlags, MovementDirection)
    //Q_FLAG(MovementFlags)

    enum IOInput
    {
        I01,
        I02,
        I03,
        I04,
        I05,
        I06,
        I07,
        I08,
        I09,
        I10,
        I11,
        I12,
        I13,
        I14,
        I15,
        I16,
    };
    Q_ENUM(IOInput)

    enum IOOutput
    {
        O01,
        O02,
        O03,
        O04,
        O05,
        O06,
        O07,
        O08,
        O09,
        O10,
        O11,
        O12,
        O13,
        O14,
        O15,
        O16,
    };
    Q_ENUM(IOOutput)

    inline static QString toString(Status status) {
        switch (status) {
        case Status::None: return "None";
        case Status::Ready: return "Ready";
        case Status::WaitingRobotConnection: return "Waiting Robot Connection";
        case Status::Connected: return "Connected";
        case Status::ReadyToMove: return "Ready to Move";
        case Status::Error: return "Error";
        default: return "";
        }
    }

    inline static QString toString(RobotState behaviour) {
        switch (behaviour) {
        case RobotState::None: return "None";
        case RobotState::DoNothing: return "Do Nothing";
        case RobotState::MoveCartesianLIN: return "Move Cartesian LIN";
        case RobotState::MoveJoint: return "Move Joint";
        case RobotState::StopMove: return "Stop Move";
        default: return "";
        }
    }

    inline static QString toString(Axis axis) {
        switch (axis) {
        case Axis::X: return "X";
        case Axis::Y: return "Y";
        case Axis::Z: return "Z";
        case Axis::A: return "A";
        case Axis::B: return "B";
        case Axis::C: return "C";
        default: return "";
        }
    }

#pragma endregion

public:
    explicit RobotKuka(QObject* parent = nullptr);
    ~RobotKuka();

	Status getStatus() const { return m_status; };
    RobotState getRobotState() const { return m_robotState; }
    void setRobotBase(bool isInRobotBase);

    // Connexion / déconnexion
    
    // Open an udp client to the given address and port. When data are received from the robot, connected() signal is emitted. Timeout is in seconds.
    void connectToRobot(const QHostAddress& hostAddress, quint16 port, quint32 timeout);
    void disconnectFromRobot();
	bool isConnected() const { return m_isConnected; }
	bool isReadyToMove() const { return m_status == Status::ReadyToMove; }

    void abortConnection();

    // Démarrage / arrêt
    void start();
    void stop();

    // Déplacement manuel
    void moveAxis(Axis axis, bool positive);
    void moveJoint(Joint joint, bool positive);
    void stopMove();

    // IO
    void setInput(IOInput input, bool enabled);
    void setOutput(IOOutput output, bool enabled);

    // Pose & Delta
    void getCurrentPose(double currentPose[6]) const;
    void getCurrentDelta(double currentDelta[6]) const;
    void resetCurrentDelta();

private slots:
    void onUdpOpened(const QHostAddress& hostAddress, quint16 port);
    void onUdpFailedToOpen(const QHostAddress& hostAddress, quint16 port);
    void onUdpClosed();

    void onInitialDatagramReceived(const QByteArray& data, const QHostAddress& sender, quint16 senderPort);
    void onConnectionTimeoutTick();
    void onDatagramReceived(const QByteArray& data, const QHostAddress& sender, quint16 senderPort);
    void onWatchdogTimeout();

private:
	void closeUdpClient();
    void setStatus(Status status);
    void setRequestState(RobotState newState) { m_robotRequestState = newState; }
    void setRobotState(RobotState state);
    void parseReceivedData(const QString& data);
    QString ipocFromTrame(const QString& trame);
    void positionFromTrame(const QString& trame, double pos[6]);

    void requestAutomate();
    void stateAutomate();
    void sendTrame();

signals:
    void statusChanged(Status status);
    void robotStateChanged(RobotState status);
    void connected();
    void disconnected();
    void started();
    void stopped();
    void failedToConnect();
    void errorOccurred(const QString& message);
    void connectionTimeRemainingChanged(quint16 seconds);

private:
    Status m_status;
    RobotState m_robotRequestState;
    RobotState m_robotState;
    bool m_isConnected;
    bool m_disconnectRequest;

    UdpClient* m_udpClient;
    quint16 m_connectionTimeout;
    quint16 m_connectionTimeRemaining;
    QTimer* m_connectionTimer;
    bool m_abortConnectionRequest;
    bool m_initialDatagramReceived;

    QHostAddress m_robotAddress;
    quint16 m_robotPort;
    QTimer* m_watchdogTimer;
    const int WATCHDOG_TIMEOUT_MS = 100; // 20 ms

    inline static const double m_ZEROS[6] = { 0., 0., 0., 0., 0., 0. };
    double m_currentPose[6]; // Positions X, Y, Z, A, B, C
	double m_currentDelta[6]; // Positions dX, dY, dZ, dA, dB, dC
    double m_deltaStep;
    Axis m_currentAxis;
	Joint m_currentJoint;
    bool m_isMovePositive;
	bool m_isMovingInRobotBase; // true = BASE, false = TOOL

    RsiTrame m_rsiTrame;
    QString m_lastIPOC;
};
