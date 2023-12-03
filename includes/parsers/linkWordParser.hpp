#ifndef LINK_WORD_PARSER_HPP
#define LINK_WORD_PARSER_HPP

#include <mutex>

#include "parser.hpp"
#include "wordParser.hpp"
#include "linkParser.hpp"

namespace se{//Search Engine

class LinkWordParser : public Parser
{
public:
    LinkWordParser(LinkParser& linkParser, WordParser& wordParser);
    LinkWordParser(LinkWordParser const& other) = default;
    LinkWordParser& operator=(LinkWordParser const& other) = default;
    virtual ~LinkWordParser() = default;

    virtual se::AnalyzPage pars(std::unique_ptr<se::Page> page) override;

private:
    Parser& m_linkParser;
    Parser& m_wordParser;
    std::mutex m_mutex;

};

}//namespace se

#endif
