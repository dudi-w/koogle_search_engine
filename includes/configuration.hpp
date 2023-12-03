#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>
#include <vector>
#include <fstream>

namespace se{

struct CrawlConfig
{
    std::vector<std::string> m_srcURL;
    size_t m_maxPages;
    bool m_bounded;
};

struct CommunicatConfig
{
    std::string m_serverAddress;
    uint16_t m_portNum;
};

struct ThreadsConfig
{
    size_t m_maxThreads;
};

class Configuration
{
public:
    ~Configuration() = default;
    
    std::vector<std::string> static const& getSrcURLs();
    size_t static maxPages();
    bool static isBounded();
    uint16_t static portNum();
    std::string static serverAddress();
    size_t static maxThreads();

private:
    explicit Configuration(std::string const& configurationFilePath);
    Configuration(Configuration const& other) = delete;
    Configuration& operator=(Configuration const& other) = delete;

    static Configuration& getInstance();
    void laodConfiguration(std::string const& configurationFilePath);

private:
    se::CrawlConfig m_crawlConfig;
    se::CommunicatConfig m_communicatConfigConfig;
    se::ThreadsConfig m_ThreadsConfig;
};

}

#endif
