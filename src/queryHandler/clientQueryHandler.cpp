#include "clientQueryHandler.hpp"
#include "myExceptions.hpp"
#include "tools.hpp"

se::ClientQueryHandler::ClientQueryHandler(std::string const& serverAddress, uint16_t port)
: m_TCPclient(serverAddress, port)
, m_fileDescription(nullptr)
{}

void se::ClientQueryHandler::receivesRequest(se::RequestIF& request)
{
    auto requestList = request.getRequest();
    std::string message = tool::convertToString(se::Request(requestList));
    m_fileDescription = m_TCPclient.connectToServer();
    m_fileDescription->write(message);
}

se::Result se::ClientQueryHandler::returnResult()//? mybe deleted
{
    if(m_fileDescription == nullptr){
        throw se::FileDiscreptorError("returnResult invalid filediscreptor number");
    }
    
    if(int fileDescriptorNum = m_fileDescription->fileDescriptorNum(); fileDescriptorNum < 3){
        throw se::FileDiscreptorError("invalid file discreptor number " + fileDescriptorNum);
    }
    std::string message = std::move(m_fileDescription->read());
    m_fileDescription = nullptr;
    return tool::convertToResult(message);
}
