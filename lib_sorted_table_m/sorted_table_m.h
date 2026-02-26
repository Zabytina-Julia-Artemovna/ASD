#pragma once
#include <stdexcept>
#include "../lib_table/table.h"
#include "../lib_vector/vector.h"
template <class TKey, class TValue>
class SortedTableM : public Table<TKey, TValue> {
private:
    Tvector<std::pair<TKey, TValue>> _rows;
    std::pair<size_t, bool> find_position(const TKey& key) const { // O(logn)
        size_t left = 0;
        size_t right = _rows.get_size();
        while (left < right) {
            size_t middle = (left + right) / 2;
            if (_rows[middle].first > key) {
                right = middle;
            }
            else if (_rows[middle].first == key) {
                return { middle, true };
            }
            else {
                left = middle + 1;
            }
        }
        return { left, false };
    }
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
template <class TKey, class TValue>
SortedTableM<TKey, TValue>& SortedTableM<TKey, TValue>::operator=(const SortedTableM<TKey, TValue>& other) { // O(n)
    if (this != &other) {
        _rows = other._rows;
    }
    return *this;
}
template <class TKey, class TValue>
void SortedTableM<TKey, TValue>::insert(const TKey& key, const TValue& value) { // O(n)
    std::pair<size_t, bool> result = find_position(key);
    if (result.second == true) {
        throw std::invalid_argument("Key already exists");
    }
    _rows.insert(std::make_pair(key, value), result.first);
}
template <class TKey, class TValue>
void SortedTableM<TKey, TValue>::erase(const TKey& key) { // O(logn)
    std::pair<size_t, bool> result = find_position(key);
    if (result.second == false) {
        throw std::out_of_range("Key not found");
    }
    _rows.erase(result.first);
}
template <class TKey, class TValue>
TValue& SortedTableM<TKey, TValue>::find(const TKey& key) { // O(logn)
    const SortedTableM& const_this = static_cast<const SortedTableM&>(*this);
    const TValue& result = const_this.find(key);
    return const_cast<TValue&>(result);
}
template <class TKey, class TValue>
const TValue& SortedTableM<TKey, TValue>::find(const TKey& key) const { // O(logn)
    std::pair<size_t, bool> result = find_position(key);
    if (result.second == false) {
        throw std::out_of_range("Key not found");
    }
    return _rows[result.first].second;
}
template <class TKey, class TValue>
bool SortedTableM<TKey, TValue>::is_empty() const noexcept { // O(1)
    return _rows.is_empty();
}
template <class TKey, class TValue>
size_t SortedTableM<TKey, TValue>::size() const noexcept { // O(1)
    return _rows.get_size();
}
template <class TKey, class TValue>
void SortedTableM<TKey, TValue>::print(std::ostream& out) const { // O(n)
    out << "Sorted table on vector: \n";
    for (size_t i = 0; i < _rows.get_size(); i++) {
        out << "| " << _rows[i].first << " | " << _rows[i].second << " |\n";
    }
}