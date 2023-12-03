#include "request.hpp"
#include "tools.hpp"

se::Request::Request(std::string const& request)
{
    std::string new_request = request;
    tool::makeLowercase(new_request);

    std::istringstream iss(new_request);
    std::string word;
    while (iss >> word){
        m_request.push_back(word);
    }
}

se::Request::Request(std::vector<std::string> const& request)
: m_request(request)
{}

std::vector<std::string> const& se::Request::getRequest() const
{
    return m_request;
}
