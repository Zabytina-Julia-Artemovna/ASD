#pragma once
#include <stdexcept>
#include "../lib_table/table.h"
#include "../lib_list/List.h"
template <class TKey, class TValue>
class UnsortedTableL : public Table<TKey, TValue> {
private:
    List<std::pair<TKey, TValue>> _items;
public:
    UnsortedTableL() = default;
    UnsortedTableL(const UnsortedTableL& other) = default;
    ~UnsortedTableL() override = default;

    UnsortedTableL<TKey, TValue>& operator=(const UnsortedTableL<TKey, TValue>& other);
    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;
    TValue& find(const TKey& key) override;
    const TValue& find(const TKey& key) const override;

    bool is_empty() const noexcept override;
    size_t size() const noexcept override;
    void print(std::ostream& out) const override;
};
template <class TKey, class TValue>
UnsortedTableL<TKey, TValue>& UnsortedTableL<TKey, TValue>::operator=(const UnsortedTableL<TKey, TValue>& other) {
    if (this != &other) {
        _items = other._items;
    }
    return *this;
}
template <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    for (auto it = _items.begin(); it != _items.end(); it++) {
        if (it->first == key) {
            throw std::invalid_argument("Key already exists");
        }
    }
    _items.push_back(std::make_pair(key, value));
}
template <class TKey, class TValue>
size_t UnsortedTableL<TKey, TValue>::size() const noexcept {
    return _items.get_size();
}
template <class TKey, class TValue>
bool UnsortedTableL<TKey, TValue>::is_empty() const noexcept {
    return _items.is_empty();
}
template <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::erase(const TKey& key) {
    size_t current_position = 0;
    for (auto it = _items.begin(); it != _items.end(); it++) {
        if (it->first == key) {
            _items.erase(current_position);
            return;
        }
        current_position++;
    }
    throw std::out_of_range("Key not found");
}
template <class TKey, class TValue>
const TValue& UnsortedTableL<TKey, TValue>::find(const TKey& key) const {
    for (auto it = _items.begin(); it != _items.end(); it++) {
        if (it->first == key) {
            return it->second;
        }
    }
    throw std::out_of_range("Key not found");
}
template <class TKey, class TValue>
TValue& UnsortedTableL<TKey, TValue>::find(const TKey& key) {
    const UnsortedTableL& const_this = static_cast<const UnsortedTableL&>(*this);
    const TValue& result = const_this.find(key);
    return const_cast<TValue&>(result);
}
template <class TKey, class TValue>
void UnsortedTableL<TKey, TValue>::print(std::ostream& out) const {
    out << "Unsorted table on list: \n";
    for (auto it = _items.begin(); it != _items.end(); it++) {
        out << "| " << it->first << " | " << it->second << " |\n";
    }
}
