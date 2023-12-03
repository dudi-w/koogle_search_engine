#include "basePage.hpp"

se::BasePage::BasePage(std::string const& src, std::string const& baseData)
: m_srcUrl(src)
, m_baseData(baseData)
{}

se::BasePage::BasePage(Page const& other)
: m_srcUrl(other.getSrc())
, m_baseData(other.getBaseData())
{}

std::string const& se::BasePage::getSrc() const
{
    return m_srcUrl;
}

std::string const& se::BasePage::getBaseData() const
{
    return m_baseData;
}
