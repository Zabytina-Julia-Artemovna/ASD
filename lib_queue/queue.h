#pragma once 
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
    Queue<T>& operator=(const Queue<T>& other);
    ~Queue();
    inline T head() const noexcept;
    inline T tail() const noexcept;
    bool is_empty() const noexcept;
    bool is_full() const noexcept;
    size_t size() const noexcept;
    void push(T value);
    void pop();
    void clear() noexcept;
};
template <class T>
Queue<T>::Queue(size_t size): _size(size), _head(0), _tail(0), _count(0) {
    _data = new T[size];
}
template <class T>
Queue<T>::Queue(const Queue<T>& other): _size(other._size), _head(other._head), _tail(other._tail), _count(0) {
    _data = new T[other._size];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
}
template <class T>
Queue<T>::~Queue() {
    delete _data;
    _data = nullptr;
}
