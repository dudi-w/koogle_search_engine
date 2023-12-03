#ifndef TCP_QUERY_HPP
#define TCP_QUERY_HPP

#include "queryBuilderIF.hpp"
#include "TCPserver.hpp"
#include "TCPsocketFile.hpp"

namespace se{//Search Engin

class TCPqueryBuilder : public QueryBuilder
{
public:
    explicit TCPqueryBuilder(uint16_t port = -1);
    TCPqueryBuilder(TCPqueryBuilder const& other) = default;
    TCPqueryBuilder& operator=(TCPqueryBuilder const& other) = default;
    ~TCPqueryBuilder() = default;

    virtual std::unique_ptr<se::RequestIF> makeRequest() override;
    virtual void recieveResult(se::Result& result) const override;

private:
    se::TCPserver m_server;
    std::unique_ptr<se::TCPsocketFile> m_fileDescription;
};

}

#endif