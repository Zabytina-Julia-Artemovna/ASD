#include <iostream>
template <class Tkey, class Tvalue>
class ITable {
public:
    virtual void insert(const Tkey& key, const Tvalue& value);
    virtual void erase(const Tkey& key);
    virtual Tvalue& found(const Tkey& key) const noexcept;
    virtual bool is_empty() const noexcept;
    virtual friend std::ostream& operator << (std::ostream& out, ITable& table);
};
