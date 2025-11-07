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
    Queue(size_t size);
    Queue(const Queue<T>& other);
    ~Queue();

    inline T head() const noexcept;
    inline T tail() const noexcept;
    bool is_empty() const noexcept;
    void is_full() const noexcept;
    size_t size() const noexcept;
   
    void push(int value);
    void pop();
    
    void clear() noexcept;
};
