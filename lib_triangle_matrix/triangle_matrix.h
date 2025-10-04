#pragma once 
#include "../lib_matrix/matrix.h"
template <class T>
class TriangleMatrix: public Matrix<T> {
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
        for (size_t i = 0; i < matrix._M; ++i) {
            for (size_t j = 0; j < matrix._N; ++j) {
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
TriangleMatrix<T>::TriangleMatrix(): Matrix<T>() {}
template<class T>
TriangleMatrix<T>::TriangleMatrix(size_t N): MathVector<MathVector<T>>(N) {
    for (size_t i = 0; i < N; ++i) {
       
    }
}
template<class T>
TriangleMatrix<T>::TriangleMatrix(T* data, size_t size) {

}

template<class T>
TriangleMatrix<T>::TriangleMatrix(const TriangleMatrix& other) {

}

template<class T>
TriangleMatrix<T>::~TriangleMatrix() = default;
