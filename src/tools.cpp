#include <regex>
#include <iostream>

#include "tools.hpp"
#include "myExceptions.hpp"

void tool::from_json(const nlohmann::json& j, se::CrawlConfig& crawlConfig,se::CommunicatConfig& communicatConfig,se::ThreadsConfig& threadsConfig)
{
    j.at("srcURL").get_to(crawlConfig.m_srcURL);
    j.at("maxPages").get_to(crawlConfig.m_maxPages);
    j.at("bounded").get_to(crawlConfig.m_bounded);

    j.at("serverAddress").get_to(communicatConfig.m_serverAddress);
    j.at("portNum").get_to(communicatConfig.m_portNum);

    j.at("maxThreads").get_to(threadsConfig.m_maxThreads);
}

void tool::from_json(const nlohmann::json& j, std::vector<std::string>& request)
{
    j.at("request").get_to(request);
}

void tool::from_json(const nlohmann::json& j, std::vector<std::pair<std::string, size_t>>& result)
{
    j.at("result").get_to(result);
}

void tool::isNetworkConnected()
{
    if(system("ping -c 1 google.com >> /dev/null")) {
        throw se::CommunicationError("Check your network connection");
    }
}

void tool::makeLowercase(std::string& string)
{
    std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c){ return std::tolower(c);});
}

se::Request tool::convertToRequest(std::string const& message)
{
    std::stringstream strs(message);
    std::vector<std::string> query;
    nlohmann::json j;
    strs >> j;
    tool::from_json(j, query);
    return se::Request(query);
}

se::Result tool::convertToResult(std::string const& message)
{
    std::stringstream strs(message);
    se::LinkVec result;
    nlohmann::json j;
    strs >> j;
    tool::from_json(j, result);
    return se::Result(result);
}

std::string tool::convertToString(se::Result const& result)
{
    nlohmann::json data;
    data["result"] = result.getResult();
    return data.dump();
}

std::string tool::convertToString(se::Request const& request)
{
    nlohmann::json data;
    data["request"] = request.getRequest();
    return data.dump();
}

void tool::extractHTTP(std::string const& srcPage, std::string& result)
{
    std::regex txt_regex("https?:");
    std::smatch HTTPmatch;
    if(std::regex_search(srcPage, HTTPmatch, txt_regex)){
        result = static_cast<std::string>(HTTPmatch[0]);
    }
}

void tool::extractPrefix(std::string const& srcPage, std::string& result)
{
    std::regex preRegex("^https?:\\/\\/(?:[a-zA-Z0-9]+)(?:\\.[a-zA-Z0-9]+)+");
    std::smatch preMatch;
    if(std::regex_search(srcPage, preMatch, preRegex)){
        result = preMatch[0];
    }else{
        result = "";
    }
}