//Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <gtest/gtest.h>
#include "../lib_triangle_matrix/triangle_matrix.h"
TEST(TestTriangleMatrixLib, tr_matrix_default_constructor) {
    // Arrange & Act
    TriangleMatrix<int> matrix;
    // Assert
    EXPECT_EQ(0, matrix.getSize());
    EXPECT_TRUE(matrix.is_empty());
}
TEST(TestTriangleMatrixLib, tr_matrix_constructor_with_size) {
    // Arrange & Act
    size_t size = 4;
    TriangleMatrix<int> matrix(size);
    // Assert
    EXPECT_EQ(size, matrix.getSize());
}
TEST(TestTriangleMatrixLib, tr_matrix_constructor_with_array_and_size) {
    // Arrange & Act
    size_t size = 3;
    int data[6] = { 1, 2, 3, 4, 5, 6 };
    TriangleMatrix<int> matrix(data, size);
    // Assert
    EXPECT_EQ(size, matrix.getSize());
    EXPECT_EQ(matrix.at(0).at(0), 1);
    EXPECT_EQ(matrix.at(0).at(1), 2);
    EXPECT_EQ(matrix.at(0).at(2), 3);
    EXPECT_EQ(matrix.at(1).at(1), 4); 
    EXPECT_EQ(matrix.at(1).at(2), 5);
    EXPECT_EQ(matrix.at(2).at(2), 6);
    EXPECT_THROW(matrix.at(1).at(0), std::logic_error);
    EXPECT_THROW(matrix.at(2).at(0), std::logic_error);
    EXPECT_THROW(matrix.at(2).at(1), std::logic_error);
}
TEST(TestTriangleMatrixLib, tr_matrix_copy_constructor) {
    // Arrange & Act
    size_t size = 3;
    int data[6] = { 1, 2, 3, 4, 5, 6 };
    TriangleMatrix<int> matrix1(data, size);
    TriangleMatrix<int> matrix2(matrix1);
    // Assert
    EXPECT_EQ(matrix1, matrix2);
}
TEST(TestTriangleMatrixLib, tr_matrix_operator_assignment) {
    // Arrange & Act
    size_t size = 3;
    int data[6] = { 1, 2, 3, 4, 5, 6 };
    TriangleMatrix<int> matrix1(data, size);
    TriangleMatrix<int> matrix2;
    matrix2 = matrix1;
    // Assert
    EXPECT_EQ(matrix1, matrix2);
}
