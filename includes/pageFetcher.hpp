#ifndef PAGE_FETCHER
#define PAGE_FETCHER

#include <atomic>

#include "crawlerIF.hpp"
#include "analyzPage.hpp"


namespace se{//Search Engine

class PageFetcher
{
public:
    explicit PageFetcher(se::CrawlerIF & crawler);
    PageFetcher(PageFetcher const& other) = default;
    PageFetcher& operator=(PageFetcher const& other) = default;
    virtual ~PageFetcher() = default;

    void startDownload();

private:
    se::CrawlerIF& m_crawler;
    std::atomic<size_t> m_lest;
};

}//namespace se

#endif
