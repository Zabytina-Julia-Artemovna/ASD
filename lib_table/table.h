#pragma once
#include <iostream>
#include "..\lib_itable\itable.h"
template <class TKey, class TValue>
class Table: public ITable<TKey, TValue> {
public:
    virtual void print(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Table<TKey, TValue>& table) {
        table.print(out);
        return out;
    }
};
