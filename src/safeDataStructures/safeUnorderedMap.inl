#ifndef SAFE_UNORDERED_MAP_INL
#define SAFE_UNORDERED_MAP_INL

#include "safeUnorderedMap.hpp"

template<typename K , typename V>
void se::SafeUnorderedMap<K , V>::operator=(std::unordered_map<K , V> const otherMap)
{
    std::unique_lock lock(m_mutex);
    m_unorderedMap = otherMap;
}

template<typename K , typename V>
void se::SafeUnorderedMap<K , V>::insert(K const& key , V const& value, std::function<void(V& value)> funcIfExis)
{
    std::unique_lock lock(m_mutex);
    if(!m_unorderedMap.count(key)){
        m_unorderedMap[key] = value;
    }else{
        funcIfExis(m_unorderedMap[key]);
    }
}

template<typename K , typename V>
std::unordered_map<K , V> se::SafeUnorderedMap<K , V>::getMap() const
{
    std::shared_lock lock(m_mutex);
    return m_unorderedMap;
}

template<typename K , typename V>
bool se::SafeUnorderedMap<K , V>::exis(K const& key) const
{
    std::shared_lock lock(m_mutex);
    return m_unorderedMap.count(key);
}

template<typename K , typename V>
V se::SafeUnorderedMap<K , V>::at(K const& key) const
{
    std::shared_lock lock(m_mutex);
    return m_unorderedMap.at(key);
}

template<typename K , typename V>
size_t se::SafeUnorderedMap<K , V>::size() const
{
    std::shared_lock lock(m_mutex);
    return m_unorderedMap.size();
}

#endif

