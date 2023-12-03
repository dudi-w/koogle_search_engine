#ifndef LINK_PARSER_HPP
#define LINK_PARSER_HPP

#include <gumbo.h>

#include "parser.hpp"

namespace se{//Search Engine

class LinkParser : public Parser
{
public:
    LinkParser() = default;
    LinkParser(LinkParser const& other) = default;
    LinkParser& operator=(LinkParser const& other) = default;
    virtual ~LinkParser() = default;

    virtual se::AnalyzPage pars(std::unique_ptr<se::Page> page) override;

private:
    void searchForLinks(GumboNode* node);
    void fixLinks(std::string const& srcUrl);
    std::string relToAbsLink(std::string const &baseUrl, std::string const &relUrl) const;
    void reset();

private:
    std::string m_srcPrefix;
    std::string m_srcHTTP;
    std::vector<std::string> m_links;
};

}//namespace se


#endif
