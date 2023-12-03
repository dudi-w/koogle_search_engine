#ifndef SAFE_UNORDERED_SET_HPP
#define SAFE_UNORDERED_SET_HPP

#include <unordered_set>
#include <mutex>
#include <shared_mutex>

namespace se{

template<typename T>
class SafeUnorderedSet
{
public:
    SafeUnorderedSet() = default;
    SafeUnorderedSet(SafeUnorderedSet const& other) = delete;
    SafeUnorderedSet& operator=(SafeUnorderedSet const& other) = delete;
    ~SafeUnorderedSet() = default;

public:
    bool insert(T const& element);
    bool insert(T && element);
    bool removeElement(T const& element);
    size_t count(T const& element) const;
    bool exis(T const& element) const;
    size_t size() const;
    bool empty() const;
    void clear();

private:
    std::unordered_set<T> m_unorderedSet;
    mutable std::shared_mutex m_mutex;
};

}// namespace se

#include "../src/safeDataStructures/safeUnorderedSet.inl"

#endif
