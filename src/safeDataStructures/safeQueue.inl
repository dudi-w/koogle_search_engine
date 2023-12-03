#ifndef SAFE_QUEUE_INL
#define SAFE_QUEUE_INL

#include "safeQueue.hpp"

template<typename T>
se::SafeQueue<T>::SafeQueue()
: SafeQueue([](){;}, [](){;})
{}

template<typename T>
se::SafeQueue<T>::SafeQueue(std::function<void(void)> sleep, std::function<void(void)> waekup)
: m_sleep(sleep)
, m_waekup(waekup)
, m_shutdown(false)
{}

template<typename T>
void se::SafeQueue<T>::deQueue(T& element)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while(true){
        if(m_shutdown){
            return;
        }
        if(!m_queue.empty()){
            element = m_queue.front();
            m_queue.pop();
            return;
        }else{
            m_sleep();
            if(m_shutdown){//band
                return;
            }
            m_cv.wait(lock);
            m_waekup();
            m_cv.notify_one();
        }
    }
}

template<typename T>
void se::SafeQueue<T>::shutdown()
{
    if(m_queue.empty()){
        m_shutdown = true;
        m_cv.notify_all();
    }
}

template<typename T>
void se::SafeQueue<T>::inQueue(const T& element)
{
    std::unique_lock lock(m_mutex);
    m_queue.push(element);
    m_cv.notify_one();
}

template<typename T>//Container
void se::SafeQueue<T>::inQueue(std::vector<T> const& elements)
{
    std::unique_lock lock(m_mutex);
    for(auto const& element : elements){
        m_queue.push(element);
    }
    m_cv.notify_all();
}

#endif
