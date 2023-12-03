#include <iostream>

#include "configuration.hpp"
#include "tools.hpp"

se::Configuration::Configuration(std::string const& configurationFilePath)
{
    laodConfiguration(configurationFilePath);
}

std::vector<std::string> const& se::Configuration::getSrcURLs()
{
    return getInstance().m_crawlConfig.m_srcURL;
}

size_t se::Configuration::maxPages()
{
    return getInstance().m_crawlConfig.m_maxPages;
}

bool se::Configuration::isBounded()
{
    return getInstance().m_crawlConfig.m_bounded;
}

size_t se::Configuration::maxThreads()
{
    return getInstance().m_ThreadsConfig.m_maxThreads;
}

uint16_t se::Configuration::portNum()
{
    return getInstance().m_communicatConfigConfig.m_portNum;
}

std::string se::Configuration::serverAddress()
{
    return getInstance().m_communicatConfigConfig.m_serverAddress;
}

se::Configuration& se::Configuration::getInstance()
{
    static se::Configuration configuration("config.json");
    return configuration;
}

void se::Configuration::laodConfiguration(std::string const& configurationFilePath)
{
    try{
        std::ifstream input_file(configurationFilePath);
        nlohmann::json j;
        input_file >> j;
        tool::from_json(j, m_crawlConfig, m_communicatConfigConfig, m_ThreadsConfig);
    }
    catch(const nlohmann::json::exception& e)
    {
        throw std::runtime_error("load configuration file failed ,check yuor configuration file");
    }  
}