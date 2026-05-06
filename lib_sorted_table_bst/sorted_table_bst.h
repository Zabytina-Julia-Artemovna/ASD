#pragma once
#include "../lib_binary_search_tree/binary_search_tree.h"
#include "../lib_table/table.h"
template <class TKey, class TValue>
class SortedTableBST: public Table<TKey, TValue> {
private:
    BinarySearchTree<TKey, TValue> _items;
    size_t _size;

public:
    SortedTableBST() : _size(0) {}
    SortedTableBST(const SortedTableBST& other) = default;
    ~SortedTableBST() override = default;
    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;
    TValue& find(const TKey& key) override;
    const TValue& find(const TKey& key) const override;

    bool is_empty() const noexcept override;
    size_t size() const noexcept override;
    void print(std::ostream& out) const override;
};
template <class TKey, class TValue>
bool SortedTableBST<TKey, TValue>::is_empty() const noexcept {
    return _size == 0;
}
template <class TKey, class TValue>
size_t SortedTableBST<TKey, TValue>::size() const noexcept {
    return _size;
}
template <class TKey, class TValue>
void SortedTableBST<TKey, TValue>::erase(const TKey& key) {
    TValue* node = _items.find(key);
    if (!node) {
        throw std::invalid_argument("Key not found");
    }
    _items.erase(key);
    _size--;
}
template <class TKey, class TValue>
void SortedTableBST<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TValue* node = _items.find(key);
    if (node) {
        throw std::invalid_argument("Key already exist");
    }
    _items.insert(key, value);
    _size++;
}
template <class TKey, class TValue>
TValue& SortedTableBST<TKey, TValue>::find(const TKey& key) {
    const SortedTableBST& const_this = static_cast<const SortedTableBST&>(*this);
    const TValue& result = const_this.find(key);
    return const_cast<TValue&>(result);
}
template <class TKey, class TValue>
const TValue& SortedTableBST<TKey, TValue>::find(const TKey& key) const {
    TValue* value = _items.find(key);
    if (!value) {
        throw std::invalid_argument("Key not found");
    }
    return *value;
}
template <class TKey, class TValue>
void SortedTableBST<TKey, TValue>::print(std::ostream& out) const {
    out << "Sorted table on binary search tree" << "\n";
    _items.traverse([&out](const std::pair<TKey, TValue>& item) {
        out << "  " << item.first << " : " << item.second << "\n"; //вывод применяется к каждому эл-ту дерева при обходе
        });
}
