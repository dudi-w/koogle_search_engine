#ifndef SET_DB_HPP
#define SET_DB_HPP

#include <string>
#include <vector>

namespace se{//Search Engine

class SetDB
{
public:
    virtual ~SetDB() = default;

    virtual void insertLinks(std::string const& srclink, std::vector<std::string> const& links) = 0;
    virtual void insertLink(std::string const& srcLink, std::string const& link) = 0;
    virtual void insertWords(std::string const& srcLink, std::vector<std::string> const& words) = 0;
    virtual void log() const= 0;
};

}//namespace se

#endif
