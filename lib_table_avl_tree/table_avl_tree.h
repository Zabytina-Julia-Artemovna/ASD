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
