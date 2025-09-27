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
TEST(TestMathVectorLib, mathvector_copy_constructor) {
    // Arrange & Act
    int data[3] = { 1,2,3 };
    size_t size = 3;
    MathVector<int> old_vector(data, size);
    MathVector<int> new_vector(old_vector);
    // Assert
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

