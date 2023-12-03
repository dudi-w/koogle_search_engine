#include "matabase.hpp"
#include "crawler.hpp"
#include "smartQueryHandler.hpp"
#include "queryBuilderFactory.hpp"
#include "queryProcessor.hpp"

int main()
{
    se::Matabase matabase;
    
    se::Crawler crawler(matabase);

    se::SmartQueryHandler searcher(matabase);
    se::QueryBuilderFactory querysIFfactory;
    std::unique_ptr<se::QueryBuilder> queryBuilder(std::move(querysIFfactory.getQueryBuilder()));
    se::QueryProcessor queryFacilitator(searcher, *queryBuilder);
    queryFacilitator.start();
    return EXIT_SUCCESS;
}