#include "UdpClient.h"
#include "AppStore.h"
#include <QDebug>
#include <QCoreApplication>

UdpClient::UdpClient(const QHostAddress& address, quint16 port, QObject* parent) :
	QObject(parent),
	m_address(address),
	m_port(port),
	m_udpSocket(nullptr),
	m_opened(false),
	m_closeAfter(false)
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
	m_closeAfter = false;
	m_address = address;
	m_port = port;

	if (m_udpSocket)
		delete m_udpSocket;

	m_udpSocket = new QUdpSocket(this);

	if (bind(address, port))
	{
		connectAutoRead();
		m_opened = true;
		emit opened(address, port);
	}
	else
	{
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
		disconnectAutoRead();

		m_udpSocket->close();
		m_udpSocket->deleteLater();
		m_udpSocket = nullptr;
		QCoreApplication::processEvents(); // Ensure all events are processed before emitting closed

		emit closed();
	}
}

void UdpClient::sendData(const QByteArray& data, const QHostAddress& targetAddress, quint16 targetPort)
{
	if (m_udpSocket && m_opened) {
		AppStore::captureDataSendedUS();
		AppStore::addToTmpStr("send=\"" + QString::number(AppStore::dataSended()) + "\" delaySend=\"" + QString::number(AppStore::delay_Emitted_to_Sended()) + "\" />");
		m_udpSocket->writeDatagram(data, targetAddress, targetPort);
		//AppStore::printTmpStr();
	}
}

bool UdpClient::readData(QByteArray& dataReceived) const
{
	bool received = false;
	if (m_udpSocket && m_opened) {
		while (m_udpSocket->hasPendingDatagrams()) {
			dataReceived = m_udpSocket->receiveDatagram().data();
			received = true;
		}
	}
	return received;
}

void UdpClient::disconnectAutoRead() const
{
	disconnect(m_udpSocket, &QUdpSocket::readyRead, this, &UdpClient::onReadyRead);
}

void UdpClient::connectAutoRead() const
{
	connect(m_udpSocket, &QUdpSocket::readyRead, this, &UdpClient::onReadyRead, Qt::ConnectionType(Qt::UniqueConnection | Qt::DirectConnection));
}

void UdpClient::onReadyRead()
{
	static long long lastTime = 0;
	m_datagramsCount = 0;
	lastTime = AppStore::dataReceived();
	AppStore::captureDataReceived();
	AppStore::addToTmpStr("<Time received=\"" + QString::number(AppStore::dataReceived()) + "\" delayReceived=\"" + QString::number(AppStore::dataReceived() - lastTime) + "\" ");

	while (m_udpSocket && m_udpSocket->hasPendingDatagrams()) {

		m_datagram = m_udpSocket->receiveDatagram();
		m_datagramsCount++;
	}

	if (m_datagramsCount)
		emit datagramReceived(m_datagram.data(), m_datagram.senderAddress(), m_datagram.senderPort());
}
