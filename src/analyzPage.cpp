#include "parser.hpp"

se::AnalyzPage::AnalyzPage(BasePage const& other)
: BasePage(other)
{}

std::vector<std::string> const& se::AnalyzPage::getLinks() const
{
    return m_links;
}

std::vector<std::string> const& se::AnalyzPage::getWords() const
{
    return m_words;
}

void se::AnalyzPage::setLinks(std::vector<std::string> const& links)
{
    m_links = links;
}

void se::AnalyzPage::setWords(std::vector<std::string> const& words)
{
    m_words = words;
}
