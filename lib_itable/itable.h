#pragma once
template <class TKey, class TValue>
class ITable {
public:
    virtual size_t size() const noexcept = 0;
    virtual void insert(const TKey& key, const TValue& value) = 0;
    virtual void erase(const TKey& key) = 0;
    virtual TValue& find(const TKey& key) = 0;
    virtual const TValue& find(const TKey& key) const = 0;
    virtual bool is_empty() const noexcept = 0;
    virtual ~ITable() = default;
};
