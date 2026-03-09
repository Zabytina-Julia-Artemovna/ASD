#pragma once
#include "../lib_list/List.h"
#include <utility>
#include <cstdlib>
template <class TKey, class TValue>
struct TNode {
    TNode();
    ~TNode();
    std::pair<TKey, TValue> data_;
    TNode** next_; //указатель на указатель (массив указателей)
};
template <class TKey, class TValue>
class SkipList {
private:
    size_t _max_levels;
    size_t _current_count_levels;
    List<TNode<TKey, TValue>*> _heads;
public:
    SkipList();
    ~SkipList();
    void insert(const TKey& key, const TValue& value);
    void print() const noexcept;
    TValue& find(const TKey& key);
    const TValue& find(const TKey& key) const;
protected:
    size_t flip_coin() const noexcept;
    TNode<TKey, TValue>* find_nearest(const TKey& key) const noexcept;
};
