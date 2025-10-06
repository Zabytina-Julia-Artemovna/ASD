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
TEST(TestTriangleMatrixLib, tr_matrix_add_value) {
    // Arrange
    size_t size = 3;
    int data[6] = { 1, 2, 3, 4, 5, 6 };
    size_t value = 10;
    TriangleMatrix<int> matrix(data, size);
    TriangleMatrix<int> result(size);
    //Act
    result = matrix + value;
    // Assert
    EXPECT_EQ(result.at(0).at(0), 11);
    EXPECT_EQ(result.at(0).at(1), 12);
    EXPECT_EQ(result.at(0).at(2), 13);
    EXPECT_EQ(result.at(1).at(1), 14);
    EXPECT_EQ(result.at(1).at(2), 15);
    EXPECT_EQ(result.at(2).at(2), 16);
}
TEST(TestTriangleMatrixLib, tr_matrix_sub_value) {
    // Arrange
    size_t size = 3;
    int data[6] = { 1, 2, 3, 4, 5, 6 };
    size_t value = 1;
    TriangleMatrix<int> matrix(data, size);
    TriangleMatrix<int> result(size);
    //Act
    result = matrix - value;
    // Assert
    EXPECT_EQ(result.at(0).at(0), 0);
    EXPECT_EQ(result.at(0).at(1), 1);
    EXPECT_EQ(result.at(0).at(2), 2);
    EXPECT_EQ(result.at(1).at(1), 3);
    EXPECT_EQ(result.at(1).at(2), 4);
    EXPECT_EQ(result.at(2).at(2), 5);
}
TEST(TestTriangleMatrixLib, tr_matrix_mult_value) {
    // Arrange
    size_t size = 3;
    int data[6] = { 1, 2, 3, 4, 5, 6 };
    size_t value = 10;
    TriangleMatrix<int> matrix(data, size);
    TriangleMatrix<int> result(size);
    //Act
    result = matrix * value;
    // Assert
    EXPECT_EQ(result.at(0).at(0), 10);
    EXPECT_EQ(result.at(0).at(1), 20);
    EXPECT_EQ(result.at(0).at(2), 30);
    EXPECT_EQ(result.at(1).at(1), 40);
    EXPECT_EQ(result.at(1).at(2), 50);
    EXPECT_EQ(result.at(2).at(2), 60);
}
TEST(TestTriangleMatrixLib, tr_matrix_div_value) {
    // Arrange
    size_t size = 3;
    int data[6] = { 2, 2, 4, 4, 8, 6 };
    size_t value = 2;
    TriangleMatrix<int> matrix(data, size);
    TriangleMatrix<int> result(size);
    //Act
    result = matrix / value;
    // Assert
    EXPECT_EQ(result.at(0).at(0), 1);
    EXPECT_EQ(result.at(0).at(1), 1);
    EXPECT_EQ(result.at(0).at(2), 2);
    EXPECT_EQ(result.at(1).at(1), 2);
    EXPECT_EQ(result.at(1).at(2), 4);
    EXPECT_EQ(result.at(2).at(2), 3);
}
TEST(TestTriangleMatrixLib, tr_matrix_div_value_with_exception) {
    // Arrange & Act
    size_t size = 3;
    int data[6] = { 2, 2, 4, 4, 8, 6 };
    size_t value = 0;
    TriangleMatrix<int> matrix(data, size);
    // Assert
    EXPECT_THROW(matrix / value, std::logic_error);
}
TEST(TestTriangleMatrixLib, tr_matrix_add_assign_value) {
    // Arrange & Act
    size_t size = 3;
    int data[6] = { 2, 2, 4, 4, 8, 6 };
    size_t value = 2;
    TriangleMatrix<int> matrix(data, size);
    matrix += value;
    // Assert
    EXPECT_EQ(matrix.at(0).at(0), 4);
    EXPECT_EQ(matrix.at(0).at(1), 4);
    EXPECT_EQ(matrix.at(0).at(2), 6);
    EXPECT_EQ(matrix.at(1).at(1), 6);
    EXPECT_EQ(matrix.at(1).at(2), 10);
    EXPECT_EQ(matrix.at(2).at(2), 8);
}
TEST(TestTriangleMatrixLib, tr_matrix_sub_assign_value) {
    // Arrange & Act
    size_t size = 3;
    int data[6] = { 2, 2, 4, 4, 8, 6 };
    size_t value = 2;
    TriangleMatrix<int> matrix(data, size);
    matrix -= value;
    // Assert
    EXPECT_EQ(matrix.at(0).at(0), 0);
    EXPECT_EQ(matrix.at(0).at(1), 0);
    EXPECT_EQ(matrix.at(0).at(2), 2);
    EXPECT_EQ(matrix.at(1).at(1), 2);
    EXPECT_EQ(matrix.at(1).at(2), 6);
    EXPECT_EQ(matrix.at(2).at(2), 4);
}
TEST(TestTriangleMatrixLib, tr_matrix_mult_assign_value) {
    // Arrange & Act
    size_t size = 3;
    int data[6] = { 1, 2, 3, 4, 5, 6 };
    size_t value = 10;
    TriangleMatrix<int> matrix(data, size);
    matrix *= value;
    // Assert
    EXPECT_EQ(matrix.at(0).at(0), 10);
    EXPECT_EQ(matrix.at(0).at(1), 20);
    EXPECT_EQ(matrix.at(0).at(2), 30);
    EXPECT_EQ(matrix.at(1).at(1), 40);
    EXPECT_EQ(matrix.at(1).at(2), 50);
    EXPECT_EQ(matrix.at(2).at(2), 60);
}
TEST(TestTriangleMatrixLib, tr_matrix_div_assign_value) {
    // Arrange & Act
    size_t size = 3;
    int data[6] = { 2, 2, 4, 4, 8, 6 };
    size_t value = 2;
    TriangleMatrix<int> matrix(data, size);
    matrix /= value;
    // Assert
    EXPECT_EQ(matrix.at(0).at(0), 1);
    EXPECT_EQ(matrix.at(0).at(1), 1);
    EXPECT_EQ(matrix.at(0).at(2), 2);
    EXPECT_EQ(matrix.at(1).at(1), 2);
    EXPECT_EQ(matrix.at(1).at(2), 4);
    EXPECT_EQ(matrix.at(2).at(2), 3);
}
