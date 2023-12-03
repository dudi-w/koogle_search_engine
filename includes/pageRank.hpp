#ifndef PAGE_RANK_HPP
#define PAGE_RANK_HPP

#include <string>
#include <unordered_map>
#include <atomic>

#include "safeUnorderedMap.hpp"
#include "safeUnorderedTable.hpp"

namespace se{

using MyMap = se::SafeUnorderedTable<std::string, std::string, size_t>;

class PageRank
{
public:
    PageRank();
    PageRank(PageRank const& other) = default;
    PageRank& operator=(PageRank const& other) = default;
    ~PageRank() = default;

    void reCalculatePageRank(se::MyMap const& linksMap);
    float getRank(std::string const& link) const;
    size_t lestUpCount() const;

private:
    se::SafeUnorderedMap<std::string, float> m_scoreMap;
    std::atomic_size_t m_lestUp;
};

}// namespace se

#endif
