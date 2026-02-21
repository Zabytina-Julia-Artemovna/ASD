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
TEST(TestPolynomLib, polynom_assignment_operator) {
    // Arrange
    Monom monom1(10.2, 1, 3, 8);
    Monom monom2(5.5, 2, 1, 0);
    Polynom original(monom1);
    Polynom other(monom2);
    // Act
    other = original;
    // Assert
    EXPECT_EQ(original.size(), other.size());
    std::ostringstream oss_original, oss_other;
    oss_original << original;
    oss_other << other;
    EXPECT_EQ(oss_original.str(), oss_other.str());
}
TEST(TestPolynomLib, polynom_self_assignment) {
    // Arrange
    Monom monom(10.2, 1, 3, 8);
    Polynom polynom(monom);
    std::ostringstream before;
    before << polynom;
    // Act
    polynom = polynom;
    // Assert
    std::ostringstream after;
    after << polynom;
    EXPECT_EQ(before.str(), after.str()); 
}
TEST(TestPolynomLib, polynom_add_polynom) {
    // Arrange
    Monom monom1(1.2, 1, 3, 8);
    Polynom polynom1(monom1);
    Monom monom2(102.12, 1, 4, 2);
    Polynom polynom2(monom2);
    // Act
    Polynom result;
    result = polynom1 + polynom2;
    // Assert
    EXPECT_EQ(result.size(), 2);
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "1.2xy^3z^8 + 102.12xy^4z^2");
}
TEST(TestPolynomLib, polynom_sub_polynom) {
    // Arrange
    Monom monom1(211.2, 1, 3, 8);
    Polynom polynom1(monom1);
    Monom monom2(33.33, 1, 4, 2);
    Polynom polynom2(monom2);
    // Act
    Polynom result;
    result = polynom1 - polynom2;
    // Assert
    EXPECT_EQ(result.size(), 2);
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "211.2xy^3z^8 - 33.33xy^4z^2");
}
TEST(TestPolynomLib, polynom_mult_polynom) {
    // Arrange
    Monom monom1(77.2, 22, 3, 8);
    Polynom polynom1(monom1);
    Monom monom2(10, 1, 49, 2);
    Polynom polynom2(monom2);
    // Act
    Polynom result;
    result = polynom1 * polynom2;
    // Assert
    EXPECT_EQ(result.size(), 1);
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "772x^23y^52z^10");
}
TEST(TestPolynomLib, polynom_add_assign_polynom) {
    // Arrange
    Monom monom1(1.2, 1, 3, 8);
    Polynom polynom1(monom1);
    Monom monom2(102.12, 1, 4, 2);
    Polynom polynom2(monom2);
    // Act
    polynom1 += polynom2;
    // Assert
    EXPECT_EQ(polynom1.size(), 2);
    std::ostringstream oss;
    oss << polynom1;
    EXPECT_EQ(oss.str(), "1.2xy^3z^8 + 102.12xy^4z^2");
}
TEST(TestPolynomLib, polynom_sub_assign_polynom) {
    // Arrange
    Monom monom1(211.2, 1, 3, 8);
    Polynom polynom1(monom1);
    Monom monom2(33.33, 1, 4, 2);
    Polynom polynom2(monom2);
    // Act
    polynom1 -= polynom2;
    // Assert
    EXPECT_EQ(polynom1.size(), 2);
    std::ostringstream oss;
    oss << polynom1;
    EXPECT_EQ(oss.str(), "211.2xy^3z^8 - 33.33xy^4z^2");
}
TEST(TestPolynomLib, polynom_mult_assign_polynom) {
    // Arrange
    Monom monom1(77.2, 22, 3, 8);
    Polynom polynom1(monom1);
    Monom monom2(10, 1, 49, 2);
    Polynom polynom2(monom2);
    // Act
    polynom1 *= polynom2;
    // Assert
    EXPECT_EQ(polynom1.size(), 1);
    std::ostringstream oss;
    oss << polynom1;
    EXPECT_EQ(oss.str(), "772x^23y^52z^10");
}
TEST(TestPolynomLib, polynom_add_monom) {
    // Arrange
    Monom monom1(1.2, 4, 4, 8);
    Polynom polynom(monom1);
    Monom monom2(66.8, 1, 4, 4);
    // Act
    Polynom result;
    result = polynom + monom2;
    // Assert
    EXPECT_EQ(result.size(), 2);
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "1.2x^4y^4z^8 + 66.8xy^4z^4");
}
TEST(TestPolynomLib, polynom_sub_monom) {
    // Arrange
    Monom monom1(2233.4, 1, 2, 8);
    Polynom polynom(monom1);
    Monom monom2(99.9, 2, 2, 2);
    // Act
    Polynom result;
    result = polynom - monom2;
    // Assert
    EXPECT_EQ(result.size(), 2);
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "2233.4xy^2z^8 - 99.9x^2y^2z^2");
}
TEST(TestPolynomLib, polynom_mult_monom) {
    // Arrange
    Polynom polynom("2x^2 + 3y");
    Monom monom(4, 1, 0, 0);
    // Act
    Polynom result = polynom * monom;
    // Assert
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "8x^3 + 12xy");
    EXPECT_EQ(result.size(), 2);
}
TEST(TestPolynomLib, polynom_mult_monom_with_zero_power) {
    // Arrange
    Polynom polynom("5x^2 + 2y^3 + 7");
    Monom monom(3, 0, 0, 0); 
    // Act
    Polynom result = polynom * monom;
    // Assert
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "15x^2 + 6y^3 + 21");
    EXPECT_EQ(result.size(), 3);
}
TEST(TestPolynomLib, polynom_mult_monom_negative_coefficient) {
    // Arrange
    Polynom polynom("4x^2 - 2y");
    Monom monom(-3, 1, 0, 0);
    // Act
    Polynom result = polynom * monom;
    // Assert
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "-12x^3 + 6xy");
    EXPECT_EQ(result.size(), 2);
}
TEST(TestPolynomLib, polynom_add_assign_monom) {
    // Arrange
    Monom monom1(1.2, 4, 4, 8);
    Polynom polynom(monom1);
    Monom monom2(66.8, 1, 4, 4);
    // Act
    polynom += monom2;
    // Assert
    EXPECT_EQ(polynom.size(), 2);
    std::ostringstream oss;
    oss << polynom;
    EXPECT_EQ(oss.str(), "1.2x^4y^4z^8 + 66.8xy^4z^4");
}
TEST(TestPolynomLib, polynom_sub_assign_monom) {
    // Arrange
    Monom monom1(2233.4, 1, 2, 8);
    Polynom polynom(monom1);
    Monom monom2(99.9, 2, 2, 2);
    // Act
    polynom -= monom2;
    // Assert
    EXPECT_EQ(polynom.size(), 2);
    std::ostringstream oss;
    oss << polynom;
    EXPECT_EQ(oss.str(), "2233.4xy^2z^8 - 99.9x^2y^2z^2");
}
TEST(TestPolynomLib, polynom_mult_assign_monom) {
    // Arrange
    Polynom polynom("2x^2 + 3y");
    Monom monom(4, 1, 0, 0);
    // Act
    polynom *= monom;
    // Assert
    std::ostringstream oss;
    oss << polynom;
    EXPECT_EQ(oss.str(), "8x^3 + 12xy");
}
TEST(TestPolynomLib, polynom_unary_minus) {
    // Arrange
    Polynom polynom("22.4xy^2z^8 - 99.9x^2y^2z^2 + 33.7y^3z");
    // Act
    polynom = -polynom;
    // Assert
    EXPECT_EQ(polynom.size(), 3);
    std::ostringstream oss;
    oss << polynom;
    EXPECT_EQ(oss.str(), "-22.4xy^2z^8 + 99.9x^2y^2z^2 - 33.7y^3z");
}
TEST(TestPolynomLib, polynom_calculate) {
    // Arrange
    Polynom polynom("2x + 3y - 4z");
    // Act
    double result = polynom.calculate(5, 7, 2);
    // Assert
    EXPECT_EQ(result, 23);
}
TEST(TestPolynomLib, polynom_calculate_very_large) {
    // Arrange
    Polynom polynom("10x^5y^3 - 7x^2y^4z + 3yz^5");
    // Act
    double result = polynom.calculate(5, 4, 3);
    // Assert
    EXPECT_EQ(result, 1868516);
}
TEST(TestPolynomLib, polynom_is_zero_expect_true) {
    // Arrange
    Polynom polynom;
    // Act & Assert
    EXPECT_TRUE(polynom.is_zero());
}
TEST(TestPolynomLib, polynom_is_zero_expect_false) {
    // Arrange
    Polynom polynom("2x + 32.3y - 4z^5");
    // Act & Assert
    EXPECT_FALSE(polynom.is_zero());
}
