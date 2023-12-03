#include "TCPquery.hpp"
#include "myExceptions.hpp"
#include "tools.hpp"

se::TCPqueryBuilder::TCPqueryBuilder(uint16_t port)
: m_server(port)
, m_fileDescription(nullptr)
{
    m_server.createSocket();
    m_server.bindSocket();
    m_server.listenForClient();
}

std::unique_ptr<se::RequestIF> se::TCPqueryBuilder::makeRequest()
{
    m_fileDescription = m_server.acceptToRecieve();
    if(m_fileDescription == nullptr){
        throw se::FileDiscreptorError("invalid filediscreptor number");
    }

    std::string message = m_fileDescription->read();
    auto request = tool::convertToRequest(message);
    if(request.getRequest().at(0) == "1234"){
        return nullptr;
    }
    return std::make_unique<se::Request>(request);
}

void se::TCPqueryBuilder::recieveResult(se::Result& result) const
{
    if(m_fileDescription == nullptr){
        throw se::FileDiscreptorError("invalid filediscreptor number");
    }

    if(int fileDescriptorNum = m_fileDescription->fileDescriptorNum(); fileDescriptorNum < 3){
        throw se::FileDiscreptorError("invalid file discreptor number " + fileDescriptorNum);
    }
    auto message = tool::convertToString(result);
    m_fileDescription->write(message);
}
