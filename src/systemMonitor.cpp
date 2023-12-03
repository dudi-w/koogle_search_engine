#include <iostream>

#include "systemMonitor.hpp"

se::SystemMonitor& se::SystemMonitor::getInstance()
{
    static se::SystemMonitor systemMonitor;
    return systemMonitor;
}

void se::SystemMonitor::start()
{
    se::SystemMonitor::getInstance().m_start_time = std::chrono::high_resolution_clock::now();
};

void se::SystemMonitor::end()
{
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - se::SystemMonitor::getInstance().m_start_time);
    std::clog << "Execution time: " << duration.count() << " microseconds\n";
    se::SystemMonitor::getInstance().m_logFunc();
}

void se::SystemMonitor::setLogFunc(std::function<void()> logFunc)
{
    se::SystemMonitor::getInstance().m_logFunc = logFunc;
}

