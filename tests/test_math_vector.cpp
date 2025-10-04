// Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <gtest/gtest.h>
#include "../lib_math_vector/math_vector.h"
TEST(TestMathVectorLib, mathvector_default_constructor) {
    // Arrange & Act
    MathVector<int> vector;
    // Assert
    EXPECT_TRUE(vector.is_empty());
}
TEST(TestMathVectorLib, mathvector_constructor_with_size) {
    // Arrange & Act
    size_t size = 10;
    MathVector<int> vector(size);
    // Assert
    EXPECT_LE(vector.get_size(), vector.get_capacity());
    EXPECT_EQ(vector.get_size(), size);
}
TEST(TestMathVectorLib, mathvector_constructor_with_size_and_start_index) {
    // Arrange & Act
    size_t size = 10;
    size_t start_index = 1;
    MathVector<int> vector(size, start_index);
    // Assert
    EXPECT_LE(vector.get_size(), vector.get_capacity());
    EXPECT_EQ(vector.get_size(), size);
    EXPECT_EQ(vector.get_start_index(), start_index);
}
TEST(TestMathVectorLib, mathvector_constructor_with_array_and_size) {
    // Arrange & Act
    int data[3] = { 1,2,3 };
    size_t size = 3;
    MathVector<int> vector(data, size);
    // Assert
    EXPECT_EQ(vector.get_size(), size);
    EXPECT_EQ(vector[0], data[0]);
    EXPECT_EQ(vector[1], data[1]);
    EXPECT_EQ(vector[2], data[2]);
    EXPECT_LE(vector.get_size(), vector.get_capacity());
}
TEST(TestMathVectorLib, mathvector_constructor_with_array_and_size_and_start_index) {
    // Arrange & Act
    int data[3] = { 1,2,3 };
    size_t size = 3;
    size_t start_index = 1;
    MathVector<int> vector(data, size, start_index);
    // Assert
    EXPECT_EQ(vector.get_start_index(), start_index);
    EXPECT_EQ(vector.get_size(), size);
    EXPECT_EQ(vector[1], data[0]);
    EXPECT_EQ(vector[2], data[1]);
    EXPECT_EQ(vector[3], data[2]);
    EXPECT_LE(vector.get_size(), vector.get_capacity());
}
TEST(TestMathVectorLib, mathvector_copy_constructor) {
    // Arrange & Act
    int data[3] = { 1,2,3 };
    size_t size = 3;
    MathVector<int> old_vector(data, size);
    MathVector<int> new_vector(old_vector);
    // Assert
    EXPECT_EQ(old_vector.get_start_index(), new_vector.get_start_index());
    EXPECT_EQ(old_vector, new_vector);
}
TEST(TestMathVectorLib, mathvector_mult_on_value) {
    // Arrange & Act
    int data[3] = { 1,2,3 };
    size_t size = 3;
    int value = 5;
    MathVector<int> vector(data, size);
    MathVector<int> result;
    result = vector * value;
    // Assert
    EXPECT_EQ(result[0], vector[0] * value);
    EXPECT_EQ(result[1], vector[1] * value);
    EXPECT_EQ(result[2], vector[2] * value);
}
TEST(TestMathVectorLib, mathvector_div_on_value) {
    // Arrange & Act
    int data[3] = { 4,8,28 };
    size_t size = 3;
    int value = 2;
    MathVector<int> vector(data, size);
    MathVector<int> result;
    result = vector / value;
    // Assert
    EXPECT_EQ(result[0], vector[0] / value);
    EXPECT_EQ(result[1], vector[1] / value);
    EXPECT_EQ(result[2], vector[2] / value);
}
TEST(TestMathVectorLib, mathvector_div_on_null_exception) {
    // Arrange & Act
    int data[3] = { 10, 27, 21 };
    size_t size = 3;
    MathVector<int> vector(data, size);
    int value = 0;
    // Assert
    EXPECT_THROW(vector / value, std::logic_error);
}
TEST(TestMathVectorLib, mathvector_mult_assign_on_value) {
    // Arrange & Act
    int data[3] = { 3, 6, 0 };
    size_t size = 3;
    int value = 3;
    MathVector<int> vector(data, size);
    vector *= value;
    // Assert
    EXPECT_EQ(vector[0], data[0] * value);
    EXPECT_EQ(vector[1], data[1] * value);
    EXPECT_EQ(vector[2], data[2] * value);
}
TEST(TestMathVectorLib, mathvector_div_assign_on_value) {
    // Arrange & Act
    int data[3] = { 4,8,28 };
    size_t size = 3;
    int value = 2;
    MathVector<int> vector(data, size);
    vector /= value;
    // Assert
    EXPECT_EQ(vector[0], data[0] / value);
    EXPECT_EQ(vector[1], data[1] / value);
    EXPECT_EQ(vector[2], data[2] / value);
}
TEST(TestMathVectorLib, mathvector_div_assign_on_null_exception) {
    // Arrange & Act
    int data[3] = { 4,8,28 };
    size_t size = 3;
    int value = 0;
    MathVector<int> vector(data, size);
    // Assert
    EXPECT_THROW(vector /= value, std::logic_error);
}
TEST(TestMathVectorLib, mathvector_add_vector) {
    // Arrange & Act
    int data1[3] = { 4, 7 ,28 };
    size_t size1 = 3;

    int data2[3] = { 5, 0, 100 };
    size_t size2 = 3;

    MathVector<int> vector1(data1, size1);
    MathVector<int> vector2(data2, size2);
    MathVector<int> result;
    result = vector1 + vector2;
    // Assert
    EXPECT_EQ(result[0], vector1[0] + vector2[0]);
    EXPECT_EQ(result[1], vector1[1] + vector2[1]);
    EXPECT_EQ(result[2], vector1[2] + vector2[2]);
}
TEST(TestMathVectorLib, mathvector_sub_vector) {
    // Arrange & Act
    int data1[3] = { 4, 7 ,28 };
    size_t size1 = 3;

    int data2[3] = { 5, 0, 100 };
    size_t size2 = 3;

    MathVector<int> vector1(data1, size1);
    MathVector<int> vector2(data2, size2);
    MathVector<int> result;
    result = vector1 - vector2;
    // Assert
    EXPECT_EQ(result[0], vector1[0] - vector2[0]);
    EXPECT_EQ(result[1], vector1[1] - vector2[1]);
    EXPECT_EQ(result[2], vector1[2] - vector2[2]);
}
TEST(TestMathVectorLib, mathvector_scalar_product) {
    // Arrange & Act
    int data1[3] = { 4, 7 ,28 };
    size_t size1 = 3;

    int data2[3] = { 5, 0, 100 };
    size_t size2 = 3;

    MathVector<int> vector1(data1, size1);
    MathVector<int> vector2(data2, size2);
    int result = 0;
    int scalar_product =
        vector1[0] * vector2[0]
        + vector1[1] * vector2[1]
        + vector1[2] * vector2[2];
    result = vector1 * vector2;
    // Assert
    EXPECT_EQ(result, scalar_product);  
}
TEST(TestMathVectorLib, mathvector_add_for_vectors_with_different_dimension_exception) {
    // Arrange & Act
    int data1[3] = { 4, 7 ,28 };
    size_t size1 = 3;

    int data2[5] = { 5, 100, 1, 22, 7 };
    size_t size2 = 5;

    MathVector<int> vector1(data1, size1);
    MathVector<int> vector2(data2, size2);
   
    // Assert
    EXPECT_THROW(vector1 + vector2, std::logic_error);
}
TEST(TestMathVectorLib, mathvector_sub_for_vectors_with_different_dimension_exception) {
    // Arrange & Act
    int data1[3] = { 4, 7 ,28 };
    size_t size1 = 3;

    int data2[5] = { 5, 100, 1, 22, 7 };
    size_t size2 = 5;

    MathVector<int> vector1(data1, size1);
    MathVector<int> vector2(data2, size2);

    // Assert
    EXPECT_THROW(vector1 - vector2, std::logic_error);
}
TEST(TestMathVectorLib, mathvector_scalar_product_for_vectors_with_different_dimension_exception) {
    // Arrange & Act
    int data1[3] = { 4, 7 ,28 };
    size_t size1 = 3;

    int data2[5] = { 5, 100, 1, 22, 7 };
    size_t size2 = 5;

    MathVector<int> vector1(data1, size1);
    MathVector<int> vector2(data2, size2);

    // Assert
    EXPECT_THROW(vector1 * vector2, std::logic_error);
}
TEST(TestMathVectorLib, mathvector_add_assign_vector) {
    // Arrange & Act
    int data1[3] = { 4, 7 ,28 };
    size_t size1 = 3;

    int data2[3] = { 5, 0, 100 };
    size_t size2 = 3;

    MathVector<int> vector1(data1, size1);
    MathVector<int> vector2(data2, size2);
    vector1 += vector2;
    // Assert
    EXPECT_EQ(vector1[0], data1[0] + data2[0]);
    EXPECT_EQ(vector1[1], data1[1] + data2[1]);
    EXPECT_EQ(vector1[2], data1[2] + data2[2]);
}
TEST(TestMathVectorLib, mathvector_sub_assign_vector) {
    // Arrange & Act
    int data1[3] = { 4, 7 ,28 };
    size_t size1 = 3;

    int data2[3] = { 5, 0, 100 };
    size_t size2 = 3;

    MathVector<int> vector1(data1, size1);
    MathVector<int> vector2(data2, size2);
    vector1 -= vector2;
    // Assert
    EXPECT_EQ(vector1[0], data1[0] - data2[0]);
    EXPECT_EQ(vector1[1], data1[1] - data2[1]);
    EXPECT_EQ(vector1[2], data1[2] - data2[2]);
}
TEST(TestMathVectorLib, mathvector_add_assign_for_vectors_with_different_dimension_exception) {
    // Arrange & Act
    int data1[3] = { 4, 7 ,28 };
    size_t size1 = 3;

    int data2[5] = { 5, 100, 1, 22, 7 };
    size_t size2 = 5;

    MathVector<int> vector1(data1, size1);
    MathVector<int> vector2(data2, size2);

    // Assert
    EXPECT_THROW(vector1 += vector2, std::logic_error);
}
TEST(TestMathVectorLib, mathvector_sub_assign_for_vectors_with_different_dimension_exception) {
    // Arrange & Act
    int data1[3] = { 4, 7 ,28 };
    size_t size1 = 3;

    int data2[5] = { 5, 100, 1, 22, 7 };
    size_t size2 = 5;

    MathVector<int> vector1(data1, size1);
    MathVector<int> vector2(data2, size2);

    // Assert
    EXPECT_THROW(vector1 -= vector2, std::logic_error);
}
TEST(TestMathVectorLib, mathvector_simple_assignment) {
    // Arrange
    MathVector<int> vector1(2);
    MathVector<int> vector2(2);
    vector1[0] = 1;
    vector1[1] = 2;
    vector2[0] = 3;
    vector2[1] = 4;
    //Act
    vector1 = vector2;
    // Assert
    EXPECT_EQ(vector1[0], 3);
    EXPECT_EQ(vector1[1], 4);  
}
TEST(TestMathVectorLib, mathvector_operator_square_brackets) {
    // Arrange
    size_t size = 5;
    size_t start_index = 1;
    MathVector<int> vector1(size, start_index);
    vector1[1] = 2;
    vector1[2] = 3;
    vector1[3] = 4;
    vector1[4] = 5;
    vector1[5] = 6;
    //Act & Assert
    EXPECT_EQ(vector1[1], 2);
    EXPECT_EQ(vector1[2], 3);
    EXPECT_EQ(vector1[5], 6);
}
TEST(TestMathVectorLib, mathvector_operator_square_brackets_with_exception) {
    // Arrange
    size_t size = 5;
    size_t start_index = 2;
    MathVector<int> vector1(size, start_index);
    vector1[2] = 3;
    vector1[3] = 4;
    vector1[4] = 5;
    vector1[5] = 6;
    vector1[6] = 7;
    //Act & Assert
    EXPECT_THROW(vector1[0], std::logic_error);
    EXPECT_THROW(vector1[1], std::logic_error);
    EXPECT_THROW(vector1[7], std::logic_error);
}
