#include "linkParser.hpp"
#include "wordParser.hpp"
#include "linkWordParser.hpp"
#include "myExceptions.hpp"

se::LinkWordParser::LinkWordParser(LinkParser& linkParser, WordParser& wordParser)
: m_linkParser(linkParser)
, m_wordParser(wordParser)
{}

se::AnalyzPage se::LinkWordParser::pars(std::unique_ptr<se::Page> page)
{
    if(page == nullptr){
        throw se::InValidArg("nothing to pars");
    }
    std::unique_lock lock(m_mutex);
    se::AnalyzPage words = m_wordParser.pars(std::make_unique<se::BasePage>(*page));
    se::AnalyzPage links = m_linkParser.pars(std::make_unique<se::BasePage>(*page));
    se::AnalyzPage analyzPage(*page);
    analyzPage.setLinks(links.getLinks());
    analyzPage.setWords(words.getWords());
    return analyzPage;
}
