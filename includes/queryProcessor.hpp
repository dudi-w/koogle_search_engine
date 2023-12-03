#ifndef QUERYFACILITA_HPP
#define QUERYFACILITA_HPP

#include "searchQueryHandler.hpp"
#include "queryBuilderIF.hpp"

namespace se{//Search Engine

class QueryProcessor
{
public:           
    explicit QueryProcessor(se::SearchQueryHandler& queryHandler, se::QueryBuilder& queryIF );
    QueryProcessor(QueryProcessor const& other) = default;
    QueryProcessor& operator=(QueryProcessor const& other) = default;
    ~QueryProcessor() = default;

    void start() const;

private:
    se::SearchQueryHandler& m_queryHandler;
    se::QueryBuilder& m_queryIF;
};

}//namespace se

#endif
