#include <thread>

#include "pageFetcher.hpp"
#include "getHTTP.hpp"
#include "myExceptions.hpp"
#include "configuration.hpp"
#include "systemMonitor.hpp"

se::PageFetcher::PageFetcher(se::CrawlerIF& crawler)
: m_crawler(crawler)
, m_lest{0}
{}

void se::PageFetcher::startDownload()
{
    while(true){
        if(std::string url = m_crawler.getURLtoDownload() ; !url.empty()){
            try{
                auto page = getHTTPpage(url);
                m_crawler.updatePage(page);
            }
            catch(const curlpp::LibcurlRuntimeError& e){
                std::cerr<<"\033[3;31mERROR: can't laod url \033[0m"<<url<<std::endl;
                continue;
            }
        }
        else{
            break;
        }
    }
    
    if((++m_lest) == se::Configuration::maxThreads()){
        se::SystemMonitor::end();
    }
}
