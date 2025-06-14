#include "UdpClient.h"
#include <QDebug>

UdpClient::UdpClient(const QHostAddress& address, quint16 port, QObject* parent) :
    QObject(parent),
    m_address(address), 
    m_port(port),
    m_udpSocket(nullptr),
    m_opened(false)
{
}

UdpClient::~UdpClient()
{
    close();
}

void UdpClient::open()
{
    open(m_address, m_port);
}

void UdpClient::open(const QHostAddress& address, quint16 port)
{
    m_opened = false;
    m_address = address;
    m_port = port;

    if (m_udpSocket)
        delete m_udpSocket;

    m_udpSocket = new QUdpSocket(this);

    if (bind(address, port)) 
    {
        connect(m_udpSocket, &QUdpSocket::readyRead, this, &UdpClient::onReadyRead);
        m_opened = true;
        emit opened(address, port);
    }
    else {
        emit failedToOpen(address, port);
    }
}

bool UdpClient::bind(const QHostAddress& address, quint16 port)
{
    return m_udpSocket->bind(address, port);
}

void UdpClient::close()
{
    if (m_udpSocket) {
        m_opened = false;
        m_udpSocket->close();
        delete m_udpSocket;
        m_udpSocket = nullptr;
        emit closed();
    }
}

void UdpClient::sendData(const QString& message, const QHostAddress& targetAddress, quint16 targetPort)
{
    if (m_udpSocket && m_opened) {
        m_udpSocket->writeDatagram(message.toUtf8(), targetAddress, targetPort);
    }
}

void UdpClient::onReadyRead()
{
    while (m_udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_udpSocket->receiveDatagram();
        emit datagramReceived(datagram.data(), datagram.senderAddress(), datagram.senderPort());
    }
}
