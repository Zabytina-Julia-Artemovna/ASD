// Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <gtest/gtest.h>
#include "../lib_monom/monom.h"
const double TEST_EPSILON = 1e-10;
TEST(TestMonomLib, monom_default_constructor) {
    // Arrange & Act
    Monom monom;
    // Assert
    EXPECT_TRUE(std::abs(monom.get_coefficient()) < TEST_EPSILON);
    EXPECT_EQ(monom.powerX(), 0);
    EXPECT_EQ(monom.powerY(), 0);
    EXPECT_EQ(monom.powerZ(), 0);
}
TEST(TestMonomLib, monom_constructor_with_arguments) {
    // Arrange & Act
    double coefficient = 1.5;
    int power_x = 2;
    int power_y = 3;
    int power_z = 5;
    Monom monom(coefficient, power_x, power_y, power_z);
    // Assert
    EXPECT_EQ(monom.get_coefficient(), coefficient);
    EXPECT_EQ(monom.powerX(), power_x);
    EXPECT_EQ(monom.powerY(), power_y);
    EXPECT_EQ(monom.powerZ(), power_z);
}
TEST(TestMonomLib, constructor_with_arguments_throws_on_negative_power_x) {
    ASSERT_THROW(Monom(1.0, -99, 1, 0), std::invalid_argument);
}
TEST(TestMonomLib, constructor_with_arguments_throws_on_negative_power_y) {
    ASSERT_THROW(Monom(10.0, 22, -301, 50), std::invalid_argument);
}
TEST(TestMonomLib, constructor_with_arguments_throws_on_negative_power_z) {
    ASSERT_THROW(Monom(100.5, 33, 67, -100), std::invalid_argument);
}
TEST(TestMonomLib, constructor_with_arguments_throws_on_all_negative_powers) {
    ASSERT_THROW(Monom(39.78, -12, -20, -33), std::invalid_argument);
}
TEST(TestMonomLib, is_monoms_similar_true) {
    // Arrange & Act
    Monom monom1(10, 2, 3, 4);
    Monom monom2(34, 2, 3, 4);
    // Assert
    EXPECT_TRUE(monom1 == monom2);
}
TEST(TestMonomLib, is_monoms_not_similar_true) {
    // Arrange & Act
    Monom monom1(10, 2, 29, 4);
    Monom monom2(34, 2, 3, 4);
    // Assert
    EXPECT_TRUE(monom1 != monom2);
}
TEST(TestMonomLib, is_monoms_similar_false) {
    // Arrange & Act
    Monom monom1(10, 2, 3, 77);
    Monom monom2(34, 2, 25, 4);
    // Assert
    EXPECT_FALSE(monom1 == monom2);
}
TEST(TestMonomLib, is_monoms_not_similar_false) {
    // Arrange & Act
    Monom monom1(10, 2, 3, 4);
    Monom monom2(34, 2, 3, 4);
    // Assert
    EXPECT_FALSE(monom1 != monom2);
}
TEST(TestMonomLib, monom1_greater_monom2_true) {
    // Arrange & Act
    Monom monom1(130, 10, 3, 4);
    Monom monom2(35, 2, 3, 4);
    // Assert
    EXPECT_TRUE(monom1 > monom2);
}
TEST(TestMonomLib, monom1_less_monom2_true) {
    // Arrange & Act
    Monom monom1(10, 1, 1, 2);
    Monom monom2(34, 2, 3, 4);
    // Assert
    EXPECT_TRUE(monom1 < monom2);
}
TEST(TestMonomLib, monom1_greater_monom2_false) {
    // Arrange & Act
    Monom monom1(130, 10, 3, 4);
    Monom monom2(35, 2, 3, 389);
    // Assert
    EXPECT_FALSE(monom1 > monom2);
}
TEST(TestMonomLib, monom1_less_monom2_false) {
    // Arrange & Act
    Monom monom1(10, 1, 39, 2);
    Monom monom2(34, 2, 3, 4);
    // Assert
    EXPECT_FALSE(monom1 < monom2);
}
