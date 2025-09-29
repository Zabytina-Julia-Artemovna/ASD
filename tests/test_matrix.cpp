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
