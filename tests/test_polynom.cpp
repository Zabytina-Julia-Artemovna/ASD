// Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <gtest/gtest.h>
#include "../lib_polynom/polynom.h"
const double TEST_EPSILON = 1e-10;
TEST(TestPolynomLib, polynom_default_constructor) {
    // Arrange & Act
    Polynom polynom;
    // Assert
    EXPECT_EQ(polynom.size(), 0);
    EXPECT_TRUE(polynom.is_zero());
}
TEST(TestPolynomLib, polynom_constructor_from_monom) {
    // Arrange
    Monom monom(22.3);

    // Act
    Polynom polynom(monom);

    // Assert
    EXPECT_EQ(polynom.size(), 1);
    std::ostringstream oss;
    oss << polynom;
    EXPECT_EQ(oss.str(), "22.3");
}

TEST(TestPolynomLib, polynom_constructor_from_monom_with_powers) {
    // Arrange
    Monom monom(2.5, 2, 1, 0); 

    // Act
    Polynom polynom(monom);

    // Assert
    EXPECT_EQ(polynom.size(), 1);
    std::ostringstream oss;
    oss << polynom;
    EXPECT_EQ(oss.str(), "2.5x^2y");
}
TEST(TestPolynomLib, polynom_copy_constructor) {
    // Arrange
    Monom monom(3.14, 1, 1, 0);
    Polynom original(monom);

    // Act
    Polynom copy(original);

    // Assert
    EXPECT_EQ(original.size(), copy.size());
    std::ostringstream oss_original, oss_copy;
    oss_original << original;
    oss_copy << copy;
    EXPECT_EQ(oss_original.str(), oss_copy.str());
}





