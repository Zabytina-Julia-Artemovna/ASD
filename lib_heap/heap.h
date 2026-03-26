#pragma once
#include <vector>
#include <algorithm>  
#include <iostream>
#include <stdexcept>
template <class TKey, class TValue>
class Heap {
private:
    std::vector<std::pair<TKey, TValue>> _items;
    size_t getParentIndex(size_t index) const {
        return (index - 1) / 2;
    }
    size_t getLeftChildIndex(size_t index) const {
        return 2 * index + 1;
    }
    size_t getRightChildIndex(size_t index) const {
        return 2 * index + 2;
    }
    void siftUp(size_t index) {
        while (index > 0 && _items[index].first < _items[getParentIndex(index)].first) { // key эл-та < key родителя - меняем их местами
            std::swap(_items[index], _items[getParentIndex(index)]);
            index = getParentIndex(index);
        }
    }
    void siftDown(size_t index, size_t heapSize) {
        size_t smallest = index; 
        size_t left = getLeftChildIndex(index);
        size_t right = getRightChildIndex(index);
        if (left < heapSize && _items[left].first < _items[smallest].first) {
            smallest = left;
        }
        if (right < heapSize && _items[right].first < _items[smallest].first) {
            smallest = right;
        }
        if (smallest != index) {
            std::swap(_items[index], _items[smallest]);
            siftDown(smallest, heapSize);
        }
    }
public:
    Heap() : _items() {}
    ~Heap() = default;
    void insert(const TKey& key, const TValue& value);
    void erase(const TKey& key);
    void heap_sort();
    void print() const;
    size_t size() const { 
        return _items.size();
    }
};
template <class TKey, class TValue>
void Heap<TKey, TValue>::print() const {
    for (const auto& item : _items) {
        std::cout << "(" << item.first << ", " << item.second << ") ";
    }
    std::cout << "\n";
}
template <class TKey, class TValue>
void Heap<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    for (const auto& item : _items) {
        if (item.first == key) {
            throw std::runtime_error("Key already exists in heap");
        }
    }
    _items.push_back(std::make_pair(key, value));
    siftUp(_items.size() - 1);
}
template <class TKey, class TValue>
void Heap<TKey, TValue>::heap_sort() {
    // Вариант 1: просто строим кучу из текущих элементов
    for (int i = _items.size() / 2 - 1; i >= 0; --i) {
        siftDown(i, _items.size());
    }

    // Сортируем
    for (size_t i = _items.size() - 1; i > 0; --i) {
        std::swap(_items[0], _items[i]);
        siftDown(0, i);
    }
}
template <class TKey, class TValue>
void Heap<TKey, TValue>::erase(const TKey& key) {
    if (_items.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    size_t index = 0;
    bool find = false;
    for (size_t i = 0; i != _items.size(); ++i) {
        if (_items[i].first == key) {
            index = i;
            find = true;
            break;
        }
    }
    if (!find) {
        throw std::runtime_error("Key not found");
    }
    if (index == _items.size()-1) {
        _items.pop_back();
        return; 
    }
    std::swap(_items[index], _items[_items.size()-1]);
    _items.pop_back();
    siftUp(index);
    siftDown(index, _items.size());
}
