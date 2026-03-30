#pragma once
#include "../lib_heap/heap.h"
template <class TKey, class TValue>
class QueueWithPriority {
private:
    Heap<TKey, TValue> _items;

public:
    QueueWithPriority() : _items() {};
    void push(const TKey& key, const TValue& value);
    void pop();
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
    const TKey& key = _items.getMinKey();
    _items.erase(key);

}
template <class TKey, class TValue>
const TValue& QueueWithPriority<TKey, TValue>::top() const {
    return _items.getMinValue();

}

template <class TKey, class TValue>
size_t QueueWithPriority<TKey, TValue>::size() const noexcept {
    return _items.size();
}
template <class TKey, class TValue>
bool QueueWithPriority<TKey, TValue>::is_empty() const noexcept{
    return _items.empty();
}
