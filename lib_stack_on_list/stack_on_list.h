#pragma once
#include "../lib_list/List.h"
#include <stdexcept>

template <class T>
class StackOnList {
private:
    List<T> _list;
    size_t _max_size;
    bool _has_max_size = false;
public:
    StackOnList(size_t size = 0);
    StackOnList(const StackOnList<T>& other);
    ~StackOnList() = default;
    StackOnList<T>& operator=(const StackOnList<T>& other);
    bool operator ==(const StackOnList<T>& other) const;
    bool operator !=(const StackOnList<T>& other) const;
    void push(T value);
    void pop();
    inline T top() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept;
    size_t size() const noexcept;
    size_t max_size() const noexcept;
    bool has_max_size() const noexcept;
};
template <class T>
StackOnList<T>::StackOnList(size_t size) {
    _max_size = size;
    if (_max_size != 0) {
        _has_max_size = true;
    }
}
template <class T>
StackOnList<T>::StackOnList(const StackOnList<T>& other) {
    _list = other._list;
    _max_size = other._max_size;
    _has_max_size = other._has_max_size;
}
template <class T>
size_t StackOnList<T>::size() const noexcept {
    return _list.get_size();
}
template <class T>
size_t StackOnList<T>::max_size() const noexcept {
    return _max_size;
}
template <class T>
bool StackOnList<T>::has_max_size() const noexcept {
    return _has_max_size;
}
template <class T>
StackOnList<T>& StackOnList<T>::operator=(const StackOnList<T>& other) {
    if (this != &other) {
        _list = other._list;
        _max_size = other._max_size;
        _has_max_size = other._has_max_size;
    }
    return *this;
}
template <class T>
bool StackOnList<T>::operator==(const StackOnList<T>& other) const {
    return this->_list == other._list;
}
template <class T>
bool StackOnList<T>::operator !=(const StackOnList<T>& other) const {
    return !(this->_list == other._list);
}
template <class T>
void StackOnList<T>::push(T value) {
    if (is_full()) {
        throw std::logic_error("Can't push the element: stack is full");
    }
    _list.push_front(value);
}
template <class T>
void StackOnList<T>::pop() {
    if (_list.is_empty()) {
        throw std::logic_error("Can't pop from empty stack");
    }
    _list.pop_front();
}
template <class T>
inline T StackOnList<T>::top() const {
    if (_list.is_empty()) {
        throw std::logic_error("Stack is empty, you can't get top element");
    }
    return *(_list.begin());
}
template <class T>
inline bool StackOnList<T>::is_empty() const noexcept {
    return _list.is_empty();
}
template <class T>
bool StackOnList<T>::is_full() const noexcept {
    if (_has_max_size == false) {
        return false;
    }
    return _max_size == _list.get_size();
}
template <class T>
void StackOnList<T>::clear() noexcept {
    while (!_list.is_empty()) {
        _list.pop_front();
    }
}
