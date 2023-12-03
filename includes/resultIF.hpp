#ifndef RESULT_IF_HPP
#define RESULT_IF_HPP

#include <string>
#include <vector>

using LinkVec = std::vector<std::pair<std::string, size_t>>;

namespace se
{
class ResultIF//?
{
public:
    virtual ~ResultIF() = default;

    virtual LinkVec getResult() const = 0;
};

}//namespace se

#endif
