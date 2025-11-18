#pragma once
#include "../lib_list/List.h"
template <class T>
class QueueOnList {
private:
    List<T> _list;
public:
    QueueOnList() = default;
    QueueOnList(const QueueOnList<T>& other): _list(other._list){}
    ~QueueOnList() = default;
    inline T head() const;
    inline T tail() const;
    size_t size() const noexcept;
    bool is_empty() const noexcept;
    void push(T value);
    void pop();
    void clear() noexcept;
};
template <class T>
T QueueOnList<T>::head() const {
    if (_list.is_empty()) {
        throw std::runtime_error("Can't get head: queue is empty");
    }
    return *(_list.begin());
}
template <class T>
T QueueOnList<T>::tail() const {
    if (this->is_empty()) {
        throw std::runtime_error("Can't get tail: queue is empty");
    }
    return _list.get_last_element();
}
template <class T>
size_t QueueOnList<T>::size() const noexcept {
    return _list.get_size();
}
template <class T>
bool QueueOnList<T>::is_empty() const noexcept {
    return _list.is_empty();
}
template <class T>
void QueueOnList<T>::push(T value) {
    _list.push_back(value);
}
template <class T>
void QueueOnList<T>::pop() {
    if (_list.is_empty()) {
        throw std::logic_error("Can't pop from empty stack");
    }
    _list.pop_front();
}
template <class T>
void QueueOnList<T>::clear() noexcept {
    while (!_list.is_empty()) {
        _list.pop_front();
    }
}
