// Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <gtest/gtest.h>
#include "../lib_matrix/matrix.h"


TEST(TestMatrixLib, matrix_default_constructor) {
    // Arrange & Act
    Matrix<int> matrix;
    // Assert
    EXPECT_EQ(0, matrix.getM());
    EXPECT_EQ(0, matrix.getN());
    EXPECT_TRUE(matrix.is_empty());
}
TEST(TestMatrixLib, matrix_constructor_with_size) {
    // Arrange & Act
    size_t M = 100;
    size_t N = 100;
    Matrix<int> matrix(M, N);
    // Assert
    EXPECT_EQ(M, matrix.getM());
    EXPECT_EQ(N, matrix.getN());
}
TEST(TestMatrixLib, matrix_constructor_with_array_and_size) {
    // Arrange & Act
    size_t M = 2;
    size_t N = 2;
    int data[4] = { 1, 2, 3, 4 };
    Matrix<int> matrix(data, M, N);
    // Assert
    EXPECT_EQ(M, matrix.getM());
    EXPECT_EQ(N, matrix.getN());
    EXPECT_EQ(matrix[0][0], data[0]);
    EXPECT_EQ(matrix[0][1], data[1]);
    EXPECT_EQ(matrix[1][0], data[2]);
    EXPECT_EQ(matrix[1][1], data[3]);
}
TEST(TestMatrixLib, matrix_copy_constructor) {
    // Arrange & Act
    size_t M = 2;
    size_t N = 2;
    int data[4] = { 1, 2, 3, 4};
    Matrix<int> old_matrix(data, M, N);
    Matrix<int> new_matrix(old_matrix);
    // Assert
    EXPECT_EQ(old_matrix, new_matrix);
}
TEST(TestMatrixLib, matrix_assignment_operator) {
    // Arrange
    size_t M = 2, N = 2;
    int data1[4] = { 1, 2, 3, 4 };
    int data2[4] = { 5, 6, 7, 8 };
    Matrix<int> matrix1(data1, M, N);
    Matrix<int> matrix2(data2, M, N);
    // Act
    matrix1 = matrix2;
    // Assert
    EXPECT_EQ(matrix1, matrix2);
}
TEST(TestMatrixLib, matrix_mult_value) {
    // Arrange
    size_t M = 2, N = 2;
    int data[4] = { 1, 2, 3, 4 };
    int value = 10;
    Matrix<int> matrix(data, M, N);
    Matrix<int> result(M, N);
    // Act
    result = matrix * value;
    // Assert   
    EXPECT_EQ(result[0][0], data[0] * value);
    EXPECT_EQ(result[0][1], data[1] * value);
    EXPECT_EQ(result[1][0], data[2] * value);
    EXPECT_EQ(result[1][1], data[3] * value);
}
TEST(TestMatrixLib, matrix_div_value) {
    // Arrange
    size_t M = 2, N = 2;
    int data[4] = { 2, 2, 10, 4 };
    int value = 2;
    Matrix<int> matrix(data, M, N);
    Matrix<int> result(M, N);
    // Act
    result = matrix  / value;
    // Assert
    EXPECT_EQ(result[0][0], data[0] / value);
    EXPECT_EQ(result[0][1], data[1] / value);
    EXPECT_EQ(result[1][0], data[2] / value);
    EXPECT_EQ(result[1][1], data[3] / value);
}
TEST(TestMatrixLib, matrix_div_value_with_exception) {
    // Arrange & Act
    size_t M = 2, N = 2;
    int data[4] = { 1, 2, 3, 4 };
    int value = 0;
    Matrix<int> matrix(data, M, N);
    // Assert
    EXPECT_THROW(matrix / value;, std::logic_error);
}
TEST(TestMatrixLib, matrix_mult_assign_value) {
    // Arrange
    size_t M = 2, N = 2;
    int data[4] = { 2, 2, 10, 4 };
    int value = 2;
    Matrix<int> matrix(data, M, N);
    // Act
    matrix *= value;
    // Assert
    EXPECT_EQ(matrix[0][0], data[0] * value);
    EXPECT_EQ(matrix[0][1], data[1] * value);
    EXPECT_EQ(matrix[1][0], data[2] * value);
    EXPECT_EQ(matrix[1][1], data[3] * value);
}
TEST(TestMatrixLib, matrix_div_assign_value) {
    // Arrange
    size_t M = 2, N = 2;
    int data[4] = { 2, 2, 10, 4 };
    int value = 2;
    Matrix<int> matrix(data, M, N);
    // Act
    matrix /= value;
    // Assert
    EXPECT_EQ(matrix[0][0], data[0] / value);
    EXPECT_EQ(matrix[0][1], data[1] / value);
    EXPECT_EQ(matrix[1][0], data[2] / value);
    EXPECT_EQ(matrix[1][1], data[3] / value);
}
TEST(TestMatrixLib, matrix_div_assign_value_with_exception) {
    // Arrange & Act
    size_t M = 2, N = 2;
    int data[4] = { 1, 2, 3, 4 };
    int value = 0;
    Matrix<int> matrix(data, M, N);
    // Assert
    EXPECT_THROW(matrix /= value; , std::logic_error);
}
TEST(TestMatrixLib, matrix_add_matrix) {
    // Arrange
    size_t M = 2, N = 3;
    int data1[6] = { 2, 2, 10, 4, 5, 7 };
    int data2[6] = { 8, 2, 3, 0, 5, 7};

    Matrix<int> matrix1(data1, M, N);
    Matrix<int> matrix2(data2, M, N);
    Matrix<int> result(M, N);
    // Act
    result = matrix1 + matrix2;
    // Assert
    EXPECT_EQ(result[0][0], data1[0] + data2[0]);
    EXPECT_EQ(result[0][1], data1[1] + data2[1]);
    EXPECT_EQ(result[0][2], data1[2] + data2[2]);
    EXPECT_EQ(result[1][0], data1[3] + data2[3]);
    EXPECT_EQ(result[1][1], data1[4] + data2[4]);
    EXPECT_EQ(result[1][2], data1[5] + data2[5]);
}
TEST(TestMatrixLib, matrix_sub_matrix) {
    // Arrange
    size_t M = 2, N = 3;
    int data1[6] = { 2, 2, 10, 4, 5, 7 };
    int data2[6] = { 8, 2, 3, 0, 5, 7 };

    Matrix<int> matrix1(data1, M, N);
    Matrix<int> matrix2(data2, M, N);
    Matrix<int> result(M, N);
    // Act
    result = matrix1 - matrix2;
    // Assert
    EXPECT_EQ(result[0][0], data1[0] - data2[0]);
    EXPECT_EQ(result[0][1], data1[1] - data2[1]);
    EXPECT_EQ(result[0][2], data1[2] - data2[2]);
    EXPECT_EQ(result[1][0], data1[3] - data2[3]);
    EXPECT_EQ(result[1][1], data1[4] - data2[4]);
    EXPECT_EQ(result[1][2], data1[5] - data2[5]);
}
TEST(TestMatrixLib, matrix_add_matrix_with_exception) {
    // Arrange & Act
    size_t M1 = 2, N1 = 3;
    size_t M2 = 2, N2 = 2;

    int data1[6] = { 2, 2, 10, 4, 5, 7 };
    int data2[4] = { 8, 2, 3, 0 };

    Matrix<int> matrix1(data1, M1, N1);
    Matrix<int> matrix2(data2, M2, N2);
   
    // Assert
    EXPECT_THROW(matrix1 + matrix2, std::logic_error);
}
TEST(TestMatrixLib, matrix_sub_matrix_with_exception) {
    // Arrange & Act
    size_t M1 = 2, N1 = 3;
    size_t M2 = 2, N2 = 2;

    int data1[6] = { 2, 2, 10, 4, 5, 7 };
    int data2[4] = { 8, 2, 3, 0 };

    Matrix<int> matrix1(data1, M1, N1);
    Matrix<int> matrix2(data2, M2, N2);

    // Assert
    EXPECT_THROW(matrix1 - matrix2, std::logic_error);
}
TEST(TestMatrixLib, matrix_add_assign_matrix) {
    // Arrange
    size_t M = 2, N = 3;
    int data1[6] = { 2, 2, 10, 4, 5, 7 };
    int data2[6] = { 8, 2, 3, 0, 5, 7 };

    Matrix<int> matrix1(data1, M, N);
    Matrix<int> matrix2(data2, M, N);
    // Act
    matrix1 += matrix2;
    // Assert
    EXPECT_EQ(matrix1[0][0], data1[0] + data2[0]);
    EXPECT_EQ(matrix1[0][1], data1[1] + data2[1]);
    EXPECT_EQ(matrix1[0][2], data1[2] + data2[2]);
    EXPECT_EQ(matrix1[1][0], data1[3] + data2[3]);
    EXPECT_EQ(matrix1[1][1], data1[4] + data2[4]);
    EXPECT_EQ(matrix1[1][2], data1[5] + data2[5]);
}
TEST(TestMatrixLib, matrix_add_assign_matrix_with_exception) {
    // Arrange & Act
    size_t M1 = 2, N1 = 3;
    size_t M2 = 2, N2 = 2;
    int data1[6] = { 2, 2, 10, 4, 5, 7 };
    int data2[4] = { 8, 2, 3, 0 };
    Matrix<int> matrix1(data1, M1, N1);
    Matrix<int> matrix2(data2, M2, N2);
    // Assert
    EXPECT_THROW(matrix1 += matrix2, std::logic_error);
}
TEST(TestMatrixLib, matrix_sub_assign_matrix) {
    // Arrange
    size_t M = 2, N = 3;
    int data1[6] = { 2, 2, 10, 4, 5, 7 };
    int data2[6] = { 8, 2, 3, 0, 5, 7 };

    Matrix<int> matrix1(data1, M, N);
    Matrix<int> matrix2(data2, M, N);
    // Act
    matrix1 -= matrix2;
    // Assert
    EXPECT_EQ(matrix1[0][0], data1[0] - data2[0]);
    EXPECT_EQ(matrix1[0][1], data1[1] - data2[1]);
    EXPECT_EQ(matrix1[0][2], data1[2] - data2[2]);
    EXPECT_EQ(matrix1[1][0], data1[3] - data2[3]);
    EXPECT_EQ(matrix1[1][1], data1[4] - data2[4]);
    EXPECT_EQ(matrix1[1][2], data1[5] - data2[5]);
}
TEST(TestMatrixLib, matrix_sub_assign_matrix_with_exception) {
    // Arrange & Act
    size_t M1 = 2, N1 = 3;
    size_t M2 = 2, N2 = 2;
    int data1[6] = { 2, 2, 10, 4, 5, 7 };
    int data2[4] = { 8, 2, 3, 0 };
    Matrix<int> matrix1(data1, M1, N1);
    Matrix<int> matrix2(data2, M2, N2);
    // Assert
    EXPECT_THROW(matrix1 -= matrix2, std::logic_error);
}
TEST(TestMatrixLib, matrix_mult_matrix) {
    // Arrange
    size_t M1 = 2, N1 = 3, M2 = 3, N2 = 2;
   
    int data1[6] = { 2, 2, 1, 2, 1, 2 };
    int data2[6] = { 3, 2, 2, 1, 3, 2 };

    Matrix<int> matrix1(data1, M1, N1);
    Matrix<int> matrix2(data2, M2, N2);
    Matrix<int> result(M1, N2);
    // Act
    result = matrix1 * matrix2;
    // Assert
    EXPECT_EQ(result[0][0], 13);
    EXPECT_EQ(result[0][1], 8);
    EXPECT_EQ(result[1][0], 14);
    EXPECT_EQ(result[1][1], 9);
}
TEST(TestMatrixLib, matrix_mult_matrix_with_throw) {
    //Arrange & Act
    size_t M1 = 2, N1 = 3, M2 = 2, N2 = 2;

    int data1[6] = { 2, 2, 1, 2, 1, 2 };
    int data2[6] = { 3, 2, 2, 1 };

    Matrix<int> matrix1(data1, M1, N1);
    Matrix<int> matrix2(data2, M2, N2);
    //Assert
    EXPECT_THROW(matrix1 * matrix2, std::logic_error);
}
TEST(TestMatrixLib, matrix_mult_vector) {
    // Arrange
    size_t M = 2, N = 3, size = 3;
    int data1[6] = { 2, 3, 1, 4, 1, 2 };
    int data2[3] = { 2, 2, 2 };
    Matrix<int> matrix(data1, M, N);
    MathVector<int> vector(data2, size);
    MathVector<int> result(M);
    // Act
    result = matrix * vector;
    // Assert
    EXPECT_EQ(result[0], 12);
    EXPECT_EQ(result[1], 14);
}
TEST(TestMatrixLib, matrix_mult_vector_with_exception) {
    // Arrange & Act
    size_t M = 2, N = 3, size = 5;
    int data1[6] = { 2, 3, 1, 4, 1, 2 };
    int data2[5] = { 2, 2, 2, 6, 7 };
    Matrix<int> matrix(data1, M, N);
    MathVector<int> vector(data2, size);
    // Assert
    EXPECT_THROW(matrix * vector, std::logic_error);
}
TEST(TestMatrixLib, matrix_simple_assignment) {
    // Arrange
    Matrix<int> matrix1(2, 2);
    Matrix<int> matrix2(2, 2);
    matrix1[0][0] = 1;
    matrix1[0][1] = 2;
    matrix1[1][0] = 3;
    matrix1[1][1] = 4;
    matrix2[0][0] = 5;
    matrix2[0][1] = 6;
    matrix2[1][0] = 7;
    matrix2[1][1] = 8;
    //Act
    matrix1 = matrix2;
    // Проверяем
    EXPECT_EQ(matrix1[0][0], 5);
    EXPECT_EQ(matrix1[0][1], 6);
    EXPECT_EQ(matrix1[1][0], 7);
    EXPECT_EQ(matrix1[1][1], 8);
}
