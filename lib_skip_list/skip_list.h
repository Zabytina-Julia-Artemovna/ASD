#pragma once
#include "../lib_vector/vector.h"
template <class TKey, class TValue>
struct Node {
    std::pair<TKey, TValue> data_;
    Node** next_;
    // конструктор и деструктор?
};
template <class TKey, class TValue>
class SkipList {
private:
    size_t _max_levels;
    size_t _current_levels;
    Tvector<Node<TKey, TValue>*> _heads;
public:
    SkipList();
    void insert(const TKey& key, const TValue& value);
    void print() const noexcept;
    TValue& find(const TKey& key);
    const TValue& find(const TKey& key) const;
protected:
    size_t flip_coin() const noexcept;
    Node* find_nearest(const TKey& key) const noexcept;
};
