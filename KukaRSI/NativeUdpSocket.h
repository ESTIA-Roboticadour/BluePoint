#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

class NativeUdpSocket {
public:
    // Updated constructor: pass local and remote addresses/ports
    NativeUdpSocket(const std::string& localIp, unsigned short localPort,
        const std::string& remoteIp, unsigned short remotePort);
    ~NativeUdpSocket();

    bool bind();
    int sendTo(const char* data, int len);
    
    bool waitForData(int timeoutMs);
    //int recvFrom(char* buffer, int buflen, std::string& senderIp, unsigned short& senderPort);
    int recvFrom(char* buffer, int buflen);
    
    // Optionally, getters
    std::string localIp() const { return m_localIp; }
    unsigned short localPort() const { return m_localPort; }
    std::string remoteIp() const { return m_remoteIp; }
    unsigned short remotePort() const { return m_remotePort; }

private:
    SOCKET m_socket;
    std::string m_localIp;
    unsigned short m_localPort;
    std::string m_remoteIp;
    unsigned short m_remotePort;
};