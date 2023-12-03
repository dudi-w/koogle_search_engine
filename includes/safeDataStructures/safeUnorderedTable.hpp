#ifndef SAFE_UNORDERED_TABLE_HPP
#define SAFE_UNORDERED_TABLE_HPP

#include <unordered_map>
#include <mutex>
#include <shared_mutex>
#include <functional>

namespace se{

template<typename K1 , typename K2 , typename V>
class SafeUnorderedTable
{
public:
    SafeUnorderedTable() = default;
    SafeUnorderedTable(SafeUnorderedTable const& other) = delete;
    SafeUnorderedTable& operator=(SafeUnorderedTable const& other) = delete;
    ~SafeUnorderedTable() = default;

    void insert(K1 const& key1 , K2 const& key2 , V const & value , std::function<void(V& value)> funcIfExis);
    std::unordered_map<K1 ,std::unordered_map<K2 ,V>> getTable() const;
    bool exis(K1 const& element) const;
    std::unordered_map<K2 ,V> at(K1 const& key1) const;
    size_t size() const;

private:
    std::unordered_map<K1 ,std::unordered_map<K2 ,V>> m_unorderedTable;
    mutable std::shared_mutex m_mutex;
};

}// namespace se

#include "../src/safeDataStructures/safeUnorderedTable.inl"

#endif
