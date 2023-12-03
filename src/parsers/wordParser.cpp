#include "wordParser.hpp"
#include "myExceptions.hpp"
#include "tools.hpp"

se::WordParser::WordParser()
: m_cleanTextRegex("(?=[^_])\\b(?:\\w+){3,}\\b(?:\\b|\\s)")
{}

void se::WordParser::searchForWords(GumboNode* node)
{
    if(node->type == GUMBO_NODE_TEXT){
        splitWords(static_cast<std::string>(node->v.text.text));
    }else if(node->type == GUMBO_NODE_ELEMENT && node->v.element.tag != GUMBO_TAG_SCRIPT && node->v.element.tag != GUMBO_TAG_STYLE){
        GumboVector* children = &node->v.element.children;
        for(unsigned int i = 0; i < children->length; ++i){
            searchForWords(static_cast<GumboNode*>(children->data[i]));
        }
        return;
    }else{
        return;
    }
}

void se::WordParser::splitWords(std::string const& text)
{
    std::stringstream ss(text);
    std::string word;

    while(ss >> word){
        m_rowWords.push_back(word);
    }
}


void se::WordParser::cleanText()
{
    auto it = m_rowWords.begin();
    while(it != m_rowWords.end()){
        std::smatch match;
        if(std::regex_search(*it, match, m_cleanTextRegex)){
            std::string word = static_cast<std::string>(match[0]);
            tool::makeLowercase(word);
            m_clwanWords.push_back(word);
        }
        ++it;
    }
}

se::AnalyzPage se::WordParser::pars(std::unique_ptr<se::Page> const page)
{
    if(page == nullptr){
        throw se::InValidArg("nothing to pars");
    }
    reset();
    GumboOutput* output = gumbo_parse(page->getBaseData().c_str());
    searchForWords(output->root);
    cleanText();
    se::AnalyzPage analyzPage(page->getSrc(), page->getBaseData());
    analyzPage.setWords(m_clwanWords);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
    return analyzPage;
}

void se::WordParser::reset()
{
    m_clwanWords.clear();
    m_rowWords.clear();
}
