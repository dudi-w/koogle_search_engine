#ifndef SOCKET_FILE_HPP
#define SOCKET_FILE_HPP

#include <string>

namespace se{

class TCPsocketFile
{
public:
    explicit TCPsocketFile(int fileDescriptor = -1);
    TCPsocketFile(TCPsocketFile const& other) = delete;
    TCPsocketFile& operator=(TCPsocketFile const& other) = delete;
    ~TCPsocketFile();

public:
    std::string read();
    void write(std::string const& text) const;
    int fileDescriptorNum() const noexcept;

private:
    void colseSocket() const;

private:
    int m_fileDescriptor;
    uint16_t m_buffSize;
};

}

#endif
