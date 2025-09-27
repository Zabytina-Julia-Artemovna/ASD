#pragma once
#include <stdexcept> 
#include "../lib_vector/vector.h"
template <class T>
class MathVector : public Tvector<T> {
public:
    MathVector();
    MathVector(size_t size);
    MathVector(T* data, size_t size);
    MathVector(const MathVector<T>& other);
    virtual ~MathVector();
    MathVector<T> operator * (T value) const;
    MathVector<T> operator / (T value) const;

    MathVector<T>& operator *= (T value);
    MathVector<T>& operator /= (T value);

    MathVector<T> operator + (const MathVector<T>& vector) const;
    MathVector<T> operator - (const MathVector<T>& vector) const;
    T operator * (const MathVector<T>& vector) const;

    MathVector<T>& operator += (const MathVector<T>& vector);
    MathVector<T>& operator -= (const MathVector<T>& vector);
    friend std::ostream& operator<<(std::ostream& out, const MathVector<T>& vector) {
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
