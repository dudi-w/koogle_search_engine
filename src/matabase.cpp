#include <iostream>

#include "matabase.hpp"
#include "myExceptions.hpp"
#include "systemMonitor.hpp"

se::Matabase::Matabase()
{
    se::SystemMonitor::setLogFunc([&](){log();});
}

void se::Matabase::log() const
{
    std::clog<<"\033[3;32mEnd of storage\033[0m\n"<<std::endl;
    std::clog<<"\tNumber of words: "<<m_safeWordsIndex.size()<<std::endl;
    std::clog<<"\tThe number of links: "<<m_safeLinksMap.size()<<std::endl;
}

se::LinkVec se::Matabase::getLinkOfWord(std::string const& word) const
{
    auto mapResult = m_safeWordsIndex.at(word);
    se::LinkVec vecResult(mapResult.cbegin(), mapResult.cend());
    return vecResult;
}

void se::Matabase::insertLinks(std::string const& srcLink, std::vector<std::string> const& links)
{
    if(!m_safeLinksMap.exis(srcLink)){
        for(auto const& link : links){
            insertLink(srcLink ,link);
        }
    }else{
        throw se::StorageError("Double storage of URL = " + srcLink);
    }
}
void se::Matabase::insertLink(std::string const& srcLink, std::string const& link)
{
    m_safeLinksMap.insert(srcLink, link, 1, [](size_t& count){ ++count;});
    if(m_safeLinksMap.size() - m_pageRank.lestUpCount() > 10){
        m_pageRank.reCalculatePageRank(m_safeLinksMap);
    }
}

void se::Matabase::insertWords(std::string const& srcLink, std::vector<std::string> const& words)
{
    for(auto const & word : words){
        m_safeWordsIndex.insert(word ,srcLink, 1, [](auto& count){ ++count;});
    }
}

float se::Matabase::getRank(std::string const& link) const
{
    return m_pageRank.getRank(link);
}

bool se::Matabase::wordExis(std::string const& word) const
{
    return m_safeWordsIndex.exis(word);
}