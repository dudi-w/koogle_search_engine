#include <iostream>

#include "crawlerQueue.hpp"
#include "myExceptions.hpp"
#include "getHTTP.hpp"
#include "tools.hpp"

se::CrawlerQueue::CrawlerQueue()
: m_safeQueueHandler{}
{
    srcURLValidation();
    if(se::Configuration::isBounded()){
        extractSrcPrefix();
    }
    inQueue(se::Configuration::getSrcURLs());
}

void se::CrawlerQueue::logAsActive(std::string const& link)
{
    std::clog<<"\U0001F525 \033[1;33m"<<link<<"\033[0m \U0001F525\n"<<std::endl;
}

std::string se::CrawlerQueue::deQueue()
{
    while(true){
		std::string link;
		if(!m_safeQueueHandler.deQueue(link)){
			break;
		}
		if(!m_activedLinks.insert(link)){
			continue;
		}
		if(m_activedLinks.size() > se::Configuration::maxPages()){
            break;
		}
    	logAsActive(link);//optionel
		return link;
    }
    return "";
}

void se::CrawlerQueue::inQueue(std::string const& link)
{
    if(!m_activedLinks.count(link) && ifBounded(link)){
        m_safeQueueHandler.inQueue(link);
    }
}

void se::CrawlerQueue::inQueue(std::string && link)
{
    if(!m_activedLinks.count(link) && ifBounded(link)){
        m_safeQueueHandler.inQueue(link);
    }
}

void se::CrawlerQueue::inQueue(std::vector<std::string> const& links)
{
    for(auto const& link : links){
        inQueue(link);
    }
}

void se::CrawlerQueue::srcURLValidation()
{
    for(auto const& url : se::Configuration::getSrcURLs()){
        try{
            tool::isNetworkConnected();
            getHTTPpage(url);
        }
        catch(const curlpp::LibcurlRuntimeError & e)
        {
            throw se::InValidSrcURL("can't laod src url " + url);
        }
    }
}

void se::CrawlerQueue::extractSrcPrefix()
{
    std::string prefix;
    for(size_t i = 0 ; i < se::Configuration::getSrcURLs().size(); ++i){
        m_homeAddress.reserve(se::Configuration::getSrcURLs().size());
        tool::extractPrefix(se::Configuration::getSrcURLs()[i], prefix);
        m_homeAddress.push_back(prefix);
    }
}

bool se::CrawlerQueue::ifBounded(std::string const& link) const
{
    if(!se::Configuration::isBounded()){
        return true;
    }else{
        std::string currentHomeAddress;
        tool::extractPrefix(link, currentHomeAddress);
        auto lambda = [&currentHomeAddress](auto const& HomeAddress){return HomeAddress == currentHomeAddress;};
        return std::any_of(m_homeAddress.cbegin(), m_homeAddress.cend(), lambda);
    }
}
