#ifndef REQUST_HPP
#define REQUST_HPP

#include "requestIF.hpp"

namespace se{

class Request : public RequestIF
{
public:
    explicit Request(std::string const& request);
    explicit Request(std::vector<std::string> const& request);
    Request(Request const& other) = default;
    Request& operator=(Request const& other) = default;
    virtual ~Request() = default;

    virtual std::vector<std::string> const& getRequest() const override;

private:
    std::vector<std::string> m_request;
};

}

#endif
