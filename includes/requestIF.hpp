#ifndef REQUST_IF_HPP
#define REQUST_IF_HPP

#include <string>
#include <vector>

namespace se{

class RequestIF//?
{
public:
    virtual ~RequestIF() = default;

    virtual std::vector<std::string> const& getRequest() const = 0;

};

}

#endif
