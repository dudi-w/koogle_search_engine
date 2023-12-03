#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <sys/socket.h>
#include <arpa/inet.h>

#include "TCPsocketFile.hpp"

namespace se{//Search Engine

class TCPserver
{
public:
    explicit TCPserver(uint16_t port);
    TCPserver(TCPserver const& other) = default;
    TCPserver& operator=(TCPserver const& other) = default;
    ~TCPserver();

public:
    void createSocket();
    void bindSocket();
    void listenForClient() const;
    std::unique_ptr<se::TCPsocketFile> acceptToRecieve() const;

private:
    void closeSocket() const;
    void logConnect(struct sockaddr_in& clientAddress) const;

private:
    struct sockaddr_in m_address;
    int m_server_fd;
    int m_port;
};

}//namespace se

#endif
