#ifndef BASE_PAGE_HPP
#define BASE_PAGE_HPP

#include "page.hpp"

namespace se{
    
class BasePage : public Page
{
public:
    explicit BasePage(std::string const& src, std::string const& baseData);
    BasePage(BasePage const& other) = default;
    BasePage(Page const& other);
    BasePage& operator=(BasePage const& other) = default;
    virtual ~BasePage() = default;

    virtual std::string const& getSrc() const override final;
    virtual std::string const& getBaseData() const override final;

private:
    std::string const m_srcUrl;
    std::string const m_baseData;
};

}//namespace se

#endif
