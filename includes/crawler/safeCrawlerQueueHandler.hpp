#ifndef SAFE_CRAWLER_QUEUE_HANDLER_HPP
#define SAFE_CRAWLER_QUEUE_HANDLER_HPP

#include <atomic>

#include "safeQueue.hpp"

namespace se{

class SafeCrawlerQueueHandler
{
public:
    SafeCrawlerQueueHandler();
    SafeCrawlerQueueHandler(SafeCrawlerQueueHandler const& other) = default;
    SafeCrawlerQueueHandler& operator=(SafeCrawlerQueueHandler const& other) = default;
    ~SafeCrawlerQueueHandler() = default;

public:
    bool deQueue(std::string& link);
    void inQueue(std::string const& link);
    void inQueue(std::vector<std::string> const& links);

private:
    void sleep();
    void waekup();

private:
    se::SafeQueue<std::string> m_safeQueue;
    std::mutex m_mutex;
    std::atomic<size_t> m_waiting;
};

}// namespace se

#endif
