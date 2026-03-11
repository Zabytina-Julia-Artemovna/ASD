#pragma once
#include <stdexcept>
#include <utility>
#include "../lib_table/table.h"
#include "../lib_binary_tree/binary_tree.h"
template <class TKey, class TValue>
class UnsortedTableT : public Table<TKey, TValue> {
private:
    BinaryTree<TKey, TValue> _items;
    size_t _size = 0;
public:
    UnsortedTableT() = default;
    UnsortedTableT(const UnsortedTableT& other) = default;
    ~UnsortedTableT() override = default;
    UnsortedTableT<TKey, TValue>& operator=(const UnsortedTableT<TKey, TValue>& other) = default;
    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;
    TValue& find(const TKey& key) override;
    const TValue& find(const TKey& key) const override;

    bool is_empty() const noexcept override;
    size_t size() const noexcept override;
    void print(std::ostream& out) const override;
};
template <class TKey, class TValue>
void UnsortedTableT<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    TValue* element = _items.find(key);
    if (element) {
        throw std::invalid_argument("Key already exist");
    }
    _items.insert(key, value);
    _size++;
}
template <class TKey, class TValue>
void UnsortedTableT<TKey, TValue>::erase(const TKey& key) {
    TValue* element = _items.find(key);
    if (!element) {
        throw std::invalid_argument("Key not found");
    }
    _items.erase(key);
    _size--;
}
template <class TKey, class TValue>
TValue& UnsortedTableT<TKey, TValue>::find(const TKey& key) {
    const UnsortedTableT& const_this = static_cast<const UnsortedTableT&>(*this);
    const TValue& result = const_this.find(key);
    return const_cast<TValue&>(result);
}
template <class TKey, class TValue>
const TValue& UnsortedTableT<TKey, TValue>::find(const TKey& key) const {
    TValue* element = _items.find(key);
    if (!element) {
        throw std::invalid_argument("Element not found");
    }
    return *element;
}
template <class TKey, class TValue>
bool UnsortedTableT<TKey, TValue>::is_empty() const noexcept {
    return _items.is_empty();
}
template <class TKey, class TValue>
size_t UnsortedTableT<TKey, TValue>::size() const noexcept {
    return _size;
}
template <class TKey, class TValue>
void UnsortedTableT<TKey, TValue>::print(std::ostream& out) const {
    out << "Unsorted table on binary tree" << "\n";
    _items.traverse([&out](const std::pair<TKey, TValue>& item) {
        out << "  " << item.first << " : " << item.second << "\n"; //вывод применяется к каждому эл-ту дерева при обходе
        });
}
