#ifndef CLIENT_QUERY_HANDLER
#define CLIENT_QUERY_HANDLER

#include "searchQueryHandler.hpp"
#include "getDatabase.hpp"
#include "TCPclient.hpp"

namespace se{//Search Engine

class ClientQueryHandler : public SearchQueryHandler
{
public:
    explicit ClientQueryHandler(std::string const& serverAddress, uint16_t port);
    ClientQueryHandler(ClientQueryHandler const& other) = default;
    ClientQueryHandler& operator=(ClientQueryHandler const& other) = default;
    virtual ~ClientQueryHandler() = default;

    virtual void receivesRequest(se::RequestIF& request) override;
    virtual se::Result returnResult() override;

public:
    se::TCPclient m_TCPclient;
    std::unique_ptr<se::TCPsocketFile> m_fileDescription;
};

}//namespace se

#endif
