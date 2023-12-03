#include <algorithm>

#include "result.hpp"

se::Result::Result(LinkVec result)
: m_result(result)
{}

se::Result::Result(LinkVec::iterator begin, LinkVec::iterator end)
: m_result(begin, end)
{}

se::LinkVec se::Result::getResult() const
{
    return m_result;
}

se::Result se::Result::operator-(Result const& other) const
{
    LinkVec this_result = this->getResult();
    LinkVec otherResult = other.getResult();
    auto it = otherResult.cbegin();
    while(it != otherResult.cend()){
        auto find = std::find_if(this_result.cbegin() ,this_result.cend(),[it](std::pair<std::string, float> const& pair){return pair.first == it->first;});
        if(find != otherResult.cend()){
            this_result.erase(find);
        }
        ++it;
    }
    return se::Result(this_result);
}

se::Result se::Result::operator|(Result const& other) const //Union operator
{
    LinkVec thisResult = this->getResult();
    LinkVec otherResult = other.getResult();
    auto it = otherResult.cbegin();
    while(it != otherResult.cend()){
        auto res = std::find_if(thisResult.begin() ,thisResult.end(), [it](std::pair<std::string, float>const& pair){return pair.first == it->first;});
        if(res == thisResult.cend()){
            thisResult.push_back(*it);
        }else{
            res->second = std::min(res->second ,it->second );
        }
        ++it;
    }
    return se::Result(thisResult);
}

se::Result se::Result::operator&(Result const& other) const //Intersection operator
{
    LinkVec result;
    LinkVec this_result = getResult();
    LinkVec otherResult = other.getResult();
    auto it = otherResult.cbegin();
    while(it != otherResult.cend()){
        auto find = std::find_if(this_result.cbegin() ,this_result.cend(), [it](std::pair<std::string, float>const& pair){return pair.first == it->first;});
        if(find != this_result.cend()){
            result.push_back({find->first, std::min(find->second ,it->second)});
        }
        ++it;
    }
    return se::Result(result);
}
