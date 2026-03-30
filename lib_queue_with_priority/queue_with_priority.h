#pragma once
#include "../lib_heap/heap.h"
#include <stdexcept>

template <class TKey, class TValue>
class QueueWithPriority {
private:
    Heap<TKey, TValue> _items;

public:
    QueueWithPriority() : _items() {}

    void push(const TKey& key, const TValue& value);
    void pop();
    TValue& top();                  
    const TValue& top() const;       
    size_t size() const noexcept;
    bool is_empty() const noexcept;
};

template <class TKey, class TValue>
void QueueWithPriority<TKey, TValue>::push(const TKey& key, const TValue& value) {
    _items.insert(key, value);
}

template <class TKey, class TValue>
void QueueWithPriority<TKey, TValue>::pop() {
    if (is_empty()) {
        throw std::runtime_error("Queue is empty");
    }
    const TKey& key = _items.getMinKey();
    _items.erase(key);
}

template <class TKey, class TValue>
TValue& QueueWithPriority<TKey, TValue>::top() {
    if (is_empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return _items.getMinValue();  
}

template <class TKey, class TValue>
const TValue& QueueWithPriority<TKey, TValue>::top() const {
    if (is_empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return _items.getMinValue(); 
}

template <class TKey, class TValue>
size_t QueueWithPriority<TKey, TValue>::size() const noexcept {
    return _items.size();
}

template <class TKey, class TValue>
bool QueueWithPriority<TKey, TValue>::is_empty() const noexcept {
    return _items.empty();
}