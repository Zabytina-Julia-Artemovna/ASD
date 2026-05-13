#pragma once
#include "../lib_avl_tree/avl_tree.h"
#include "../lib_table/table.h"
template <class TKey, class TValue>
class TableAVLTree : public Table<TKey, TValue> {
private:
    AVLTree<TKey, TValue> _items;
    size_t _size;
public:
    TableAVLTree() : _size(0) {}
    TableAVLTree(const TableAVLTree& other) = default;
    ~TableAVLTree() override = default;
    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;
    TValue& find(const TKey& key) override;
    const TValue& find(const TKey& key) const override;

    bool is_empty() const noexcept override;
    size_t size() const noexcept override;
    void print(std::ostream& out) const override;
};
template <class TKey, class TValue>
bool TableAVLTree<TKey, TValue>::is_empty() const noexcept {
    return _items.is_empty();
}
template <class TKey, class TValue>
size_t TableAVLTree<TKey, TValue>::size() const noexcept {
    return _size;
}
template <class TKey, class TValue>
TValue& TableAVLTree<TKey, TValue>::find(const TKey& key) {
    TValue* value = _items.find(key);
    if (!value) {
        throw std::invalid_argument("Key not found");
    }
    return *value;
}
template <class TKey, class TValue>
const TValue& TableAVLTree<TKey, TValue>::find(const TKey& key) const {
    TValue* value = _items.find(key);
    if (!value) {
        throw std::invalid_argument("Key not found");
    }
    return *value;
}
template <class TKey, class TValue>
void TableAVLTree<TKey, TValue>::print(std::ostream& out) const {
    out << "Sorted table on binary search tree" << "\n";
    _items.traverse([&out](const std::pair<TKey, TValue>& item) {
        out << "  " << item.first << " : " << item.second << "\n"; //вывод применяется к каждому эл-ту дерева при обходе
        });
}
template <class TKey, class TValue>
void TableAVLTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TValue* node = _items.find(key);
    if (node) {
        throw std::invalid_argument("Key already exist");
    }
    _items.insert(key, value);
    _size++;
}
template <class TKey, class TValue>
void TableAVLTree<TKey, TValue>::erase(const TKey& key)  {
    TValue* node = _items.find(key);
    if (!node) {
        throw std::invalid_argument("Key not found");
    }
    _items.erase(key);
    _size--;
}
