#ifndef SAFE_UNORDERED_TABLE_INL
#define SAFE_UNORDERED_TABLE_INL

#include "safeUnorderedTable.hpp"

template<typename K1 ,typename K2 ,typename V>
void se::SafeUnorderedTable<K1 ,K2 ,V>::insert(K1 const& key1 , K2 const& key2 , V const& value, std::function<void(V& value)> funcIfExis)
{
    std::unique_lock lock(m_mutex);
    if(!m_unorderedTable.count(key1) || !m_unorderedTable.at(key1).count(key2)){
        m_unorderedTable[key1][key2] = value;
    }else{
        funcIfExis(m_unorderedTable[key1][key2]);
    }
}

template<typename K1 ,typename K2 ,typename V>
std::unordered_map<K1 ,std::unordered_map<K2 ,V>> se::SafeUnorderedTable<K1 ,K2 ,V>::getTable() const
{
    std::shared_lock lock(m_mutex);
    return m_unorderedTable;
}

template<typename K1 , typename K2 , typename V>
bool se::SafeUnorderedTable<K1 ,K2 ,V>::exis(K1 const& key1) const
{
    std::shared_lock lock(m_mutex);
    return m_unorderedTable.count(key1);
}

template<typename K1 , typename K2 , typename V>
std::unordered_map<K2 ,V> se::SafeUnorderedTable<K1 ,K2 ,V>::at(K1 const& key1) const
{
    std::shared_lock lock(m_mutex);
    return m_unorderedTable.at(key1);
}

template<typename K1 , typename K2 , typename V>
size_t se::SafeUnorderedTable<K1 ,K2 ,V>::size() const
{
    std::shared_lock lock(m_mutex);
    return m_unorderedTable.size();
}

#endif
