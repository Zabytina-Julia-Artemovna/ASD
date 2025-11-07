#pragma once 
#include <stdexcept>
template <class T>
class Queue {
private:
    T* _data;
    size_t _size;
    size_t _head;
    size_t _tail;
    size_t _count;
public:
    explicit Queue(size_t size);
    Queue(const Queue<T>& other);
    ~Queue();
    inline T head() const;
    inline T tail() const;
    size_t size() const noexcept;
    size_t count() const noexcept;
    bool is_empty() const noexcept;
    bool is_full() const noexcept;
    void push(T value);
    void pop();
    void clear() noexcept;
};
template <class T>
Queue<T>::Queue(size_t size): _size(size), _head(0), _tail(0), _count(0) {
    _data = new T[size];
}
template <class T>
Queue<T>::Queue(const Queue<T>& other): _size(other._size), _head(other._head), _tail(other._tail), _count(other._count) {
    _data = new T[other._size];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
}
template <class T>
Queue<T>::~Queue() {
    delete[] _data;
    _data = nullptr;
}
template <class T>
inline T Queue<T>::head() const {
    if (this->is_empty()) {
        throw std::runtime_error("Can't get head: queue is empty");
    }
    return _data[_head];
}
template <class T>
inline T Queue<T>::tail() const {
    if (this->is_empty()) {
        throw std::runtime_error("Can't get tail: queue is empty");
    }
    return _data[(_tail + _size - 1) % _size];
}
template <class T>
size_t Queue<T>::size() const noexcept {
    return _size;
}
template <class T>
size_t Queue<T>::count() const noexcept {
    return _count;
}
template <class T>
bool Queue<T>::is_empty() const noexcept {
    return _count == 0;
}
template <class T>
bool Queue<T>::is_full() const noexcept {
    return _count == _size;
}
template <class T>
void  Queue<T>::push(T value) {
    if (this->is_full()) {
        throw std::logic_error("The queue is full, you can't push the element");
    }
    _data[_tail] = value;
    _tail = (_tail + 1) % _size;
    _count++;
}
template <class T>
void  Queue<T>::pop() {
    if (this->is_empty()) {
        throw std::logic_error("The queue is empty, you can't pop the element");
    }
    _head = (_head + 1) % _size;
    _count--;
}
template <class T>
void Queue<T>::clear() noexcept {
    _head = 0;
    _tail = 0;
    _count = 0;
}
