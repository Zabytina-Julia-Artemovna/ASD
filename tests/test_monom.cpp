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
    Monom monom(1.5, 2, 3, 5);
    // Assert
    EXPECT_EQ(monom.get_coefficient(), 1.5);
    EXPECT_EQ(monom.powerX(), 2);
    EXPECT_EQ(monom.powerY(), 3);
    EXPECT_EQ(monom.powerZ(), 5);
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
    Monom monom1(10.0, 2, 3, 4);
    Monom monom2(34.0, 2, 3, 4);
    // Assert
    EXPECT_TRUE(monom1 == monom2);
}

TEST(TestMonomLib, is_monoms_not_similar_true) {
    // Arrange & Act
    Monom monom1(10.0, 2, 29, 4);
    Monom monom2(34.0, 2, 3, 4);
    // Assert
    EXPECT_TRUE(monom1 != monom2);
}

TEST(TestMonomLib, is_monoms_similar_false) {
    // Arrange & Act
    Monom monom1(10.0, 2, 3, 77);
    Monom monom2(34.0, 2, 25, 4);
    // Assert
    EXPECT_FALSE(monom1 == monom2);
}

TEST(TestMonomLib, is_monoms_not_similar_false) {
    // Arrange & Act
    Monom monom1(10.0, 2, 3, 4);
    Monom monom2(34.0, 2, 3, 4);
    // Assert
    EXPECT_FALSE(monom1 != monom2);
}

TEST(TestMonomLib, monom1_greater_monom2_true) {
    // Arrange & Act
    Monom monom1(130.0, 10, 3, 4);
    Monom monom2(35.0, 2, 3, 4);
    // Assert
    EXPECT_TRUE(monom1 > monom2);
}

TEST(TestMonomLib, monom1_less_monom2_true) {
    // Arrange & Act
    Monom monom1(10.0, 1, 1, 2);
    Monom monom2(34.0, 2, 3, 4);
    // Assert
    EXPECT_TRUE(monom1 < monom2);
}

TEST(TestMonomLib, monom1_greater_monom2_false) {
    // Arrange & Act
    Monom monom1(130.0, 10, 3, 4);
    Monom monom2(35.0, 2, 3, 389);
    // Assert
    EXPECT_FALSE(monom1 > monom2);
}

TEST(TestMonomLib, monom1_less_monom2_false) {
    // Arrange & Act
    Monom monom1(10.1, 1, 39, 2);
    Monom monom2(34.0, 2, 3, 4);
    // Assert
    EXPECT_FALSE(monom1 < monom2);
}

TEST(TestMonomLib, add_monoms) {
    // Arrange & Act
    Monom monom1(23.0, 1, 5, 2);
    Monom monom2(44.0, 1, 5, 2);
    Monom result = monom1 + monom2;
    // Assert
    EXPECT_EQ(result.get_coefficient(), 67.0);
    EXPECT_EQ(result.powerX(), 1);
    EXPECT_EQ(result.powerY(), 5);
    EXPECT_EQ(result.powerZ(), 2);
}

TEST(TestMonomLib, add_monoms_with_exception) {
    // Arrange & Act
    Monom monom1(23.0, 1, 5, 2);
    Monom monom2(44.0, 1, 55, 2);
    // Assert
    ASSERT_THROW(monom1 + monom2, std::invalid_argument);
}

TEST(TestMonomLib, sub_monoms) {
    // Arrange & Act
    Monom monom1(33.9, 1, 5, 2);
    Monom monom2(44.0, 1, 5, 2);
    Monom result = monom1 - monom2;
    // Assert
    EXPECT_NEAR(result.get_coefficient(), -10.1, TEST_EPSILON);
    EXPECT_EQ(result.powerX(), 1);
    EXPECT_EQ(result.powerY(), 5);
    EXPECT_EQ(result.powerZ(), 2);
}

