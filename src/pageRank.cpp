#include <algorithm>
#include <numeric>

#include "pageRank.hpp"

std::unordered_map<std::string, float> calculatePageRank(se::MyMap const& linksMap);

se::PageRank::PageRank()
: m_lestUp{0}
{}

void se::PageRank::reCalculatePageRank(se::MyMap const& linksMap)//? maybe pase copy 
{
    m_lestUp = linksMap.size();
    m_scoreMap = calculatePageRank(linksMap);
}

float se::PageRank::getRank(std::string const& link) const
{
    return (m_scoreMap.exis(link)) ? m_scoreMap.at(link) : 0 ;
}

size_t se::PageRank::lestUpCount() const
{
    return m_lestUp;
}

/*tools*/
std::unordered_map<std::string, float> calculatePageRank(se::MyMap const& linksMap)
{
    auto linksMapCopy = std::move(linksMap.getTable());
    std::unordered_map<std::string, float> pageRank(linksMapCopy.size());
    
    for(auto const& link : linksMapCopy){
        pageRank[link.first] = 1;
    }

    const size_t N = pageRank.size();//Total number of pages
    const float d = 0.85;//Damping factor, usually 0.85
    float dis = 1, newDis = 0;

    while(dis != newDis){
        newDis = dis;
        std::unordered_map<std::string, float> newPageRank;
        for(auto const& [linkSrc , scoreSrc] : pageRank){
            auto linkCount = std::accumulate(linksMapCopy.at(linkSrc).begin(),\
            linksMapCopy.at(linkSrc).end(), 0,\
            [](int sum, std::pair<std::string, size_t> const& pair){return sum + pair.second;});

            for(auto const& [link , count] : linksMapCopy.at(linkSrc)){
                if(pageRank.count(link)){
                    if(newPageRank.count(link)){
                        newPageRank[link] += (scoreSrc/linkCount)*count;
                    }else{
                        newPageRank[link] = scoreSrc/linkCount*count;
                    }
                }
            }
        }
        std::for_each(newPageRank.cbegin(), newPageRank.cend(), [&](std::pair<std::string, float> const& pair){pageRank[pair.first] = ((1-d)/N) + (d*pair.second);});

        auto it = newPageRank.cbegin();
        dis = std::abs(it->second - pageRank[it->first]);
    }
    return pageRank;
}