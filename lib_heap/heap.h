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

    void siftUp(size_t index);
    void siftDown(size_t index, size_t heapSize);
    void maxSiftDown(size_t index, size_t heapSize);

public:
    Heap();
    ~Heap() = default;

    void insert(const TKey& key, const TValue& value);
    void erase(const TKey& key);
    void heap_sort();

    const TKey& getMinKey() const;
    const TValue& getMinValue() const;
    bool empty() const;
    size_t size() const;
    void print() const;
};
template <class TKey, class TValue>
Heap<TKey, TValue>::Heap() : _items() {}

template <class TKey, class TValue>
void Heap<TKey, TValue>::siftUp(size_t index) {
    while (index > 0 && _items[index].first < _items[getParentIndex(index)].first) {
        std::swap(_items[index], _items[getParentIndex(index)]);
        index = getParentIndex(index);
    }
}

template <class TKey, class TValue>
void Heap<TKey, TValue>::siftDown(size_t index, size_t heapSize) {
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

template <class TKey, class TValue>
void Heap<TKey, TValue>::maxSiftDown(size_t index, size_t heapSize) {
    while (true) {
        size_t largest = index;
        size_t left = getLeftChildIndex(index);
        size_t right = getRightChildIndex(index);

        if (left < heapSize && _items[left].first > _items[largest].first)
            largest = left;
        if (right < heapSize && _items[right].first > _items[largest].first)
            largest = right;

        if (largest == index) break;
        std::swap(_items[index], _items[largest]);
        index = largest;
    }
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
void Heap<TKey, TValue>::erase(const TKey& key) {
    if (_items.empty()) {
        throw std::runtime_error("Heap is empty");
    }

    size_t index = 0;
    bool found = false;
    for (size_t i = 0; i < _items.size(); ++i) {
        if (_items[i].first == key) {
            index = i;
            found = true;
            break;
        }
    }

    if (!found) {
        throw std::runtime_error("Key not found");
    }

    if (index == _items.size() - 1) {
        _items.pop_back();
        return;
    }

    std::swap(_items[index], _items[_items.size() - 1]);
    _items.pop_back();

    siftUp(index);
    siftDown(index, _items.size());
}

template <class TKey, class TValue>
void Heap<TKey, TValue>::heap_sort() {
    if (_items.empty()) return;
    size_t n = _items.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        maxSiftDown(i, n);
    }
    for (size_t i = n - 1; i > 0; --i) {
        std::swap(_items[0], _items[i]);
        maxSiftDown(0, i);
    }
}

template <class TKey, class TValue>
const TKey& Heap<TKey, TValue>::getMinKey() const {
    if (_items.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    return _items[0].first;
}

template <class TKey, class TValue>
const TValue& Heap<TKey, TValue>::getMinValue() const {
    if (_items.empty()) {
        throw std::runtime_error("Heap is empty");
    }
    return _items[0].second;
}
template <class TKey, class TValue>
bool Heap<TKey, TValue>::empty() const {
    return _items.empty();
}

template <class TKey, class TValue>
size_t Heap<TKey, TValue>::size() const {
    return _items.size();
}

template <class TKey, class TValue>
void Heap<TKey, TValue>::print() const {
    for (const auto& item : _items) {
        std::cout << "(" << item.first << ", " << item.second << ") ";
    }
    std::cout << "\n";
}
