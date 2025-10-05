#pragma once 
#include "../lib_matrix/matrix.h"

template <class T>
class TriangleMatrix : public Matrix<T> {
public:
    TriangleMatrix();
    TriangleMatrix(size_t size);
    TriangleMatrix(T* data, size_t size);
    TriangleMatrix(const TriangleMatrix& other);
    ~TriangleMatrix();

    size_t getSize() const {
        return this->_M;
    }

    TriangleMatrix<T> operator + (T value) const;
    TriangleMatrix<T> operator - (T value) const;
    TriangleMatrix<T> operator * (T value) const;
    TriangleMatrix<T> operator / (T value) const;

    TriangleMatrix<T>& operator += (T value);
    TriangleMatrix<T>& operator -= (T value);
    TriangleMatrix<T>& operator *= (T value);
    TriangleMatrix<T>& operator /= (T value);

    MathVector<T> operator * (const MathVector<T>& vector) const;

    TriangleMatrix<T> operator + (const TriangleMatrix<T>& other) const;
    TriangleMatrix<T> operator - (const TriangleMatrix<T>& other) const;
    TriangleMatrix<T> operator * (const TriangleMatrix<T>& other) const;

    TriangleMatrix<T>& operator += (const TriangleMatrix<T>& other);
    TriangleMatrix<T>& operator -= (const TriangleMatrix<T>& other);
    TriangleMatrix<T>& operator= (const TriangleMatrix<T>& other);

    friend std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& matrix) {
        for (size_t i = 0; i < matrix.getSize(); ++i) {
            for (size_t j = 0; j < matrix.getSize(); ++j) {
                if (i <= j) {
                    out << matrix[i][j] << "\t";
                }
                else {
                    out << "0\t";
                }
            }
            out << std::endl;
        }
        return out;
    }
};
template<class T>
TriangleMatrix<T>::TriangleMatrix() : Matrix<T>() {}
template<class T>
TriangleMatrix<T>::TriangleMatrix(size_t size) : Matrix<T>(size, size) {
    for (size_t i = 0; i < size; ++i) {
        (*this)[i] = MathVector<T>(size - i, i);
    }
}
template<class T>
TriangleMatrix<T>::TriangleMatrix(T* data, size_t size) : Matrix<T>(size, size) {
    for (size_t i = 0; i < size; ++i) {
        (*this)[i] = MathVector<T>(data + i * size + i, size - i, i);
       
    }
}
template<class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix& other) : Matrix<T>(other) {}
template<class T>
TriangleMatrix<T>::~TriangleMatrix() = default;
template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator= (const TriangleMatrix<T>& other) {
    if (this != &other) {
        Matrix<T>::operator=(other);
    }
    return *this;
}
