#pragma once
template <class Tkey, class Tvalue>
class ITable {
public:
    virtual size_t size() const noexcept = 0;
    virtual void insert(const Tkey& key, const Tvalue& value) = 0;
    virtual void erase(const Tkey& key) = 0;
    virtual Tvalue& find(const Tkey& key) = 0;
    virtual const Tvalue& find(const Tkey&) const = 0;
    virtual bool is_empty() const noexcept = 0;
    virtual ~ITable() = default;
};
