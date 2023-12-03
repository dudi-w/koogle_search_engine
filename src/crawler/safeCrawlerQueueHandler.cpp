#include "safeCrawlerQueueHandler.hpp"
#include "configuration.hpp"

se::SafeCrawlerQueueHandler::SafeCrawlerQueueHandler()
: m_safeQueue([this](){sleep();}, [this](){waekup();})
, m_waiting(0)
{}

bool se::SafeCrawlerQueueHandler::deQueue(std::string& link)
{
    m_safeQueue.deQueue(link);
    return !link.empty();
}

void se::SafeCrawlerQueueHandler::inQueue(std::string const& link)
{
    m_safeQueue.inQueue(link);
}

void se::SafeCrawlerQueueHandler::inQueue(std::vector<std::string> const& links)
{
    m_safeQueue.inQueue(links);
}

void se::SafeCrawlerQueueHandler::sleep()
{
    ++m_waiting;
    if(m_waiting == se::Configuration::maxThreads()){
        m_safeQueue.shutdown();
    }

    /*if(m_waiting == se::Configuration::maxThreads()){
        std::string poisonApple = "";
        for(size_t i = 0 ; i < se::Configuration::maxThreads() ; ++i){
            m_safeQueue.unsafeInQueue(poisonApple);
        }
    }

    if(m_waiting == se::Configuration::maxThreads()){
        std::string poisonApple = "";
        std::thread t([&](){
            for(size_t i = 0 ; i < se::Configuration::maxThreads() ; ++i){
                m_safeQueue.inQueue(poisonApple);
            }});
        t.detach();
    }*/

}

void se::SafeCrawlerQueueHandler::waekup()
{
    --m_waiting;
}