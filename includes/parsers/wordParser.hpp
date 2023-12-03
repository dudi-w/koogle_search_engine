#ifndef WORD_PARSER_HPP
#define WORD_PARSER_HPP

#include <gumbo.h>
#include <regex>

#include "parser.hpp"

namespace se{

class WordParser : public Parser
{
public:
    WordParser();
    WordParser(WordParser const& other) = default;
    WordParser& operator=(WordParser const& other) = default;
    virtual ~WordParser() = default;

    virtual se::AnalyzPage pars(std::unique_ptr<se::Page> page) override;

private:
    void searchForWords(GumboNode* node);
    void splitWords(std::string const& text);
    void cleanText();
    void reset();

private:
    std::regex m_cleanTextRegex;
    std::vector<std::string> m_rowWords;
    std::vector<std::string> m_clwanWords;
};

}

#endif
