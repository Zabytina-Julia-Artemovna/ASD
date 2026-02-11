#include "../lib_itable/itable.h"
#include "../lib_vector/vector.h"
template <class Tkey, class Tvalue>
struct TPair {
    Tkey key;
    Tvalue value;
};
template <class Tkey, class Tvalue>
class UnsortedTableM : ITable<Tkey, Tvalue> {
private:
    Tvector<std::pair<Tkey, Tvalue>> _rows;
public:
    void insert(Tkey key, Tvalue value) {
        _rows.push_back(value);
    }
    void erase(Tkey key) {
        _rows.erase(key);
    }
    Tvalue found(Tkey key) {
        //_rows.find?
    }
    UnsortedTableM();
    ~UnsortedTableM();
    bool is_empty();
    std::ostream& operator<<(std::ostream& out, const UnsortedTableM& table);
};
