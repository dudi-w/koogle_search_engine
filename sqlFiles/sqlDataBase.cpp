#include <iostream>
#include <fstream>
#include <sstream>

#include "sqlDataBase.hpp"
#include "../includes/myExceptions.hpp"
#include "../includes/systemMonitor.hpp"

se::SqlDataBase::SqlDataBase()
: m_sqlite("seDB.sqlite")//TODO from configutation
{
    m_sqlite.execute(laodBuildDataBaseFile("sqlFiles/buildDB.sql"));//TODO from configutation
    se::SystemMonitor::setLogFunc([&](){log();});
}

void se::SqlDataBase::log() const
{
    const std::string countwords = m_sqlite.executeQuery("select count(*) from Word;")[0][1];
    const std::string countLinks = m_sqlite.executeQuery("SELECT count(DISTINCT Source) from Graph;")[0][1];
    std::clog<<"\033[3;32mEnd of storage\033[0m\n"<<std::endl;
    std::clog<<"\tNumber of words: "<<countwords<<std::endl;
    std::clog<<"\tThe number of links: "<<countLinks<<std::endl;
}

se::LinkVec se::SqlDataBase::getLinkOfWord(std::string const& word) const
{
    se::SqlResult res = m_sqlite.executeQuery("SELECT l.Path, wtl.Count\
                                                FROM WordToLink wtl\
                                                LEFT JOIN word w\
                                                ON w.ID = wtl.WordID\
                                                LEFT JOIN Link l\
                                                ON l.ID = wtl.LinkID\
                                                WHERE w.Token LIKE \"" + word + "\";");
    
    se::LinkVec vecResult;
    vecResult.reserve(res.size());
    for(auto& row : res){
        vecResult.push_back({row[1], std::stoull(row[3])});
    }
    return vecResult;
}

void se::SqlDataBase::insertLinks(std::string const& srcLink, std::vector<std::string> const& links)
{   
    if(!m_sqlite.executeQuery("SELECT 1 FROM Graph g LEFT JOIN Link l ON g.Source=l.ID WHERE l.path LIKE \"" + srcLink + "\" ;").size()){
        auto srcLinkID = m_sqlite.executeQuery("INSERT OR IGNORE INTO Link (Path) VALUES (\"" + srcLink +"\"); SELECT ID FROM Link WHERE path LIKE \""+ srcLink +"\";")[0][1];
        std::string sqlQuery;
        for(auto const& link : links){
            sqlQuery += "INSERT OR IGNORE INTO Link (Path) VALUES (\"" + link +"\");\
                        INSERT INTO Graph (Source, Destination, Count)\
                        VALUES ("+srcLinkID + "," + "(SELECT ID FROM Link WHERE path LIKE \""+ link + "\")" + ", COALESCE((SELECT Count FROM Graph WHERE Source = "+srcLinkID + " AND Destination = " + "(SELECT ID FROM Link WHERE path LIKE \""+ link + "\")" + ") + 1,1))\
                        ON CONFLICT(Source, Destination)\
                        DO UPDATE SET Count = Count + 1;";
        }
        auto start = std::chrono::high_resolution_clock::now();
        m_sqlite.execute(sqlQuery);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
        std::clog << "Execution insertLinks time: " << duration.count() << " microseconds\n";
    }else{
        throw se::StorageError("Double storage of URL = " + srcLink);
    }

}
void se::SqlDataBase::insertLink(std::string const& srcLinkID, std::string const& link)
{
    m_sqlite.execute("INSERT OR IGNORE INTO Link (Path) VALUES (\"" + link +"\");\
                        INSERT INTO Graph (Source, Destination, Count)\
                        VALUES ("+srcLinkID + ",(SELECT ID FROM Link WHERE path LIKE \""+ link + "\"), COALESCE((SELECT Count FROM Graph WHERE Source = "+srcLinkID + " AND Destination =(SELECT ID FROM Link WHERE path LIKE \""+ link + "\")) + 1,1))\
                        ON CONFLICT(Source, Destination)\
                        DO UPDATE SET Count = Count + 1;");

    // if(auto linksSize = m_sqlite.executeQuery("select count(*) from Link")[0][1] ; std::stoull(linksSize) - m_pageRank.lestUpCount() > 10){
    //     m_pageRank.reCalculatePageRank(m_safeLinksMap);
    // }
}

void se::SqlDataBase::insertWords(std::string const& srcLink, std::vector<std::string> const& words)
{

    auto linkID = m_sqlite.executeQuery("SELECT ID FROM Link WHERE path LIKE \""+ srcLink +"\";")[0][1];
    std::string sqlQuery;
    for(auto const & word : words){
        sqlQuery += "INSERT OR IGNORE INTO Word (Token) VALUES (\"" + word + "\");\
                    INSERT INTO WordToLink (WordID, LinkID, Count)\
                        VALUES ((SELECT ID FROM Word WHERE Token LIKE \""+ word +"\")," + linkID + ", COALESCE((SELECT Count FROM WordToLink WHERE WordID = (SELECT ID FROM Word WHERE Token LIKE \""+ word +"\") AND LinkID = " + linkID + ") + 1,1))\
                        ON CONFLICT(WordID, LinkID)\
                        DO UPDATE SET Count = Count + 1;";
    }
    auto start = std::chrono::high_resolution_clock::now();
    m_sqlite.execute(sqlQuery);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
    std::clog << "Execution insertWords time: " << duration.count() << " microseconds\n";
}

float se::SqlDataBase::getRank(std::string const& link) const
{
    auto linkID = m_sqlite.executeQuery("SELECT Score FROM Link WHERE path LIKE \""+ link +"\";")[0][1];
    return std::stof(linkID);
}

bool se::SqlDataBase::wordExis(std::string const& word) const
{
    return m_sqlite.executeQuery("SELECT 1 FROM Word WHERE Token LIKE \"" + word + "\" ;").size(); 
}

std::string se::SqlDataBase::laodBuildDataBaseFile(std::string const& BuildDataBaseFilePath)//must move to "tools.hpp"
{
    std::ifstream input_file(BuildDataBaseFilePath);
    if(!input_file.is_open()){
        throw std::runtime_error("load sql-script file failed ,check the file");
    }
    std::stringstream sql_script;
    sql_script << input_file.rdbuf();
    input_file.close();
    return sql_script.str();
}