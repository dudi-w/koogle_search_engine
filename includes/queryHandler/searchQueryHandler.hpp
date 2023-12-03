#ifndef SEARCH_QUERY_HANDLER
#define SEARCH_QUERY_HANDLER

#include <memory>

#include "requestIF.hpp"
#include "result.hpp"

namespace se{//Search Engine

class SearchQueryHandler
{
public:
    virtual ~SearchQueryHandler() = default;

    virtual void receivesRequest(se::RequestIF& request) = 0;
    virtual se::Result returnResult() = 0;
};

}//namespace se

#endif
