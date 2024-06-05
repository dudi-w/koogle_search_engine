#ifndef SQL_DB_HPP
#define SQL_DB_HPP

#include <string>
#include <vector>

// #include "safeUnorderedTable.hpp"
#include "../includes/setDatabase.hpp"
#include "../includes/getDatabase.hpp"
#include "sqliteAPI.hpp"
// #include "../includes/pageRank.hpp"

namespace se{//Search Engine

using StrC = std::string const&;
// using MyMap = se::SafeUnorderedTable<std::string, std::string, size_t>;

class SqlDataBase : public SetDB , public GetDB
{
public:
    SqlDataBase();
    SqlDataBase(SqlDataBase const& other) = delete;
    SqlDataBase& operator=(SqlDataBase const& other) = delete;
    virtual ~SqlDataBase() = default;

    virtual se::LinkVec getLinkOfWord(StrC word) const override;
    float getRank(std::string const& link) const;
    virtual void insertLinks(StrC srclink, std::vector<std::string> const& links) override;
    virtual void insertWords(StrC srcLink, std::vector<std::string> const& words) override;
    virtual void log() const override;
    virtual bool wordExis(StrC word) const override;

private:
    std::string laodBuildDataBaseFile(std::string const& BuildDataBaseFilePath);
    virtual void insertLink(StrC srcLink, StrC link) override;

private:
    se::SqliteAPI m_sqlite;
    // se::MyMap m_safeWordsIndex;
    // se::MyMap m_safeLinksMap;
    // se::PageRank m_pageRank;//Page grade grade by Paige's ranking
};

}//namespace se

#endif
