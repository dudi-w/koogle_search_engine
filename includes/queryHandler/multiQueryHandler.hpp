#ifndef P_MULTI_QUERY_HANDLER
#define P_MULTI_QUERY_HANDLER

#include "simpleQueryHandler.hpp"

namespace se{//Search Engine

class MultiQueryHandler : public SearchQueryHandler
{
public:
    explicit MultiQueryHandler(se::GetDB const& searchDB);
    MultiQueryHandler(MultiQueryHandler const& other) = default;
    MultiQueryHandler& operator=(MultiQueryHandler const& other) = default;
    virtual ~MultiQueryHandler() = default;

    virtual void receivesRequest(se::RequestIF& request) override;
    void receivesRequest(std::vector<std::string> const& requests);
    virtual se::Result returnResult() override;

private:
    void makeForNegative();
    void makeForPositive();
    void reset();

private:
    se::SimpleQueryHandler m_simpleQueryHandler;
    std::vector<std::string> m_requests;
    se::Result m_result;
};

}//namespace se

#endif
