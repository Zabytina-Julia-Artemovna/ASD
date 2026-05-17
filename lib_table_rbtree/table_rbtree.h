#pragma once
#include "../lib_rbtree/rbtree.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
class TableRBTree : public Table<TKey, TValue> {
private:
    RBTree<std::pair<TKey, TValue>> _items;
    size_t _size;

public:
    TableRBTree() : _size(0) {} 
    TableRBTree(const TableRBTree& other) = default;
    ~TableRBTree() override = default;

    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;
    TValue& find(const TKey& key) override;
    const TValue& find(const TKey& key) const override;

    bool is_empty() const noexcept override;
    size_t size() const noexcept override;
    void print(std::ostream& out) const override;
};
template <class TKey, class TValue>
bool TableRBTree<TKey, TValue>::is_empty() const noexcept {
    return _items.is_empty();
}
template <class TKey, class TValue>
size_t TableRBTree<TKey, TValue>::size() const noexcept {
    return _size;
}
template <class TKey, class TValue>
TValue& TableRBTree<TKey, TValue>::find(const TKey& key) {
    TValue* value = _items.find(key);
    if (!value) {
        throw std::invalid_argument("Key not found");
    }
    return *value;
}
template <class TKey, class TValue>
const TValue& TableRBTree<TKey, TValue>::find(const TKey& key) const {
    TValue* value = _items.find(key);
    if (!value) {
        throw std::invalid_argument("Key not found");
    }
    return *value;
}
template <class TKey, class TValue>
void TableRBTree<TKey, TValue>::print(std::ostream& out) const {
    out << "Sorted table on RB tree" << "\n";
    _items.traverse([&out](const std::pair<TKey, TValue>& item) {
        out << "  " << item.first << " : " << item.second << "\n";
        });
}
template <class TKey, class TValue>
void TableRBTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    if (_items.find(key)) {
        throw std::invalid_argument("Key already exists");
    }
    _items.insert({ key, value });
    _size++;
}
template <class TKey, class TValue>
void TableRBTree<TKey, TValue>::erase(const TKey& key) {
    if (!_items.find(key)) {
        throw std::invalid_argument("Key not found");
    }
    _items.erase(key);
    _size--;
}
