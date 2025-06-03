// LightControlModel.h
#pragma once

#include <QObject>
#include <QSerialPort>
#include <QTimer>

class LightControl : public QObject
{
    Q_OBJECT

public:
    explicit LightControl(QObject* parent = nullptr);
    ~LightControl() override = default;

    void release();
    static QStringList getAvailablePorts();
    void disconnect();
    void connectToPort(const QString& portName);
    void toggleRelay(int relayIndex);
    void setRelay(int relayIndex, bool on);

private slots:
    void pollRelayStates();

private:
    void sendCommand(int command);
	void turnOffAllRelays();

signals:
	void disconnected();
	void connected(const QString& portName);
	void connectionFailed(const QString& portName, const QString& error);
    void moduleInfoReceived(int id, int version);
    void relayStateChanged(int relayIndex, bool state);
    void released();

private:
    QSerialPort m_serial;
    QTimer m_pollTimer;
    int m_relayStates;
};
