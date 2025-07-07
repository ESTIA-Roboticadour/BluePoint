#pragma once

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>

class UdpClient : public QObject
{
	Q_OBJECT

public:
	explicit UdpClient(const QHostAddress& address, quint16 port, QObject* parent = nullptr);
	~UdpClient();

	QHostAddress address() const { return m_address; }
	quint16 port() const { return m_port; }

	void close();

	void open();
	void open(const QHostAddress& address, quint16 port);
	bool isOpened() const { return m_opened; }

	// Envoi de données
	void sendData(const QString& message, const QHostAddress& targetAddress, quint16 targetPort);

	bool readData(QByteArray& dataReceived) const;
	void disconnectAutoRead() const;
	void connectAutoRead() const;

signals:
	void opened(const QHostAddress& m_address, quint16 m_port);
	void closed();
	void failedToOpen(const QHostAddress& m_address, quint16 m_port);
	// Signal émis à chaque réception de datagramme
	void datagramReceived(const QByteArray& data, const QHostAddress& sender, quint16 senderPort);

private slots:
	// Slot déclenché à la réception
	void onReadyRead();

private:
	// Liaison locale
	bool bind(const QHostAddress& address, quint16 port);

private:
	bool m_opened;
	bool m_closeAfter;
	quint16 m_port;
	QHostAddress m_address;
	QUdpSocket* m_udpSocket;
};
