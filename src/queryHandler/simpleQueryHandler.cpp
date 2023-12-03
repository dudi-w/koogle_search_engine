#include <algorithm>

#include "simpleQueryHandler.hpp"
#include "myExceptions.hpp"

se::SimpleQueryHandler::SimpleQueryHandler(se::GetDB const& searchDB)
: m_SearchDB(searchDB)
, m_result({})
{}

void se::SimpleQueryHandler::receivesRequest(se::RequestIF& request)
{
    if(request.getRequest().size() != 1){
        throw se::InValidArg("Only one argument is required");
    }
    receivesRequest(request.getRequest()[0]);
}

void se::SimpleQueryHandler::receivesRequest(std::string const& request)
{
    m_result = se::Result({});
    se::LinkVec vecResult;

    if(m_SearchDB.wordExis(request)){
        vecResult = std::move(m_SearchDB.getLinkOfWord(request));
        auto it = vecResult.begin();
        while(it != vecResult.end()){
            if(!m_SearchDB.getRank(it->first)){
                it = vecResult.erase(it);
            }else{
                ++it;
            }
        }
        std::sort(vecResult.begin(), vecResult.end(), [this](auto pair1 ,auto pair2){return pair1.second*m_SearchDB.getRank(pair1.first) > pair2.second*m_SearchDB.getRank(pair2.first);});
        m_result = std::move(se::Result(vecResult));
    }
}

se::Result se::SimpleQueryHandler::returnResult()
{
    return m_result;
}