TEST(TestMonomLib, sub_monoms_with_exception) {
    // Arrange & Act
    Monom monom1(23.0, 1, 5, 2);
    Monom monom2(4.4, 1, 5, 772);
    // Assert
    ASSERT_THROW(monom1 - monom2, std::invalid_argument);
}

TEST(TestMonomLib, mult_monoms) {
    // Arrange & Act
    Monom monom1(23.8, 33, 5, 2);
    Monom monom2(44.0, 2, 4555, 7);
    Monom result = monom1 * monom2;
    // Assert
    EXPECT_NEAR(result.get_coefficient(), 1047.2, TEST_EPSILON);
    EXPECT_EQ(result.powerX(), 35);
    EXPECT_EQ(result.powerY(), 4560);
    EXPECT_EQ(result.powerZ(), 9);
}

TEST(TestMonomLib, div_monoms) {
    // Arrange & Act
    Monom monom1(23.9, 33, 4555, 22);
    Monom monom2(33.3, 2, 5, 7);
    Monom result = monom1 / monom2;
    // Assert
    EXPECT_NEAR(result.get_coefficient(), 23.9 / 33.3, TEST_EPSILON);
    EXPECT_EQ(result.powerX(), 31);
    EXPECT_EQ(result.powerY(), 4550);
    EXPECT_EQ(result.powerZ(), 15);
}

TEST(TestMonomLib, div_monoms_with_exception) {
    // Arrange & Act
    Monom monom1(25.9, 2, 3, 1);
    Monom monom2(3.3, 3, 2, 1);
    // Assert
    ASSERT_THROW(monom1 / monom2, std::invalid_argument);
}

TEST(TestMonomLib, monom_mult_value) {
    // Arrange & Act
    Monom monom(223.39, 33, 4555, 22);
    Monom result = monom * 22.5;
    // Assert
    EXPECT_NEAR(result.get_coefficient(), 223.39 * 22.5, TEST_EPSILON);
    EXPECT_EQ(result.powerX(), 33);
    EXPECT_EQ(result.powerY(), 4555);
    EXPECT_EQ(result.powerZ(), 22);
}

TEST(TestMonomLib, monom_div_value) {
    // Arrange & Act
    Monom monom(223.39, 33, 4555, 22);
    Monom result = monom / 223.5;
    // Assert
    EXPECT_NEAR(result.get_coefficient(), 223.39 / 223.5, TEST_EPSILON);
    EXPECT_EQ(result.powerX(), 33);
    EXPECT_EQ(result.powerY(), 4555);
    EXPECT_EQ(result.powerZ(), 22);
}

TEST(TestMonomLib, monom_div_value_with_exception) {
    // Arrange & Act
    Monom monom(223.39, 333, 4, 2);
    // Assert
    ASSERT_THROW(monom / 0.0, std::invalid_argument);
}

TEST(TestMonomLib, plus_equals_operator) {
    // Arrange & Act
    Monom monom1(23.0, 1, 5, 2);
    Monom monom2(44.0, 1, 5, 2);
    monom1 += monom2;
    // Assert
    EXPECT_EQ(monom1.get_coefficient(), 67.0);
    EXPECT_EQ(monom1.powerX(), 1);
    EXPECT_EQ(monom1.powerY(), 5);
    EXPECT_EQ(monom1.powerZ(), 2);
}

TEST(TestMonomLib, plus_equals_operator_with_exception) {
    // Arrange & Act
    Monom monom1(23.0, 1, 5, 2);
    Monom monom2(44.0, 1, 55, 2);
    // Assert
    ASSERT_THROW(monom1 += monom2, std::invalid_argument);
}

TEST(TestMonomLib, minus_equals_operator) {
    // Arrange & Act
    Monom monom1(50.0, 3, 2, 1);
    Monom monom2(30.0, 3, 2, 1);
    monom1 -= monom2;
    // Assert
    EXPECT_EQ(monom1.get_coefficient(), 20.0);
    EXPECT_EQ(monom1.powerX(), 3);
    EXPECT_EQ(monom1.powerY(), 2);
    EXPECT_EQ(monom1.powerZ(), 1);
}

