#ifndef SAFE_UNORDERED_SET_INL
#define SAFE_UNORDERED_SET_INL

#include "safeUnorderedSet.hpp"

template<typename T>
bool se::SafeUnorderedSet<T>::insert(T const& element)
{
    std::unique_lock lock(m_mutex);
    return m_unorderedSet.insert(element).second;
}

template<typename T>
bool se::SafeUnorderedSet<T>::insert(T && element)
{
    std::unique_lock lock(m_mutex);
    return m_unorderedSet.insert(std::move(element)).second;
}

template<typename T>
bool se::SafeUnorderedSet<T>::removeElement(T const& element)
{
    std::unique_lock lock(m_mutex);
    auto it = m_unorderedSet.find(element);
    if(it == m_unorderedSet.cend()){
        return false;
    }
    m_unorderedSet.erase(it);
    return true;
}

template<typename T>
void se::SafeUnorderedSet<T>::clear()
{
    std::unique_lock lock(m_mutex);
    m_unorderedSet.clear();
}

template<typename T>
size_t se::SafeUnorderedSet<T>::count(T const& element) const
{
    std::shared_lock lock(m_mutex);
    return m_unorderedSet.count(element);
}

template<typename T>
bool se::SafeUnorderedSet<T>::exis(T const& element) const
{
    std::shared_lock lock(m_mutex);
    return m_unorderedSet.count(element);
}

template<typename T>
size_t se::SafeUnorderedSet<T>::size() const
{
    std::shared_lock lock(m_mutex);
    return m_unorderedSet.size();
}

template<typename T>
bool se::SafeUnorderedSet<T>::empty() const
{
    std::shared_lock lock(m_mutex);
    return m_unorderedSet.empty();
}

#endif
