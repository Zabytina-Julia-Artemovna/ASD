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
    ASSERT_THROW(Monom(1.0, -1, 0, 0), std::invalid_argument);
}
TEST(TestMonomLib, constructor_with_arguments_throws_on_negative_power_y) {
    ASSERT_THROW(Monom(1.0, 0, -1, 0), std::invalid_argument);
}
TEST(TestMonomLib, constructor_with_arguments_throws_on_negative_power_z) {
    ASSERT_THROW(Monom(1.0, 0, 0, -1), std::invalid_argument);
}
TEST(TestMonomLib, constructor_with_arguments_throws_on_all_negative_powers) {
    ASSERT_THROW(Monom(1.0, -1, -2, -3), std::invalid_argument);
}
