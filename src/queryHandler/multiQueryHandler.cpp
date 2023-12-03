#include <algorithm>

#include "multiQueryHandler.hpp"
#include "myExceptions.hpp"

se::MultiQueryHandler::MultiQueryHandler(se::GetDB const& searchDB)
: m_simpleQueryHandler(searchDB)
, m_result({})
{}

void se::MultiQueryHandler::receivesRequest(se::RequestIF& request)
{
    receivesRequest(request.getRequest());
}

void se::MultiQueryHandler::receivesRequest(std::vector<std::string> const& requests)
{
    reset();
    m_requests = requests;
    if(m_requests.size() == 0){
        return;
    }
    auto lambdaNeg = [](std::string const& request){return request[0] == '-';};
    auto lambdaPos = [](std::string const& request){return request[0] != '-';};
    if(std::all_of(m_requests.cbegin(), m_requests.cend(), lambdaNeg)){
        makeForNegative();
    }else if(std::all_of(m_requests.cbegin(), m_requests.cend(), lambdaPos)){
        makeForPositive();
    }else{
        throw se::InValidArg("Mixed arguments!");
    }
}

void se::MultiQueryHandler::reset()
{
    m_requests.clear();
    m_result = se::Result({});
}

void se::MultiQueryHandler::makeForNegative()
{
    for(size_t i = 0; i < m_requests.size(); ++i){
        m_simpleQueryHandler.receivesRequest(m_requests[i].substr(1));
        auto result = m_simpleQueryHandler.returnResult();
        if(result.getResult().size() != 0){
            m_result = m_result | result;
        }
    }
}

void se::MultiQueryHandler::makeForPositive()
{
    m_simpleQueryHandler.receivesRequest(m_requests[0]);
    auto result = m_simpleQueryHandler.returnResult();
    if(result.getResult().size() == 0){
        return;
    }

    m_result = se::Result(result.getResult());

    for(size_t i = 1; i < m_requests.size(); ++i){
        m_simpleQueryHandler.receivesRequest(m_requests[i]);
        result = m_simpleQueryHandler.returnResult();
        if(result.getResult().size() == 0){
            m_result = se::Result({});
            return;
        }
        m_result = m_result & result;
    }
}

se::Result se::MultiQueryHandler::returnResult()
{
    return m_result;
}
