#ifndef PARSE_PAGE_HPP
#define PARSE_PAGE_HPP

#include <vector>

#include "basePage.hpp"

namespace se{//Search Engine

class AnalyzPage : public BasePage//?
{
public:
    using BasePage::BasePage;
    AnalyzPage(BasePage const& other);
    AnalyzPage& operator=(AnalyzPage const& other) = default;
    ~AnalyzPage() = default;

    std::vector<std::string> const& getLinks() const;
    std::vector<std::string> const& getWords() const;
    void setLinks(std::vector<std::string> const& links);
    void setWords(std::vector<std::string> const& words);

private:
    std::vector<std::string> m_links;
    std::vector<std::string> m_words;
};

}//namespace se

#endif
