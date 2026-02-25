#pragma once
#include <stdexcept>
#include "../lib_table/table.h"
#include "../lib_vector/vector.h"
template <class TKey, class TValue>
class UnsortedTableM : public Table<TKey, TValue> {
private:
    Tvector<std::pair<TKey, TValue>> _rows;
public:
    UnsortedTableM() = default;
    UnsortedTableM(const UnsortedTableM& other) = default;
    ~UnsortedTableM() override = default;

    UnsortedTableM<TKey, TValue>& operator=(const UnsortedTableM<TKey, TValue>& other);
    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;
    TValue& find(const TKey& key) override;
    const TValue& find(const TKey& key) const override;
     
    bool is_empty() const noexcept override;
    size_t size() const noexcept override;
    void print(std::ostream& out) const override;
};
template <class TKey, class TValue>
UnsortedTableM<TKey, TValue>& UnsortedTableM<TKey, TValue>::operator=(const UnsortedTableM<TKey, TValue>& other) { // O(n)
    if (this != &other) {
        _rows = other._rows;
    }
    return *this;
}
template <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::insert(const TKey& key, const TValue& value) { // O(n)
    for (size_t i = 0; i < _rows.get_size(); i++) {
        if (_rows[i].first == key) {
            throw std::invalid_argument("Key already exists");
        }
    }
    _rows.push_back(std::make_pair(key, value));
}
template <class TKey, class TValue>
size_t UnsortedTableM<TKey, TValue>::size() const noexcept { // O(1)
    return _rows.get_size();
}
template <class TKey, class TValue> 
bool UnsortedTableM<TKey, TValue>::is_empty() const noexcept { // O(1)
    return _rows.is_empty();
}
template <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::erase(const TKey& key) { // O(n)
    for (size_t i = 0; i < _rows.get_size(); i++) {
        if (_rows[i].first == key) {
            _rows.erase(i);
            return;
        }
    }
    throw std::out_of_range("Key not found");
}
template <class TKey, class TValue>
const TValue& UnsortedTableM<TKey, TValue>::find(const TKey& key) const { // O(n)
    for (size_t i = 0; i < _rows.get_size(); i++) {
        if (_rows[i].first == key) {
            return _rows[i].second;
        }
    }
    throw std::out_of_range("Key not found");
}
template <class TKey, class TValue>
TValue& UnsortedTableM<TKey, TValue>::find(const TKey& key) { // O(n)
    const UnsortedTableM& const_this = static_cast<const UnsortedTableM&>(*this);
    const TValue& result = const_this.find(key);
    return const_cast<TValue&>(result);
}
template <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::print(std::ostream& out) const { // O(n)
    out << "Unsorted table on vector: \n";
        for (size_t i = 0; i < _rows.get_size(); i++) {
            out << "| " << _rows[i].first << " | " << _rows[i].second << " |\n";
        }
}
