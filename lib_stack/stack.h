#pragma once
#include "../lib_vector/vector.h"
template <class T>
class Stack {
private:
    Tvector<T> _data;
public:
    Stack(size_t size);
    Stack(const Stack<T>& other);
    const Tvector<T>& getData() const;
    Stack<T>& operator=(const Stack<T>& other);
    bool operator ==(const Stack<T>& other) const;
    void push(T value);
    void pop();
    inline T top() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear() noexcept; 
};
template <class T>
Stack<T>::Stack(size_t size): _data(size) {}
template <class T>
Stack<T>::Stack(const Stack<T>& other): _data(other.getData()) {}
template <class T>
const Tvector<T>& Stack<T>::getData() const {
    return _data;
}
template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this != &other) {
        _data = other.getData();
    }
    return *this;
}

template <class T>

bool  Stack<T>::operator ==(const Stack<T>& other) const {
    return _data == other.getData();
}

template <class T>
void Stack<T>::push(T value) {
    if (is_full()) {
        throw std::logic_error("You can't push the element, because stack is full");
    }
    _data.push_back(value);
}
template <class T>
void Stack<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("You can't pop the element, because stack is empty");
    }
    _data.pop_back();
}
