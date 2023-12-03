#ifndef SMART_QUERY_HANDLER
#define SMART_QUERY_HANDLER

#include <algorithm>

#include "searchQueryHandler.hpp"
#include "multiQueryHandler.hpp"

namespace se{//Search Engine

class SmartQueryHandler : public SearchQueryHandler
{
public:
    explicit SmartQueryHandler(se::GetDB const& searchDB);
    SmartQueryHandler(SmartQueryHandler const& other) = default;
    SmartQueryHandler& operator=(SmartQueryHandler const& other) = default;
    virtual ~SmartQueryHandler() = default;

    virtual void receivesRequest(se::RequestIF& request) override;
    virtual se::Result returnResult() override;

private:
    void reset();

private:
    se::MultiQueryHandler m_multiQueryHandler;
    std::vector<std::string> m_requests;
    std::vector<std::string> m_negativeRequests;
    se::Result m_result;
};

}//namespace se

#endif
