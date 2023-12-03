#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <sstream>

#include "TCPsocketFile.hpp"
#include "tools.hpp"
#include "myExceptions.hpp"

se::TCPsocketFile::TCPsocketFile(int fileDescriptor)
: m_fileDescriptor(fileDescriptor)
, m_buffSize(4096)
{}

se::TCPsocketFile::~TCPsocketFile()
{
    colseSocket();
}

std::string se::TCPsocketFile::read()
{
    std::string message;
    while(true){
        std::string buffer(m_buffSize, 0);
        ssize_t bytesReceived = recv(m_fileDescriptor, buffer.data(), m_buffSize ,0);
        if(bytesReceived < 0){
            throw se::ReadError("Cannot read from file descriptor number " + m_fileDescriptor);
        }
        message.append(buffer ,0 ,bytesReceived);
        if(bytesReceived < m_buffSize && bytesReceived){
            break;
        }
    }
    return message;
}

void se::TCPsocketFile::write(std::string const& text) const
{
    if(ssize_t bytesSent = send(m_fileDescriptor, text.c_str(), text.size(), 0); bytesSent < 0){
        throw se::WriteError("Cannot write to file descriptor number " + m_fileDescriptor);
    }
}

void se::TCPsocketFile::colseSocket() const
{
    close(m_fileDescriptor);
}

int se::TCPsocketFile::fileDescriptorNum() const noexcept
{
    return m_fileDescriptor;
}
