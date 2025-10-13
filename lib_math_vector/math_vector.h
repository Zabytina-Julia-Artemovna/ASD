#pragma once
#include <stdexcept> 
#include "../lib_vector/vector.h"
template <class T>
class MathVector:public Tvector<T> {
protected:
    size_t _start_index = 0;
public:
    MathVector();
    MathVector(size_t size);
    MathVector(size_t size, size_t start_index);
    MathVector(T* data, size_t size);
    MathVector(T* data, size_t size, size_t start_index);
    MathVector(const MathVector<T>& other);
    virtual ~MathVector();

    size_t get_start_index() const { 
        return _start_index; 
    }
    void set_start_index(size_t index) { 
        _start_index = index; 
    }

    T& at(size_t index);
    const T& at(size_t index) const;

    MathVector<T> operator * (T value) const;
    MathVector<T> operator / (T value) const;

    MathVector<T>& operator *= (T value);
    MathVector<T>& operator /= (T value);

    MathVector<T> operator + (const MathVector<T>& vector) const;
    MathVector<T> operator - (const MathVector<T>& vector) const;
    T operator * (const MathVector<T>& vector) const;

    MathVector<T>& operator += (const MathVector<T>& vector);
    MathVector<T>& operator -= (const MathVector<T>& vector);
    MathVector<T>& operator=(const MathVector<T>& other);
    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const MathVector<U>& vector);
   
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
};
template<class T>
MathVector<T>::MathVector() : Tvector<T>() {}
template <class T>
MathVector<T>::MathVector(size_t size) : Tvector<T>(size) {}
template <class T>
MathVector<T>::MathVector(size_t size, size_t start_index) : Tvector<T>(size), _start_index(start_index) {}
template <class T>
MathVector<T>::MathVector(T* data, size_t size) : Tvector<T>(data, size) {} 
template <class T>
MathVector<T>::MathVector(T* data, size_t size, size_t start_index) : 
    Tvector<T>(data, size), _start_index(start_index) {}
template <class T>
MathVector<T>::MathVector(const MathVector<T>& other) : 
    Tvector<T>(other), _start_index(other._start_index) {}
template <class T>
MathVector<T>::~MathVector() = default;
template <class T>
MathVector<T> MathVector<T>::operator * (T value) const {
    MathVector<T> result(this->get_size());
    for (size_t i = 0; i < this->get_size(); ++i) {
        result[i] = (*this)[i] * value;
    }
    return result;
}
template <class T>
MathVector<T> MathVector<T>::operator / (T value) const {
    if (value == 0) {
        throw std::logic_error("Can't divide by zero!");
    }
    MathVector<T> result(this->get_size());
    for (size_t i = 0; i < this->get_size(); ++i) {
        result[i] = (*this)[i] / value;
    }
    return result;
}
template <class T>
MathVector<T>& MathVector<T>::operator *= (T value) {
    for (size_t i = 0; i < this->get_size(); ++i) {
        (*this)[i] *= value;
   }
    return *this;
}
template <class T>
MathVector<T>& MathVector<T>::operator /= (T value) {
    if (value == 0) {
        throw std::logic_error("Can't divide by zero!");
    }
    for (size_t i = 0; i < this->get_size(); ++i) {
        (*this)[i] /= value;
    }
    return *this;
}
template<class T>
MathVector<T> MathVector<T>::operator + (const MathVector<T>& vector) const {
    if (this->get_size() != vector.get_size()) {
        throw std::logic_error("Vectors must have the same dimension");
    }
    MathVector<T> result(this->get_size());
    for (size_t i = 0; i < this->get_size(); ++i) {
        result[i] = (*this)[i] + vector[i];
    }
    return result;
}
template<class T>
MathVector<T> MathVector<T>::operator - (const MathVector<T>& vector) const {
    if (this->get_size() != vector.get_size()) {
        throw std::logic_error("Vectors must have the same dimension");
    }
    MathVector<T> result(this->get_size());
    for (size_t i = 0; i < this->get_size(); ++i) {
        result[i] = (*this)[i] - vector[i];
    }
    return result;
}
template<class T>
T MathVector<T>::operator * (const MathVector<T>& vector) const {
    if (this->get_size() != vector.get_size()) {
        throw std::logic_error("Vectors must have the same dimension");
    }
    T result{};
    for (size_t i = 0; i < this->get_size(); ++i) {
        result += (*this)[i] * vector[i];
    }
    return result;
}
template<class T>
MathVector<T>& MathVector<T>::operator += (const MathVector<T>& vector)  {
    if (this->get_size() != vector.get_size()) {
        throw std::logic_error("Vectors must have the same dimension");
    }
    for (size_t i = 0; i < this->get_size(); ++i) { 
        (*this)[i] += vector[i];
    }
    return *this;
}
template<class T>
MathVector<T>& MathVector<T>::operator -= (const MathVector<T>& vector) {
    if (this->get_size() != vector.get_size()) {
        throw std::logic_error("Vectors must have the same dimension");
    }
    for (size_t i = 0; i < this->get_size(); ++i) {
        (*this)[i] -= vector[i];
    }
    return *this;
}
template <class T>
MathVector<T>& MathVector<T>::operator=(const MathVector<T>& other) {
    if (this != &other) {
        Tvector<T>::operator=(other);
        _start_index = other._start_index;
    }
    return *this;
}
template <class T>
T& MathVector<T>::operator[](size_t index) {
    return this->Tvector<T>::operator[](index - _start_index);
}
template <class T>
const T& MathVector<T>::operator[](size_t index) const {
    return this->Tvector<T>::operator[](index - _start_index);
}
template <class T>
T& MathVector<T>::at(size_t index) {
    if (index < _start_index || index >= _start_index + this->get_size()) {
        throw std::logic_error("MathVector index out of range");
    }
    return this->Tvector<T>::operator[](index - _start_index);
}
template <class T>
const T& MathVector<T>::at(size_t index) const {
    if (index < _start_index || index >= _start_index + this->get_size()) {
        throw std::std::logic_error("MathVector index out of range");
    }
    return this->Tvector<T>::operator[](index - _start_index);
}

template <class U>
std::ostream& operator<<(std::ostream& out, const MathVector<U>& vector) {
    out << "[";
    for (size_t i = 0; i < vector.get_size(); ++i) {
        out << vector[i];
        if (i < vector.get_size() - 1) {
            out << ", ";
        }
    }
    out << "]";
    return out;
}
