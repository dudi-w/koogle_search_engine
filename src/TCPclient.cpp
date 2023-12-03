#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <memory>

#include "TCPclient.hpp"
#include "myExceptions.hpp"

se::TCPclient::TCPclient::TCPclient(std::string const& serverAddress, uint16_t port)
: m_serverPort(port)
, m_serverAddress(serverAddress)
{}

se::TCPclient::~TCPclient()
{
    closeSocket();
}

void se::TCPclient::createSocket()
{
    if((m_client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        throw se::CreateSocketError("failed to create socket");
    }
}

std::unique_ptr<se::TCPsocketFile> se::TCPclient::connectToServer()
{
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(m_serverPort);
    createSocket();
    
    if(inet_pton(AF_INET, m_serverAddress.c_str(), &serverAddr.sin_addr) <= 0){
        close(m_client_fd);
        throw se::CommunicationError("Error converting server address");
    }
    if(int status = connect(m_client_fd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) ; status < 0){
        closeSocket();
        throw se::CommunicationError("Error connecting to server");
    }
    return std::make_unique<se::TCPsocketFile>(m_client_fd);
}

void se::TCPclient::closeSocket() const
{
    close(m_client_fd);
}
