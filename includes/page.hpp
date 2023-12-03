#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>

namespace se{//Search Engine

class Page
{
public:
    virtual ~Page() = default;

    virtual std::string const& getSrc() const = 0;
    virtual std::string const& getBaseData() const = 0;
};

}//namespace se

#endif
