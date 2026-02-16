#pragma once
#include "../lib_list/List.h"
template <class Tkey, class Tvalue>
struct SkipListNode { //Мн-во указателей на первые узлы на каждом уровне списка
    std::pair <Tkey, Tvalue> data_;
    SkipListNode** next_;
    size_t height_;
public:
    SkipListNode();
    ~SkipListNode();
};
template <class Tkey, class Tvalue>
class SkipList {
    size_t _max_count_levels;
    size_t _current_count_levels;
    List<SkipListNode<Tkey, Tvalue>*> _heads;
public:
    SkipList();
    ~SkipList();
    void insert(const Tkey& key, const Tvalue& value);
    void print() const noexcept;
protected:
    size_t flip_coin() const noexcept; //возвращает рандомный уровень для insert нового элемента
    SkipListNode<Tkey, Tvalue>* find_nearest(const Tkey& key) const noexcept;
};
