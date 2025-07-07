#include "NativeUdpSocket.h"
#include <sys/types.h>
#include <sys/timeb.h>

NativeUdpSocket::NativeUdpSocket(const std::string& localIp, unsigned short localPort,
	const std::string& remoteIp, unsigned short remotePort)
	: m_socket(INVALID_SOCKET),
	m_localIp(localIp),
	m_localPort(localPort),
	m_remoteIp(remoteIp),
	m_remotePort(remotePort)
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

NativeUdpSocket::~NativeUdpSocket() {
	if (m_socket != INVALID_SOCKET)
		closesocket(m_socket);
	WSACleanup();
}

bool NativeUdpSocket::bind() {
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_localPort);
	inet_pton(AF_INET, m_localIp.c_str(), &addr.sin_addr);
	return ::bind(m_socket, (sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR;
}

int NativeUdpSocket::sendTo(const char* data, int len) {
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_remotePort);
	inet_pton(AF_INET, m_remoteIp.c_str(), &addr.sin_addr);
	return sendto(m_socket, data, len, 0, (sockaddr*)&addr, sizeof(addr));
}

bool NativeUdpSocket::waitForData(int timeoutMs)
{
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(m_socket, &readfds);

	timeval tv;
	tv.tv_sec = timeoutMs / 1000;
	tv.tv_usec = (timeoutMs % 1000) * 1000;

	int result = select(0, &readfds, nullptr, nullptr, &tv);
	return (result > 0) && FD_ISSET(m_socket, &readfds);
}

//int NativeUdpSocket::recvFrom(char* buffer, int buflen, std::string& senderIp, unsigned short& senderPort) {
//    sockaddr_in from = {};
//    int fromlen = sizeof(from);
//    int ret = recvfrom(m_socket, buffer, buflen, 0, (sockaddr*)&from, &fromlen);
//    if (ret > 0) {
//        char ipbuf[INET_ADDRSTRLEN];
//        inet_ntop(AF_INET, &from.sin_addr, ipbuf, sizeof(ipbuf));
//        senderIp = ipbuf;
//        senderPort = ntohs(from.sin_port);
//    }
//    return ret;
//}

int NativeUdpSocket::recvFrom(char* buffer, int buflen) {
	return recv(m_socket, buffer, buflen, 0);
	// return recvfrom(m_socket, buffer, buflen, 0, nullptr, nullptr);
}
