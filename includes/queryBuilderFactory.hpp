#ifndef QUERY_FACTORY_HPP
#define QUERY_FACTORY_HPP

#include <memory>

#include "queryBuilderIF.hpp"
#include "textUI.hpp"
#include "TCPquery.hpp"

namespace se{//Search Engine

class QueryBuilderFactory
{
public:
    QueryBuilderFactory() = default;
    QueryBuilderFactory(QueryBuilderFactory const& other) = default;
    QueryBuilderFactory& operator=(QueryBuilderFactory const& other) = default;
    ~QueryBuilderFactory() = default;

    std::unique_ptr<se::QueryBuilder> getQueryBuilder();
};

}//namespace se

#endif
