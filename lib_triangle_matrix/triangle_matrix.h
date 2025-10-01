#pragma once 
#include "../lib_matrix/matrix.h"
template <class T>
class TriangleMatrix : public Matrix<T> {
public: 
    TriangleMatrix();
    TriangleMatrix(size_t M, size_t N);
    TriangleMatrix(T* data, size_t M, size_t N);
    TriangleMatrix(const TriangleMatrix& other);
    ~TriangleMatrix();

    TriangleMatrix<T> operator + (T value) const;
    TriangleMatrix<T> operator - (T value) const;
    TriangleMatrix<T> operator * (T value) const;
    TriangleMatrix<T> operator / (T value) const;

    TriangleMatrix<T>& operator += (T value);
    TriangleMatrix<T>& operator -= (T value);
    TriangleMatrix<T>& operator *= (T value);
    TriangleMatrix<T>& operator /= (T value);

    MathVector<T> operator * (const MathVector<T>& vector) const;

    TriangleMatrix<T> operator + (const TriangleMatrix<T>& other_matrix) const;
    TriangleMatrix<T> operator - (const TriangleMatrix<T>& other_matrix) const;
    TriangleMatrix<T> operator * (const TriangleMatrix<T>& other_matrix) const;

    TriangleMatrix<T>& operator += (const TriangleMatrix<T>& other_matrix);
    TriangleMatrix<T>& operator -= (const TriangleMatrix<T>& other_matrix);

    friend std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& matrix) {
        for (size_t i = 0; i < matrix.getM(); ++i) {
            for (size_t j = 0; j < matrix.getN(); ++j) {
                out << matrix[i][j] << "\t";
            }
            out << std::endl;
        }
        return out;
    }
    TriangleMatrix<T>& operator= (const TriangleMatrix<T>& other);
};
template <class T>
TriangleMatrix<T>::TriangleMatrix() : Matrix<T>() {}
template <class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix& other) : Matrix<T>(other) {}
template <class T>
TriangleMatrix<T>::~TriangleMatrix() = default;
template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator + (T value) const {
    TriangleMatrix<T> matrix;
    return matrix;
}
template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator - (T value) const {
    TriangleMatrix<T> matrix;
    return matrix;
}
template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator * (T value) const {
    TriangleMatrix<T> matrix;
    return matrix;
}
template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator / (T value) const {
    TriangleMatrix<T> matrix;
    return matrix;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator += (T value) {
    return *this;
}
template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator -= (T value) {
    return *this;

}
template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator *= (T value) {
    return *this;
}
template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator /= (T value) {
    return *this;
}

template <class T>
MathVector<T> TriangleMatrix<T>::operator * (const MathVector<T>& vector) const {
    TriangleMatrix<T> matrix;
    return matrix;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator + (const TriangleMatrix<T>& other_matrix) const {
    TriangleMatrix<T> matrix;
    return matrix;
}
template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator - (const TriangleMatrix<T>& other_matrix) const {
    TriangleMatrix<T> matrix;
    return matrix;
}
template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator * (const TriangleMatrix<T>& other_matrix) const {
    TriangleMatrix<T> matrix;
    return matrix;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator += (const TriangleMatrix<T>& other_matrix) {
    return *this;
}
template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator -= (const TriangleMatrix<T>& other_matrix) {
    return *this;
}

template <class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator= (const TriangleMatrix<T>& other) {
    Matrix<T>::operator=(other);
    _M = other._M;
    _N = other._N;
    return *this;
}
