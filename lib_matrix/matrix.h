#pragma once
#include <stdexcept>
#include "../lib_math_vector/math_vector.h"
template <class T>
class Matrix : public MathVector<MathVector<T>> {
protected:
    size_t _M;
    size_t _N;
    Matrix<T> transpose() const {
        Matrix<T> result(_N, _M);
        for (size_t i = 0; i < _M; ++i) {
            for (size_t j = 0; j < _N; ++j) {
                result[j][i] = (*this)[i][j];
            }
        }
        return result;
    }
public:
    Matrix();
    Matrix(size_t M, size_t N);
    Matrix(T* data, size_t M, size_t N);
    Matrix(const Matrix& other);
    virtual ~Matrix();
    size_t getM() const;
    size_t getN() const;

    Matrix<T> operator * (T value) const;
    Matrix<T> operator / (T value) const;

    Matrix<T>& operator *= (T value);
    Matrix<T>& operator /= (T value);

    Matrix<T> operator + (const Matrix<T>& other_matrix) const;
    Matrix<T> operator - (const Matrix<T>& other_matrix) const;
    Matrix<T> operator * (const Matrix<T>& other_matrix) const;

    MathVector<T> operator * (const MathVector<T>& vector) const;

    Matrix<T>& operator += (const Matrix<T>& other_matrix);
    Matrix<T>& operator -= (const Matrix<T>& other_matrix);
    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const Matrix<U>& matrix);
    
    Matrix<T>& operator=(const Matrix<T>& other);
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
Matrix<T> Matrix<T>::operator * (T value) const {
    Matrix result(_M, _N);
    for (size_t i = 0; i < _M; ++i) {
        result[i] = (*this)[i] * value;
    }
    return result;
}
template <class T>
Matrix<T> Matrix<T>::operator / (T value) const {
    if (value == 0) {
        throw std::logic_error("Division by zero!");
    }
    Matrix result(_M, _N);
    for (size_t i = 0; i < _M; ++i) {
        result[i] = (*this)[i] / value;
    }
    return result;
}
template <class T>
Matrix<T>& Matrix<T>::operator *= (T value) {
    for (size_t i = 0; i < _M; ++i) {
        (*this)[i] *= value;
    }
    return *this;
}
template <class T>
Matrix<T>& Matrix<T>::operator /= (T value) {
    if (value == 0) {
        throw std::logic_error("Division by zero!");
    }
    for (size_t i = 0; i < _M; ++i) {
            (*this)[i] /= value;
        }
    return *this;
}
template <class T>
Matrix<T> Matrix<T>::operator + (const Matrix<T>& other_matrix) const {
    if (_M != other_matrix.getM() || _N != other_matrix.getN()) {
        throw std::logic_error("The matrices have different sizes!");
    }
    Matrix<T> result(_M, _N);
    for (size_t i = 0; i < _M; ++i) {
        result[i] = (*this)[i] + other_matrix[i];
    }
    return result;
}
template <class T>
Matrix<T> Matrix<T>::operator - (const Matrix<T>& other_matrix) const {
    if (_M != other_matrix.getM() || _N != other_matrix.getN()) {
        throw std::logic_error("The matrices have different sizes!");
    }
    Matrix<T> result(_M, _N);
    for (size_t i = 0; i < _M; ++i) {
        result[i] = (*this)[i] - other_matrix[i];
    }
    return result;
}
template <class T>
Matrix<T> Matrix<T>::operator * (const Matrix<T>& other_matrix) const {
    if (_N != other_matrix.getM()) {
        throw std::logic_error
        ("The sizes of the matrices are not compatible for this operation!");
    }
    Matrix<T> result (_M, other_matrix.getN());
    Matrix<T> matrix_t = other_matrix.transpose();
    for (size_t i = 0; i < _M; ++i) {
        for (size_t j = 0; j < matrix_t.getM(); ++j) {
            result[i][j] = (*this)[i] * matrix_t[j];
        }
    }
    return result;
}
template <class T>
MathVector<T> Matrix<T>::operator * (const MathVector<T>& vector) const {
    if (_N != vector.get_size()) {
        throw std::logic_error
        ("Size of matrix aren't compatible with vector's size for this operation!");
    }
    MathVector<T> result(_M);
    for (size_t i = 0; i < _M; ++i) {
        result[i] = (*this)[i] * vector;

    }
    return result;
}
template <class T>
Matrix<T>& Matrix<T>::operator += (const Matrix<T>& other_matrix) {
    if (_M != other_matrix.getM() || _N != other_matrix.getN()) {
        throw std::logic_error("The matrices have different sizes!");
    }
    for (size_t i = 0; i < _M; ++i) {
        (*this)[i] += other_matrix[i];
    }
    return *this;
}
template <class T>
Matrix<T>& Matrix<T>::operator -= (const Matrix<T>& other_matrix) {
    if (_M != other_matrix.getM() || _N != other_matrix.getN()) {
        throw std::logic_error("The matrices have different sizes!");
    }
    for (size_t i = 0; i < _M; ++i) {
        (*this)[i] -= other_matrix[i];
    }
    return *this;
}
template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    MathVector<MathVector<T>>::operator=(other);
    _M = other._M;
    _N = other._N;
    return *this;
}
template <class U>
std::ostream& operator<<(std::ostream& out, const Matrix<U>& matrix) {
    for (size_t i = 0; i < matrix.getM(); ++i) {
        for (size_t j = 0; j < matrix.getN(); ++j) {
            out << matrix[i][j] << "\t";
        }
        out << std::endl;
    }
    return out;
}
