#include <iostream>
template <class Tkey, class Tvalue>
class ITable {
public:
    virtual void insert(const Tkey& key, const Tvalue& value) = 0;
    virtual void erase(const Tkey& key) = 0;
    virtual Tvalue& found(const Tkey& key) const = 0;
    virtual bool is_empty() const noexcept = 0;
    virtual void print(std::ostream& out) const = 0;
    friend std::ostream& operator << (std::ostream& out, const ITable& table);
};
