#ifndef QUERY_BUILDER_IF_HPP
#define QUERY_BUILDER_IF_HPP

#include <memory>

#include "request.hpp"
#include "result.hpp"

namespace se{//Search Engin

class QueryBuilder
{
public:
    virtual ~QueryBuilder() = default;

    virtual std::unique_ptr<se::RequestIF> makeRequest() = 0;
    virtual void recieveResult(se::Result& result) const = 0;
};

}

#endif

