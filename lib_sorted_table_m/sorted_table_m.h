#pragma once
#include <stdexcept>
#include "../lib_table/table.h"
#include "../lib_vector/vector.h"
template <class TKey, class TValue>
class SortedTableM : public Table<TKey, TValue> {
private:
    Tvector<std::pair<TKey, TValue>> _rows;
public:
    SortedTableM() = default;
    SortedTableM(const SortedTableM& other) = default;
    ~SortedTableM() override = default;

    SortedTableM<TKey, TValue>& operator=(const SortedTableM<TKey, TValue>& other);
    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;
    TValue& find(const TKey& key) override;
    const TValue& find(const TKey& key) const override;

    bool is_empty() const noexcept override;
    size_t size() const noexcept override;
    void print(std::ostream& out) const override;
};
