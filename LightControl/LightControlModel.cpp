#include "LightControlModel.h"
#include <QSerialPortInfo>
#include <QDebug>

static const int states[4] = { 0x01, 0x02, 0x04, 0x08 };

LightControlModel::LightControlModel(QObject* parent) :
    QObject(parent),
    m_serial(this),
	m_pollTimer(this),
	m_relayStates(0)
{
    connect(&m_pollTimer, &QTimer::timeout, this, &LightControlModel::pollRelayStates);
}

void LightControlModel::release()
{
    if (m_serial.isOpen()) 
        m_serial.close();
    m_pollTimer.stop();

    emit released();
}

QStringList LightControlModel::getAvailablePorts() const
{
    QStringList ports;
    for (const QSerialPortInfo& info : QSerialPortInfo::availablePorts()) {
        ports << info.portName();
    }
    return ports;
}

void LightControlModel::disconnect()
{
	if (m_serial.isOpen()) 
    {
		m_serial.close();
		emit disconnected();
	}
	m_pollTimer.stop();
}

void LightControlModel::connectToPort(const QString& portName)
{
    disconnect();

	if (portName.isEmpty())
    {
		emit connectionFailed(portName, "Port not specified");
		return;
	}

    m_serial.setPortName(portName);
    m_serial.setBaudRate(QSerialPort::Baud9600);

    if (!m_serial.open(QIODevice::ReadWrite)) {
        emit connectionFailed(portName, "Unknown error");
        qWarning() << "Failed to open port:" << portName;
        return;
    }

    // Get module info
    sendCommand(0x5A); // ID and version
    if (m_serial.waitForReadyRead(500)) 
    {
        QByteArray buf = m_serial.read(2);
        if (buf.size() == 2) 
            emit moduleInfoReceived(buf[0], buf[1]);
        m_pollTimer.start(100);
    }
    else
    {
        qWarning() << portName << ": Timeout";
		disconnect();
    }

}

void LightControlModel::toggleRelay(int relayIndex)
{
    if (!m_serial.isOpen()) 
        return;

    static const int cmdOn[4] = { 0x65, 0x66, 0x67, 0x68 };
    static const int cmdOff[4] = { 0x6F, 0x70, 0x71, 0x72 };

    bool on = (m_relayStates & states[relayIndex]) == 0;
    sendCommand(on ? cmdOn[relayIndex] : cmdOff[relayIndex]);
}

void LightControlModel::pollRelayStates()
{
    sendCommand(0x5B); // Get relay states
    if (m_serial.waitForReadyRead(500)) 
    {
        QByteArray buf = m_serial.read(1);
        if (buf.size() == 1) 
        {
            m_relayStates = static_cast<int>(buf[0]);

            for (int i = 0; i < 4; ++i)
            {
                emit relayStateChanged(i, (bool)(m_relayStates & states[i]));
            }
        }
    }
}

void LightControlModel::sendCommand(int command)
{
    if (m_serial.isOpen())
    {
        QByteArray data(1, static_cast<int>(command));
        m_serial.write(data);
        m_serial.waitForBytesWritten(500);
    }
}
