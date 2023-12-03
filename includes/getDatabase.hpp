#ifndef GET_DB_HPP
#define GET_DB_HPP

#include <string>
#include <vector>
#include <unordered_map>

namespace se{//Search Engine

using LinkVec = std::vector<std::pair<std::string, size_t>>;

class GetDB 
{
public:
    virtual ~GetDB() = default;

    virtual se::LinkVec getLinkOfWord(std::string const& word) const = 0;
    virtual float getRank(std::string const& link) const = 0;
    virtual bool wordExis(std::string const& word) const = 0;
};

}//namespace se

#endif
