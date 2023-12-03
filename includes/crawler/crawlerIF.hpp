#ifndef CRAWLER_IF_HPP
#define CRAWLER_IF_HPP

#include <string>
#include <vector>

#include "analyzPage.hpp"

namespace se{//Search Engine

class CrawlerIF
{
public:
    virtual ~CrawlerIF() = default;

    virtual std::string getURLtoDownload() = 0;
    virtual void updatePage(AnalyzPage const& page) = 0;
};

}//namespace se

#endif
