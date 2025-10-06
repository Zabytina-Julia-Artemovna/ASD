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
    size_t data_index = 0;
    for (size_t i = 0; i < size; ++i) {
        (*this)[i] = MathVector<T>(size - i, i);
        for (size_t j = i; j < size; ++j) {
            (*this)[i][j] = data[data_index++];
        }
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
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator + (T value) const {
    TriangleMatrix<T> result(this->getSize());
    for (size_t i = 0; i < result.getSize(); ++i) {
        for (size_t j = i; j < result.getSize(); ++j) {
            result[i][j] = (*this)[i][j] + value;
        }
    }
    return result;
}
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator - (T value) const {
    TriangleMatrix<T> result(this->getSize());
    for (size_t i = 0; i < result.getSize(); ++i) {
        for (size_t j = i; j < result.getSize(); ++j) {
            result[i][j] = (*this)[i][j] - value;
        }
    }
    return result;
}
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator * (T value) const {
    TriangleMatrix<T> result(this->getSize());
    for (size_t i = 0; i < result.getSize(); ++i) {
        for (size_t j = i; j < result.getSize(); ++j) {
            result[i][j] = (*this)[i][j] * value;
        }
    }
    return result;
}
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator / (T value) const {
    if (value == 0) {
        throw std::logic_error("Division by zero!");
    }
    TriangleMatrix<T> result(this->getSize());
    for (size_t i = 0; i < result.getSize(); ++i) {
        for (size_t j = i; j < result.getSize(); ++j) {
            result[i][j] = (*this)[i][j] / value;
        }
    }
    return result;
}
template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator += (T value) {
    for (size_t i = 0; i < this->getSize(); ++i) {
        for (size_t j = i; j < this->getSize(); ++j) {
            (*this)[i][j] += value;
        }
    }
    return *this;
}
template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator -= (T value) {
    for (size_t i = 0; i < this->getSize(); ++i) {
        for (size_t j = i; j < this->getSize(); ++j) {
            (*this)[i][j] -= value;
        }
    }
    return *this;
}
template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator *= (T value) {
    for (size_t i = 0; i < this->getSize(); ++i) {
        for (size_t j = i; j < this->getSize(); ++j) {
            (*this)[i][j] *= value;
        }
    }
    return *this;
}
template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator /= (T value) {
    if (value == 0) {
        throw std::logic_error("Division by zero!");
    }
    for (size_t i = 0; i < this->getSize(); ++i) {
        for (size_t j = i; j < this->getSize(); ++j) {
            (*this)[i][j] /= value;
        }
    }
    return *this;
}

template<class T>
MathVector<T> TriangleMatrix<T>::operator * (const MathVector<T>& vector) const {
    if (this->getSize() != vector.get_size() ) {
        throw std::logic_error("Matrix columns must equal vector size");
    }
    MathVector<T> result(this->getSize());
    for (size_t i = 0; i < this->getSize(); ++i) {
        result[i] = (*this)[i] * vector;
    }
    return result;
}
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator + (const TriangleMatrix<T>& other) const {
    if (this->getSize() != other.getSize()) {
        throw std::logic_error("Matrices must have the same size");
    }
    TriangleMatrix<T> result(this->getSize());
    for (size_t i = 0; i < this->getSize(); ++i) {
        for (size_t j = i; j < this->getSize(); ++j){
            result[i][j] = (*this)[i][j] + other[i][j];
        }
    }
    return result;
}
template<class T>
TriangleMatrix<T> TriangleMatrix<T>::operator - (const TriangleMatrix<T>& other) const {
    if (this->getSize() != other.getSize()) {
        throw std::logic_error("Matrices must have the same size");
    }
    TriangleMatrix<T> result(this->getSize());
    for (size_t i = 0; i < this->getSize(); ++i) {
        for (size_t j = i; j < this->getSize(); ++j){
            result[i][j] = (*this)[i][j] - other[i][j];
        }
    }
    return result;
}
template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator += (const TriangleMatrix<T>& other) {
    if (this->getSize() != other.getSize()) {
        throw std::logic_error("Matrices must have the same size");
    }
    for (size_t i = 0; i < this->getSize(); ++i) {
        for (size_t j = i; j < this->getSize(); ++j) {
            (*this)[i][j] += other[i][j];
        }
    }
    return *this;
}
template<class T>
TriangleMatrix<T>& TriangleMatrix<T>::operator -= (const TriangleMatrix<T>& other) {
    if (this->getSize() != other.getSize()) {
        throw std::logic_error("Matrices must have the same size");
    }
    for (size_t i = 0; i < this->getSize(); ++i) {
        for (size_t j = i; j < this->getSize(); ++j) {
            (*this)[i][j] -= other[i][j];
        }
    }
    return *this;
}
