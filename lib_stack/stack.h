#pragma once
#include "../lib_vector/vector.h"
template <class T>
class Stack {
private:
    Tvector<T> _data;
public:
    Stack(size_t size);
    Stack(const Stack& other);
    void push(int value);
    void pop();
    inline int top() const;
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void clear(); noexcept;
};
