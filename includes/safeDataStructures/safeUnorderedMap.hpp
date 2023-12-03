#ifndef SAFE_UNORDERED_MAP_HPP
#define SAFE_UNORDERED_MAP_HPP

#include <unordered_map>
#include <mutex>
#include <shared_mutex>
#include <functional>

namespace se{

template<typename K , typename V>
class SafeUnorderedMap
{
public: 
    SafeUnorderedMap() = default;
    SafeUnorderedMap(SafeUnorderedMap const& other) = delete;
    SafeUnorderedMap& operator=(SafeUnorderedMap const& other) = delete;
    ~SafeUnorderedMap() = default;

    void operator=(std::unordered_map<K , V> const otherMap);
    void insert(K const& key, V const & value , std::function<void(V& value)> funcIfExis);
    std::unordered_map<K ,V> getMap() const;
    bool exis(K const& element) const;
    V at(K const& key) const;
    size_t size() const;

private:
    std::unordered_map<K , V> m_unorderedMap;
    mutable std::shared_mutex m_mutex;
};

}// namespace se

#include "../src/safeDataStructures/safeUnorderedMap.inl"

#endif