TEST(TestMonomLib, minus_equals_operator_with_exception) {
    // Arrange & Act
    Monom monom1(50.0, 3, 2, 1);
    Monom monom2(30.0, 3, 2, 11);
    // Assert
    ASSERT_THROW(monom1 -= monom2, std::invalid_argument);
}

TEST(TestMonomLib, multiply_equals_monom_operator) {
    // Arrange & Act
    Monom monom1(2.0, 3, 2, 1);
    Monom monom2(3.0, 1, 2, 3);
    monom1 *= monom2;
    // Assert
    EXPECT_EQ(monom1.get_coefficient(), 6.0);
    EXPECT_EQ(monom1.powerX(), 4);
    EXPECT_EQ(monom1.powerY(), 4);
    EXPECT_EQ(monom1.powerZ(), 4);
}

TEST(TestMonomLib, multiply_equals_scalar_operator) {
    // Arrange & Act
    Monom monom(5.0, 2, 3, 1);
    monom *= 3.5;
    // Assert
    EXPECT_EQ(monom.get_coefficient(), 17.5);
    EXPECT_EQ(monom.powerX(), 2);
    EXPECT_EQ(monom.powerY(), 3);
    EXPECT_EQ(monom.powerZ(), 1);
}

TEST(TestMonomLib, divide_equals_monom_operator) {
    // Arrange & Act
    Monom monom1(12.0, 4, 3, 2);
    Monom monom2(3.0, 1, 1, 1);
    monom1 /= monom2;
    // Assert
    EXPECT_EQ(monom1.get_coefficient(), 4.0);
    EXPECT_EQ(monom1.powerX(), 3);
    EXPECT_EQ(monom1.powerY(), 2);
    EXPECT_EQ(monom1.powerZ(), 1);
}

TEST(TestMonomLib, divide_equals_monom_operator_with_exception_division_by_zero) {
    // Arrange & Act
    Monom monom1(12.0, 4, 3, 2);
    Monom monom2(0.0, 1, 1, 1);
    // Assert
    ASSERT_THROW(monom1 /= monom2, std::invalid_argument);
}

TEST(TestMonomLib, divide_equals_monom_operator_with_exception_negative_power) {
    // Arrange & Act
    Monom monom1(12.0, 1, 2, 3);
    Monom monom2(3.0, 2, 1, 1);
    // Assert
    ASSERT_THROW(monom1 /= monom2, std::invalid_argument);
}

TEST(TestMonomLib, divide_equals_scalar_operator) {
    // Arrange & Act
    Monom monom(15.0, 2, 3, 1);
    monom /= 3.0;
    // Assert
    EXPECT_EQ(monom.get_coefficient(), 5.0);
    EXPECT_EQ(monom.powerX(), 2);
    EXPECT_EQ(monom.powerY(), 3);
    EXPECT_EQ(monom.powerZ(), 1);
}

TEST(TestMonomLib, divide_equals_scalar_operator_with_exception) {
    // Arrange & Act
    Monom monom(15.0, 2, 3, 1);
    // Assert
    ASSERT_THROW(monom /= 0.0, std::invalid_argument);
}

TEST(TestMonomLib, calculate_method) {
    // Arrange & Act
    Monom monom(2.0, 2, 1, 3);
    double result = monom.calculate(3.0, 2.0, 1.0);
    // Assert
    EXPECT_EQ(result, 36.0);
}

TEST(TestMonomLib, calculate_method_with_zero_powers) {
    // Arrange & Act
    Monom monom(5.0, 0, 0, 0);
    double result = monom.calculate(10.0, 20.0, 30.0);
    // Assert
    EXPECT_EQ(result, 5.0);
}

TEST(TestMonomLib, calculate_method_with_negative_coefficient) {
    // Arrange & Act
    Monom monom(-3.0, 1, 2, 0);
    double result = monom.calculate(2.0, 3.0, 1.0);
    // Assert
    EXPECT_EQ(result, -54.0);
}