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

TEST(TestTriangleMatrixLib, tr_matrix_mult_value) {
    // Arrange
    size_t size = 3;
    int data[6] = { 1, 2, 3, 4, 5, 6 };
    int value = 10;
    TriangleMatrix<int> matrix(data, size);
    Matrix<int> result(size);
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
    int value = 2;
    TriangleMatrix<int> matrix(data, size);
    Matrix<int> result(size);
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

TEST(TestTriangleMatrixLib, tr_matrix_mult_assign_value) {
    // Arrange & Act
    size_t size = 3;
    int data[6] = { 1, 2, 3, 4, 5, 6 };
    int value = 10;
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
    int value = 2;
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
TEST(TestTriangleMatrixLib, tr_matrix_add_tr_matrix) {
    // Arrange
    size_t size = 3;
    int data1[6] = { 2, 2, 4, 4, 8, 6 };
    int data2[6] = { 1, 1, 1, 1, 1, 1 };
   
    TriangleMatrix<int> matrix1(data1, size);
    TriangleMatrix<int> matrix2(data2, size);
    TriangleMatrix<int> result(size);
    //Act
    result = matrix1 + matrix2;
    // Assert
    EXPECT_EQ(result.at(0).at(0), 3);
    EXPECT_EQ(result.at(0).at(1), 3);
    EXPECT_EQ(result.at(0).at(2), 5);
    EXPECT_EQ(result.at(1).at(1), 5);
    EXPECT_EQ(result.at(1).at(2), 9);
    EXPECT_EQ(result.at(2).at(2), 7);
}
TEST(TestTriangleMatrixLib, tr_matrix_sub_tr_matrix) {
    // Arrange
    size_t size = 3;
    int data1[6] = { 2, 2, 4, 4, 8, 6 };
    int data2[6] = { 1, 1, 1, 1, 1, 1 };

    TriangleMatrix<int> matrix1(data1, size);
    TriangleMatrix<int> matrix2(data2, size);
    TriangleMatrix<int> result(size);
    //Act
    result = matrix1 - matrix2;
    // Assert
    EXPECT_EQ(result.at(0).at(0), 1);
    EXPECT_EQ(result.at(0).at(1), 1);
    EXPECT_EQ(result.at(0).at(2), 3);
    EXPECT_EQ(result.at(1).at(1), 3);
    EXPECT_EQ(result.at(1).at(2), 7);
    EXPECT_EQ(result.at(2).at(2), 5);
}
TEST(TestTriangleMatrixLib, tr_matrix_add_assig_tr_matrix) {
    // Arrange & Act
    size_t size = 3;
    int data1[6] = { 2, 2, 4, 4, 8, 6 };
    int data2[6] = { 1, 1, 1, 1, 1, 1 };

    TriangleMatrix<int> matrix1(data1, size);
    TriangleMatrix<int> matrix2(data2, size);
    matrix1 += matrix2;
    // Assert
    EXPECT_EQ(matrix1.at(0).at(0), 3);
    EXPECT_EQ(matrix1.at(0).at(1), 3);
    EXPECT_EQ(matrix1.at(0).at(2), 5);
    EXPECT_EQ(matrix1.at(1).at(1), 5);
    EXPECT_EQ(matrix1.at(1).at(2), 9);
    EXPECT_EQ(matrix1.at(2).at(2), 7);
}
TEST(TestTriangleMatrixLib, tr_matrix_sub_assig_tr_matrix) {
    // Arrange & Act
    size_t size = 3;
    int data1[6] = { 2, 2, 4, 4, 8, 6 };
    int data2[6] = { 1, 1, 1, 1, 1, 1 };

    TriangleMatrix<int> matrix1(data1, size);
    TriangleMatrix<int> matrix2(data2, size);
    matrix1 -= matrix2;
    // Assert
    EXPECT_EQ(matrix1.at(0).at(0), 1);
    EXPECT_EQ(matrix1.at(0).at(1), 1);
    EXPECT_EQ(matrix1.at(0).at(2), 3);
    EXPECT_EQ(matrix1.at(1).at(1), 3);
    EXPECT_EQ(matrix1.at(1).at(2), 7);
    EXPECT_EQ(matrix1.at(2).at(2), 5);
}
TEST(TestTriangleMatrixLib, tr_matrix_add_tr_matrix_with_exception) {
    // Arrange & Act
   
    int data1[6] = { 2, 2, 4, 4, 8, 6 };
    int data2[4] = { 1, 1, 1, 1 };

    TriangleMatrix<int> matrix1(data1, 3);
    TriangleMatrix<int> matrix2(data2, 2);
 
    // Assert
    EXPECT_THROW(matrix1 + matrix2, std::logic_error);
}
TEST(TestTriangleMatrixLib, tr_matrix_sub_tr_matrix_with_exception) {
    // Arrange & Act

    int data1[6] = { 2, 2, 4, 4, 8, 6 };
    int data2[4] = { 1, 1, 1, 1 };

    TriangleMatrix<int> matrix1(data1, 3);
    TriangleMatrix<int> matrix2(data2, 2);

    // Assert
    EXPECT_THROW(matrix1 - matrix2, std::logic_error);
}
TEST(TestTriangleMatrixLib, tr_matrix_add_assign_tr_matrix_with_exception) {
    // Arrange & Act

    int data1[6] = { 2, 2, 4, 4, 8, 6 };
    int data2[4] = { 1, 1, 1, 1 };

    TriangleMatrix<int> matrix1(data1, 3);
    TriangleMatrix<int> matrix2(data2, 2);

    // Assert
    EXPECT_THROW(matrix1 += matrix2, std::logic_error);
}
TEST(TestTriangleMatrixLib, tr_matrix_sub_assign_tr_matrix_with_exception) {
    // Arrange & Act

    int data1[6] = { 2, 2, 4, 4, 8, 6 };
    int data2[4] = { 1, 1, 1, 1 };

    TriangleMatrix<int> matrix1(data1, 3);
    TriangleMatrix<int> matrix2(data2, 2);

    // Assert
    EXPECT_THROW(matrix1 -= matrix2, std::logic_error);
}
TEST(TestTriangleMatrixLib, tr_matrix_mult_vector) {
    // Arrange
    int data1[6] = { 2, 2, 4, 4, 8, 6 };
    int data2[3] = { 1, 1, 1 };

    TriangleMatrix<int> matrix(data1, 3);
    MathVector<int> vector(data2, 3);
    MathVector<int> result(3);
    //Act
    result = matrix * vector;
    // Assert
    EXPECT_EQ(result.at(0), 8);
    EXPECT_EQ(result.at(1), 12);
    EXPECT_EQ(result.at(2), 6);
}
TEST(TestTriangleMatrixLib, tr_matrix_mult_vector_with_exception) {
    // Arrange & Act
    int data1[6] = { 2, 2, 4, 4, 8, 6 };
    int data2[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    TriangleMatrix<int> matrix(data1, 3);
    MathVector<int> vector(data2, 10);
    MathVector<int> result(3);
    // Assert
    EXPECT_THROW(matrix * vector, std::logic_error);
}
TEST(TestTriangleMatrixLib, tr_matrix_mult_tr_matrix) {
    // Arrange
    size_t size = 3;
    int data1[6] = { 2, 2, 4, 4, 8, 6 };
    int data2[6] = { 1, 1, 1, 1, 1, 1 };
    TriangleMatrix<int> matrix1(data1, size);
    TriangleMatrix<int> matrix2(data2, size);
    TriangleMatrix<int> result(size);
    //Act
    result = matrix1 * matrix2;
    // Assert
    EXPECT_EQ(result.at(0).at(0), 2);
    EXPECT_EQ(result.at(0).at(1), 4);
    EXPECT_EQ(result.at(0).at(2), 8);
    EXPECT_EQ(result.at(1).at(1), 4);
    EXPECT_EQ(result.at(1).at(2), 12);
    EXPECT_EQ(result.at(2).at(2), 6);
}
TEST(TestTriangleMatrixLib, tr_matrix_mult_tr_matrix_with_exception) {
    // Arrange & Act
    int data1[6] = { 2, 2, 4, 4, 8, 6 };
    int data2[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    TriangleMatrix<int> matrix1(data1, 3);
    TriangleMatrix<int> matrix2(data2, 4);
    TriangleMatrix<int> result(3);
    // Assert
    EXPECT_THROW(matrix1 * matrix2, std::logic_error);
}
