#pragma once
#include "../lib_list/List.h"
#include <stdexcept>

template <class T>
class StackOnList {
private:
    List<T> _list;
public:
    StackOnList() = default;
    StackOnList(const StackOnList<T>& other): _list(other._list){}
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
    size_t size() const noexcept {
        return _list.get_size();
    }
};
template <class T>
StackOnList<T>& StackOnList<T>::operator=(const StackOnList<T>& other) {
    if (this != &other) {
        this->_list = other._list;
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
        throw std::logic_error("Stack is empty, you can't get top element's index");
    }
    return *(_list.begin());
}
template <class T>
inline bool StackOnList<T>::is_empty() const noexcept {
    return _list.is_empty();
}
template <class T>
void StackOnList<T>::clear() noexcept {
    while (!_list.is_empty()) {
        _list.pop_front();
    }
}
