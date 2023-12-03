#ifndef SYSTEM_MONITOR_HPP
#define SYSTEM_MONITOR_HPP

#include <chrono>
#include <functional>

namespace se{

class SystemMonitor
{
public:
    ~SystemMonitor() = default;
    
    static void start();
    static void end();
    static void setLogFunc(std::function<void()> logFunc);

private:
    SystemMonitor() = default;
    SystemMonitor(SystemMonitor const& other) = delete;
    SystemMonitor& operator=(SystemMonitor const& other) = delete;

    static SystemMonitor& getInstance();

private:
    std::chrono::_V2::system_clock::time_point m_start_time;
    std::function<void()> m_logFunc;
};

}

#endif
