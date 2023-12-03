#ifndef TUI_HPP
#define TUI_HPP

#include <memory>
#include <regex>

#include "queryBuilderIF.hpp"

namespace se{//Search Engin

class TextUI : public QueryBuilder
{
public:
    TextUI();
    TextUI(TextUI const& other) = default;
    TextUI& operator=(TextUI const& other) = default;
    ~TextUI() = default;

    virtual std::unique_ptr<se::RequestIF> makeRequest() override;
    virtual void recieveResult(se::Result& result) const override;

private:
    std::string m_request;
    std::regex const m_checkInput;
};

}

#endif

