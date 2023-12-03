#include <regex>

#include "linkParser.hpp"
#include "myExceptions.hpp"
#include "tools.hpp"

void se::LinkParser::searchForLinks(GumboNode* node)
{
    if(node->type != GUMBO_NODE_ELEMENT){
        return;
    }
    GumboAttribute* href;
    if(node->v.element.tag == GUMBO_TAG_A && (href = gumbo_get_attribute(&node->v.element.attributes, "href"))){
        m_links.push_back(href->value);
    }
    GumboVector* children = &node->v.element.children;
    for(unsigned int i = 0; i < children->length; ++i){
        searchForLinks(static_cast<GumboNode*>(children->data[i]));
    }
}

void se::LinkParser::fixLinks(std::string const& srcUrl)
{
    auto it = m_links.begin();
    while(it != m_links.end()){
        *it = relToAbsLink(srcUrl , *it);
        ++it;
    }
}

se::AnalyzPage se::LinkParser::pars(std::unique_ptr<se::Page> const page)
{
    if(page == nullptr){
        throw se::InValidArg("nothing to pars");
    }
    reset();
    tool::extractHTTP(page->getSrc(), m_srcHTTP);
    tool::extractPrefix(page->getSrc(), m_srcPrefix);
    GumboOutput* output = gumbo_parse(page->getBaseData().c_str());
    searchForLinks(output->root);
    fixLinks(page->getSrc());
    gumbo_destroy_output(&kGumboDefaultOptions, output);
    se::AnalyzPage analyzPage(*page);
    analyzPage.setLinks(m_links);
    return analyzPage;
}

std::string se::LinkParser::relToAbsLink(std::string const &srcUrl, std::string const &url) const
{
    auto startsWith = [](std::string const &s, std::string const &w){return !s.compare(0, w.size(), w);};
    if(startsWith(url, "http")){
        return url;
    }
    if(startsWith(url, "//")){
        return m_srcHTTP + url;
    }
    if(startsWith(url, "/")){
        return m_srcPrefix + url;
    }else{
        std::smatch r;
        std::regex e("^https?:\\/\\/(?:[a-zA-Z0-9]+)(?:\\.[a-zA-Z0-9]+)+\\/(?:[a-zA-Z0-9]+\\/)*");
        std::regex_search(srcUrl, r, e);
        std::string prefix = r[0].str();
        return prefix + url;
    }
}

void se::LinkParser::reset()
{
    m_links.clear();
    m_srcHTTP.clear();
    m_srcPrefix.clear();
}

