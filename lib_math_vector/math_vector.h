#pragma once
#include "../lib_vector/vector.h"
template <class T>
class MathVector : public Tvector<T> {
public:
    MathVector();
    MathVector(size_t size);
    MathVector(T* data, size_t size);
    MathVector(const MathVector<T>& other);
    virtual ~MathVector();
};
template<class T>
MathVector<T>::MathVector() : Tvector<T>() {}
template <class T>
MathVector<T>::MathVector(size_t size) : Tvector<T>(size) {}
template <class T>
MathVector<T>::MathVector(T* data, size_t size) : Tvector<T>(data, size) {} 
template <class T>
MathVector<T>::MathVector(const MathVector<T>& other) : Tvector<T>(other) {}
template <class T>
MathVector<T>::~MathVector() = default;
