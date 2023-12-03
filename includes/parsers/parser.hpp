#ifndef PARSER_HPP
#define PARSER_HPP

#include <memory>

#include "page.hpp"
#include "analyzPage.hpp"

namespace se{

class Parser
{
public:
    virtual ~Parser() = default;

    virtual se::AnalyzPage pars(std::unique_ptr<se::Page> const page) = 0;
};

}

#endif
