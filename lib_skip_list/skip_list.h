#pragma once
#include "../lib_list/List.h"
#include <utility>
#include <random>
#include <iostream>
template <class TKey, class TValue>
struct TNode {
    TNode(int level, const TKey& key = TKey(), const TValue& value = TValue())
        : level_(level), data_(std::make_pair(key, value)) {
        next_ = new TNode* [level + 1]();  // () инициализирует все указатели nullptr
    }
    ~TNode() {
        delete[] next_;
    }
    size_t level_;
    std::pair<TKey, TValue> data_;
    TNode** next_; //указатель на указатель (массив указателей на след узлы для кажд уровня)
};
template <class TKey, class TValue>
class SkipList {
private:
    size_t _max_levels;
    size_t _current_count_levels;
    List<TNode<TKey, TValue>*> _heads;

    TNode<TKey, TValue>* get_head(size_t level) const {
        auto it = _heads.begin();
        for (size_t i = 0; i < level; ++i) {
            ++it;
        }
        return *it;
    }
    void set_head(size_t level, TNode<TKey, TValue>* node) {
        auto it = _heads.begin();
        for (size_t i = 0; i < level; ++i) {
            ++it;
        }
        *it = node;
    }
public:
    SkipList(size_t max_levels = 16);
    ~SkipList();
    void insert(const TKey& key, const TValue& value);
    void print() const noexcept;
    TValue& find(const TKey& key);
    const TValue& find(const TKey& key) const;

protected:
    size_t flip_coin() const noexcept;
    TNode<TKey, TValue>* find_nearest(const TKey& key) const noexcept;
};
template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList(size_t max_levels)
    : _max_levels(max_levels)
    , _current_count_levels(1) {

    TNode<TKey, TValue>* head = new TNode<TKey, TValue>(_max_levels);
    for (size_t i = 0; i <= _max_levels; ++i) {
        _heads.push_back(head);
    }
}
template <class TKey, class TValue>
SkipList<TKey, TValue>::~SkipList() {
    if (_heads.is_empty()) {
        return;
    }
    TNode<TKey, TValue>* head = get_head(0);     
    TNode<TKey, TValue>* current = head->next_[0];
    while (current != nullptr) {
        TNode<TKey, TValue>* next = current->next_[0];
        delete current;
        current = next;
    }
    delete head;
}
template <class TKey, class TValue>
size_t SkipList<TKey, TValue>::flip_coin() const noexcept {
    static thread_local std::random_device rd; // аппаратный генератор случайных чисел
    static thread_local std::mt19937 gen(rd()); //генератор, получив начальное число, может генерировать псевдослучайные числа
    static thread_local std::bernoulli_distribution dist(0.5); //преобразует числа от mt19937 в значения true или false с вер-тью 50 проц
    size_t level = 1;
    while (dist(gen) && level < _max_levels) {
        ++level;
    }
    return level;
}
template <class TKey, class TValue>
TNode<TKey, TValue>* SkipList<TKey, TValue>::find_nearest(const TKey& key) const noexcept { // поиск ближайший узел с ключом >= искомого
    if (_heads.is_empty()) {
        return nullptr;
    }
    TNode<TKey, TValue>* current = get_head(_current_count_levels - 1);

    for (int i = _current_count_levels - 1; i >= 0; --i) {
        while (current->next_[i] != nullptr && //пока на текущем уровне есть следующий узел && его ключ меньше искомого
            current->next_[i]->data_.first < key) {
            current = current->next_[i];
        }
    }
    return current->next_[0];
}
template <class TKey, class TValue>
TValue& SkipList<TKey, TValue>::find(const TKey& key) {
    const SkipList* const_this = static_cast<const SkipList*>(this);
    const TValue& const_result = const_this->find(key);
    TValue& result = const_cast<TValue&>(const_result);
    return result;
}
template <class TKey, class TValue>
const TValue& SkipList<TKey, TValue>::find(const TKey& key) const {
    TNode<TKey, TValue>* node = find_nearest(key);
    if (node != nullptr && node->data_.first == key) {
        return node->data_.second;
    }
    throw std::runtime_error("Key not found");
}
template <class TKey, class TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    size_t node_level = flip_coin();
    TNode<TKey, TValue>** update = new TNode<TKey, TValue>* [_max_levels + 1]; //массив указателей на элементы, 
                                                                               //которые будут перед новым узлом на каждом уровне
    TNode<TKey, TValue>* current = get_head(_current_count_levels - 1);

    for (int i = _current_count_levels - 1; i >= 0; --i) {
        while (current->next_[i] != nullptr &&
            current->next_[i]->data_.first < key) {
            current = current->next_[i];
        }
        update[i] = current; //это последний узел перед местом вставки на уровне i
    }
    current = current->next_[0];
    if (current != nullptr && current->data_.first == key) { // нашли узел с тем же ключом : просто обновл. значение
        current->data_.second = value;
        delete[] update; 
        return;
    }
    if (node_level > _current_count_levels) { // новый уровень выше текущего максимума
        for (size_t i = _current_count_levels; i < node_level; ++i) {
            update[i] = get_head(i);
        }
        _current_count_levels = node_level;
    }
    TNode<TKey, TValue>* newNode = new TNode<TKey, TValue>(node_level, key, value);
    for (int i = 0; i < node_level; ++i) { // вставляем узел на всех уровнях
        newNode->next_[i] = update[i]->next_[i];
        update[i]->next_[i] = newNode;
    }
    delete[] update; 
}
template <class TKey, class TValue>
void SkipList<TKey, TValue>::print() const noexcept {
    if (_heads.is_empty()) {
        std::cout << "Empty list" << std::endl;
        return;
    }
    // печатаем сверху вниз
    for (int i = _current_count_levels - 1; i >= 0; --i) {
        std::cout << "Level " << i << ": H -> ";
        TNode<TKey, TValue>* current = get_head(i)->next_[i];
        while (current != nullptr) {
            std::cout << "[" << current->data_.first
                << ":" << current->data_.second << "] -> ";
            current = current->next_[i];
        }
        std::cout << "nullptr" << std::endl;
    }
}
