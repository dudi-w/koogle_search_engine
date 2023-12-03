#ifndef SEARCH_DB_HPP
#define SEARCH_DB_HPP

#include <string>
#include <vector>

#include "safeUnorderedTable.hpp"
#include "setDatabase.hpp"
#include "getDatabase.hpp"
#include "pageRank.hpp"

namespace se{//Search Engine

using StrC = std::string const&;
using MyMap = se::SafeUnorderedTable<std::string, std::string, size_t>;

class Matabase : public SetDB , public GetDB
{
public:
    Matabase();
    Matabase(Matabase const& other) = delete;
    Matabase& operator=(Matabase const& other) = delete;
    virtual ~Matabase() = default;

    virtual se::LinkVec getLinkOfWord(StrC word) const override;
    float getRank(std::string const& link) const;
    virtual void insertLinks(StrC srclink, std::vector<std::string> const& links) override;
    virtual void insertWords(StrC srcLink, std::vector<std::string> const& words) override;
    virtual void log() const override;
    virtual bool wordExis(StrC word) const override;

private:
    virtual void insertLink(StrC srcLink, StrC link) override;

private:
    se::MyMap m_safeWordsIndex;
    se::MyMap m_safeLinksMap;
    se::PageRank m_pageRank;
};

}//namespace se

#endif
