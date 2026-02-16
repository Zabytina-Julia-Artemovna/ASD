#pragma once
#include "../lib_list/List.h"
template <class Tvalue, class Tkey>
struct Node { //Мн-во указателей на первые узлы на каждом уровне списка
    std::pair <Tkey, Tvalue> data_;
    Node** next_
public:
    Node();
    ~Node();
};
template <class Tvalue, class Tkey>
class SkipList {
    size_t _max_count_levels;
    size_t _current_count_levels;
    List<Node*> _heads;
public:
    void insert(const Tkey& key, const Tvalue& value);
    void print() const noexcept;
protected:
    size_t flip_coint() const noexcept;
    Node* find_nearest(const Tkey& key) const noexcept;
};
