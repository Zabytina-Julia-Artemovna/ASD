#pragma once
#include "../lib_list/List.h"
template <class T>
class QueueOnList {
private:
    List<T> _list;
    size_t _max_size;  
    bool _has_max_size = false;
public:
    QueueOnList(size_t size = 0);
    QueueOnList(const QueueOnList<T>& other);
    ~QueueOnList() = default;
    QueueOnList<T>& operator=(const QueueOnList<T>& other);
    bool operator ==(const QueueOnList<T>& other) const;
    bool operator !=(const QueueOnList<T>& other) const;
    inline T head() const;
    inline T tail() const;
    size_t size() const noexcept;
    size_t max_size() const noexcept;
    bool has_max_size() const noexcept;
    bool is_empty() const noexcept;
    void push(T value);
    void pop();
    inline bool is_full() const noexcept;
    void clear() noexcept;
};
template <class T>
QueueOnList<T>::QueueOnList(size_t size) {
    _max_size = size;
    if (_max_size != 0) {
        _has_max_size = true;
    }
}
template <class T>
QueueOnList<T>::QueueOnList(const QueueOnList<T>& other) {
    _list = other._list;
    _max_size = other._max_size;
    _has_max_size = other._has_max_size;
}
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
size_t QueueOnList<T>::max_size() const noexcept {
    return _max_size;
}
template <class T>
bool QueueOnList<T>::has_max_size() const noexcept {
    return _has_max_size;
}
template <class T>
bool QueueOnList<T>::is_empty() const noexcept {
    return _list.is_empty();
}
template <class T>
void QueueOnList<T>::push(T value) {
    if (is_full()) {
        throw std::logic_error("Can't push element: queue is full");
    }
    _list.push_back(value);
}
template <class T>
void QueueOnList<T>::pop() {
    if (_list.is_empty()) {
        throw std::logic_error("Can't pop from empty queue");
    }
    _list.pop_front();
}
template <class T>
bool QueueOnList<T>::is_full() const noexcept {
    if (_has_max_size == false) {
        return false;
    }
    return _max_size == _list.get_size();
}
template <class T>
void QueueOnList<T>::clear() noexcept {
    while (!_list.is_empty()) {
        _list.pop_front();
    }
}
template <class T>
QueueOnList<T>& QueueOnList<T>::operator=(const QueueOnList<T>& other) {
    if (this != &other) {
        _list = other._list;
        _max_size = other._max_size;
        _has_max_size = other._has_max_size;
    }
    return *this;
}
template <class T>
bool QueueOnList<T>::operator ==(const QueueOnList<T>& other) const {
    return this->_list == other._list;
}
template <class T>
bool QueueOnList<T>::operator !=(const QueueOnList<T>& other) const {
    return !(this->_list == other._list);
}
