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
    Monom monom1(10.1, 1, 39, 2);
    Monom monom2(34, 2, 3, 4);
    // Assert
    EXPECT_FALSE(monom1 < monom2);
}
TEST(TestMonomLib, add_monoms) {
    // Arrange & Act
    Monom monom1(23, 1, 5, 2);
    Monom monom2(44, 1, 5, 2);
    Monom result = monom1 + monom2;
    // Assert
    EXPECT_EQ(result.get_coefficient(), monom1.get_coefficient() + monom2.get_coefficient());
}
TEST(TestMonomLib, add_monoms_with_exception) {
    // Arrange & Act
    Monom monom1(23, 1, 5, 2);
    Monom monom2(44, 1, 55, 2);
    // Assert
    ASSERT_THROW(monom1 + monom2, std::invalid_argument);
}
TEST(TestMonomLib, sub_monoms) {
    // Arrange & Act
    Monom monom1(33.9, 1, 5, 2);
    Monom monom2(44, 1, 5, 2);
    Monom result = monom1 - monom2;
    // Assert
    EXPECT_EQ(result.get_coefficient(), monom1.get_coefficient() - monom2.get_coefficient());
}
TEST(TestMonomLib, sub_monoms_with_exception) {
    // Arrange & Act
    Monom monom1(23, 1, 5, 2);
    Monom monom2(4.4, 1, 5, 772);
    // Assert
    ASSERT_THROW(monom1 - monom2, std::invalid_argument);
}
TEST(TestMonomLib,mult_monoms) {
    // Arrange & Act
    Monom monom1(23.8, 33, 5, 2);
    Monom monom2(44, 2, 4555, 7);
    Monom result = monom1 * monom2;
    // Assert
    EXPECT_EQ(result.get_coefficient(), monom1.get_coefficient() * monom2.get_coefficient());
    EXPECT_EQ(result.powerX(), monom1.powerX() + monom2.powerX());
    EXPECT_EQ(result.powerY(), monom1.powerY() + monom2.powerY());
    EXPECT_EQ(result.powerZ(), monom1.powerZ() + monom2.powerZ());
}
TEST(TestMonomLib, div_monoms) {
    // Arrange & Act
    Monom monom1(23.9, 33, 4555, 22);
    Monom monom2(33.3, 2, 5, 7);
    Monom result = monom1 / monom2;
    // Assert
    EXPECT_EQ(result.get_coefficient(), monom1.get_coefficient() / monom2.get_coefficient());
    EXPECT_EQ(result.powerX(), monom1.powerX() - monom2.powerX());
    EXPECT_EQ(result.powerY(), monom1.powerY() - monom2.powerY());
    EXPECT_EQ(result.powerZ(), monom1.powerZ() - monom2.powerZ());
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
    double value = 22.5;
    Monom result = monom * value;
    // Assert
    EXPECT_EQ(result.get_coefficient(), monom.get_coefficient() * value);
}
TEST(TestMonomLib, monom_div_value) {
    // Arrange & Act
    Monom monom(223.39, 33, 4555, 22);
    double value = 223.5;
    Monom result = monom / value;
    // Assert
    EXPECT_EQ(result.get_coefficient(), monom.get_coefficient() / value);
}
TEST(TestMonomLib, monom_div_value_with_exception) {
    // Arrange & Act
    Monom monom(223.39, 333, 4, 2);
    double value = 0.0;
    // Assert
    ASSERT_THROW(monom / value, std::invalid_argument);
}
TEST(TestMonomLib, plus_equals_operator) {
    // Arrange & Act
    Monom monom1(23, 1, 5, 2);
    Monom monom2(44, 1, 5, 2);
    monom1 += monom2;
    // Assert
    EXPECT_EQ(monom1.get_coefficient(), 67);
    EXPECT_EQ(monom1.powerX(), 1);
    EXPECT_EQ(monom1.powerY(), 5);
    EXPECT_EQ(monom1.powerZ(), 2);
}
TEST(TestMonomLib, plus_equals_operator_with_exception) {
    // Arrange & Act
    Monom monom1(23, 1, 5, 2);
    Monom monom2(44, 1, 55, 2);
    // Assert
    ASSERT_THROW(monom1 += monom2, std::invalid_argument);
}
TEST(TestMonomLib, minus_equals_operator) {
    // Arrange & Act
    Monom monom1(50, 3, 2, 1);
    Monom monom2(30, 3, 2, 1);
    monom1 -= monom2;
    // Assert
    EXPECT_EQ(monom1.get_coefficient(), 20);
    EXPECT_EQ(monom1.powerX(), 3);
    EXPECT_EQ(monom1.powerY(), 2);
    EXPECT_EQ(monom1.powerZ(), 1);
}
TEST(TestMonomLib, minus_equals_operator_with_exception) {
    // Arrange & Act
    Monom monom1(50, 3, 2, 1);
    Monom monom2(30, 3, 2, 11);
    // Assert
    ASSERT_THROW(monom1 -= monom2, std::invalid_argument);
}
TEST(TestMonomLib, multiply_equals_monom_operator) {
    // Arrange & Act
    Monom monom1(2, 3, 2, 1);
    Monom monom2(3, 1, 2, 3);
    monom1 *= monom2;
    // Assert
    EXPECT_EQ(monom1.get_coefficient(), 6);
    EXPECT_EQ(monom1.powerX(), 4);  
    EXPECT_EQ(monom1.powerY(), 4); 
    EXPECT_EQ(monom1.powerZ(), 4); 
}
TEST(TestMonomLib, multiply_equals_scalar_operator) {
    // Arrange & Act
    Monom monom(5, 2, 3, 1);
    double value = 3.5;
    monom *= value;
    // Assert
    EXPECT_EQ(monom.get_coefficient(), 17.5);
    EXPECT_EQ(monom.powerX(), 2);
    EXPECT_EQ(monom.powerY(), 3);
    EXPECT_EQ(monom.powerZ(), 1);
}
TEST(TestMonomLib, divide_equals_monom_operator) {
    // Arrange & Act
    Monom monom1(12, 4, 3, 2);
    Monom monom2(3, 1, 1, 1);
    monom1 /= monom2;
    // Assert
    EXPECT_EQ(monom1.get_coefficient(), 4);
    EXPECT_EQ(monom1.powerX(), 3);  
    EXPECT_EQ(monom1.powerY(), 2);
    EXPECT_EQ(monom1.powerZ(), 1); 
}
TEST(TestMonomLib, divide_equals_monom_operator_with_exception_division_by_zero) {
    // Arrange & Act
    Monom monom1(12, 4, 3, 2);
    Monom monom2(0, 1, 1, 1);
    // Assert
    ASSERT_THROW(monom1 /= monom2, std::invalid_argument);
}
TEST(TestMonomLib, divide_equals_monom_operator_with_exception_negative_power) {
    // Arrange & Act
    Monom monom1(12, 1, 2, 3);
    Monom monom2(3, 2, 1, 1);
    // Assert
    ASSERT_THROW(monom1 /= monom2, std::invalid_argument);
}
TEST(TestMonomLib, divide_equals_scalar_operator) {
    // Arrange & Act
    Monom monom(15, 2, 3, 1);
    double value = 3.0;
    monom /= value;
    // Assert
    EXPECT_EQ(monom.get_coefficient(), 5);
    EXPECT_EQ(monom.powerX(), 2);
    EXPECT_EQ(monom.powerY(), 3);
    EXPECT_EQ(monom.powerZ(), 1);
}
TEST(TestMonomLib, divide_equals_scalar_operator_with_exception) {
    // Arrange & Act
    Monom monom(15, 2, 3, 1);
    double value = 0.0;
    // Assert
    ASSERT_THROW(monom /= value, std::invalid_argument);
}
TEST(TestMonomLib, calculate_method) {
    // Arrange & Act
    Monom monom(2, 2, 1, 3); 
    double x = 3.0;
    double y = 2.0;
    double z = 1.0;
    double result = monom.calculate(x, y, z);
    // Assert
    EXPECT_EQ(result, 36);
}
TEST(TestMonomLib, calculate_method_with_zero_powers) {
    // Arrange & Act
    Monom monom(5, 0, 0, 0);
    double x = 10.0;
    double y = 20.0;
    double z = 30.0;
    double result = monom.calculate(x, y, z); 
    // Assert
    EXPECT_EQ(result, 5);
}
TEST(TestMonomLib, calculate_method_with_negative_coefficient) {
    // Arrange & Act
    Monom monom(-3, 1, 2, 0);
    double x = 2.0;
    double y = 3.0;
    double z = 1.0;
    double result = monom.calculate(x, y, z); 
    // Assert
    EXPECT_EQ(result, -54);
}
