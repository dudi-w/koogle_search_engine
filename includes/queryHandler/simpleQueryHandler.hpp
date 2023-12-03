#ifndef SIMPLE_QUERY_HANDLER
#define SIMPLE_QUERY_HANDLER

#include "getDatabase.hpp"
#include "searchQueryHandler.hpp"
#include "requestIF.hpp"
#include "result.hpp"

namespace se{//Search Engine

class SimpleQueryHandler : public SearchQueryHandler
{
public:
    explicit SimpleQueryHandler(se::GetDB const& searchDB);
    SimpleQueryHandler(SimpleQueryHandler const& other) = default;
    SimpleQueryHandler& operator=(SimpleQueryHandler const& other) = default;
    virtual ~SimpleQueryHandler() = default;

    virtual void receivesRequest(se::RequestIF& request) override;
    void receivesRequest(std::string const& requests);
    virtual se::Result returnResult() override;

private:
    se::GetDB const& m_SearchDB;
    se::Result m_result;
};

}//namespace se

#endif
