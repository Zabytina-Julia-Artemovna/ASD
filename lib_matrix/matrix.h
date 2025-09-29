#pragma once
#include <stdexcept>
#include "../lib_math_vector/math_vector.h"
template <class T>
class Matrix : public MathVector<MathVector<T>> {
protected:
    size_t _M;
    size_t _N;
public:
    Matrix();
    Matrix(size_t M, size_t N);
    Matrix(T* data, size_t M, size_t N);
    Matrix(const Matrix& other);
    virtual ~Matrix();
    size_t getM() const;
    size_t getN() const;

    Matrix<T> operator + (T value) const;
    Matrix<T> operator - (T value) const;
    Matrix<T> operator * (T value) const;
    Matrix<T> operator / (T value) const;

    Matrix<T>& operator += (T value);
    Matrix<T>& operator -= (T value);
    Matrix<T>& operator *= (T value);
    Matrix<T>& operator /= (T value);

    Matrix<T> operator + (const MathVector<T>& vector) const;
    Matrix<T> operator - (const MathVector<T>& vector) const;
    MathVector<T> operator * (const MathVector<T>& vector) const;

    Matrix<T>& operator += (const MathVector<T>& vector);
    Matrix<T>& operator -= (const MathVector<T>& vector);

    Matrix<T> operator + (const Matrix<T>& other_matrix) const;
    Matrix<T> operator - (const Matrix<T>& other_matrix) const;
    Matrix<T> operator * (const Matrix<T>& other_matrix) const;

    Matrix<T>& operator += (const Matrix<T>& other_matrix);
    Matrix<T>& operator -= (const Matrix<T>& other_matrix);
    Matrix<T>& operator *= (const Matrix<T>& other_matrix);
    friend std::ostream& operator<< (std::ostream& out, const Matrix<T>& matrix) {
        for (size_t i = 0; i < matrix.getM(); ++i) {
            for (size_t j = 0; j < matrix.getN(); ++j) {
                out << matrix[i][j] << "\t";
            }
            out << std::endl;
        }
        return out;
    }
    MathVector<T>& operator[](size_t index);
    const MathVector<T>& operator[](size_t index) const;
};
template <class T>
size_t Matrix<T>::getM() const {
    return _M;
}
template <class T>
size_t Matrix<T>::getN() const {
    return _N;
}

template <class T>
Matrix<T>::Matrix() : MathVector<MathVector<T>>(), _M(0), _N(0) {}
template <class T>
Matrix<T>::Matrix(size_t M, size_t N) : MathVector<MathVector<T>>(M) {
    _M = M;
    _N = N;
    for (size_t i = 0; i < _M; ++i) {
        (*this)[i] = MathVector<T>(_N);
    }
}
template <class T>
Matrix<T>::Matrix(T* data, size_t M, size_t N) : MathVector<MathVector<T>>(M) {
    _M = M;
    _N = N;
    for (size_t i = 0; i < _M; ++i) {
        (*this)[i] = MathVector<T>(data + i * _N, _N);
    }
}
template <class T>
Matrix<T>::Matrix(const Matrix& other) :
    MathVector<MathVector<T>>(other), _M(other._M), _N(other._N) {}
template <class T>
Matrix<T>::~Matrix() = default;

template <class T>
Matrix<T> Matrix<T>::operator + (T value) const {
    Matrix<T> matrix(_M, _N);
    for (size_t i = 0; i < _M; ++i) {
        for (size_t j = 0; j < _N; ++j) {
            matrix[i][j] = (*this)[i][j] + value
        }
    }
    return matrix;
}
template <class T>
Matrix<T> Matrix<T>::operator - (T value) const {
    Matrix<T> matrix(_M, _N);
    for (size_t i = 0; i < _M; ++i) {
        for (size_t j = 0; j < _N; ++j) {
            matrix[i][j] = (*this)[i][j] - value
        }
    }
    return matrix;
}
template <class T>
Matrix<T> Matrix<T>::operator * (T value) const {
    Matrix<T> matrix(_M, _N);
    for (size_t i = 0; i < _M; ++i) {
        for (size_t j = 0; j < _N; ++j) {
            matrix[i][j] = (*this)[i][j] * value
        }
    }
    return matrix;
}
template <class T>
Matrix<T> Matrix<T>::operator / (T value) const {
    Matrix<T> matrix(_M, _N);
    for (size_t i = 0; i < _M; ++i) {
        for (size_t j = 0; j < _N; ++j) {
            matrix[i][j] = (*this)[i][j] / value
        }
    }
    return matrix;
}

template <class T>
Matrix<T>& Matrix<T>::operator += (T value) {
    return *this;
}
template <class T>
Matrix<T>& Matrix<T>::operator -= (T value) {
    return *this;

}
template <class T>
Matrix<T>& Matrix<T>::operator *= (T value) {
    return *this;
}
template <class T>
Matrix<T>& Matrix<T>::operator /= (T value) {
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator + (const MathVector<T>& vector) const {
    Matrix<T> matrix;
    return matrix;
}
template <class T>
Matrix<T> Matrix<T>::operator - (const MathVector<T>& vector) const {
    Matrix<T> matrix;
    return matrix;
}
template <class T>
MathVector<T> Matrix<T>::operator * (const MathVector<T>& vector) const {
    MathVector<T> math_vector;
    return math_vector;
}

template <class T>
Matrix<T>& Matrix<T>::operator += (const MathVector<T>& vector) {
    return *this;
}
template <class T>
Matrix<T>& Matrix<T>::operator -= (const MathVector<T>& vector) {
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator + (const Matrix<T>& other_matrix) const {
    Matrix<T> matrix;
    return matrix;
}
template <class T>
Matrix<T> Matrix<T>::operator - (const Matrix<T>& other_matrix) const {
    Matrix<T> matrix;
    return matrix;
}
template <class T>
Matrix<T> Matrix<T>::operator * (const Matrix<T>& other_matrix) const {
    Matrix<T> matrix;
    return matrix;
}

template <class T>
Matrix<T>& Matrix<T>::operator += (const Matrix<T>& other_matrix) {
    return *this;
}
template <class T>
Matrix<T>& Matrix<T>::operator -= (const Matrix<T>& other_matrix) {
    return *this;
}
template <class T>
Matrix<T>& Matrix<T>::operator *= (const Matrix<T>& other_matrix) {
    return *this;
}
template <class T>
MathVector<T>& Matrix<T>::operator[](size_t index) {
    return MathVector<MathVector<T>>::operator[](index);
}
template <class T>
const MathVector<T>& Matrix<T>::operator[](size_t index) const {
    return MathVector<MathVector<T>>::operator[](index);
}
