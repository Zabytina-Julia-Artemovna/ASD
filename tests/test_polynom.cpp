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
//TEST(TestPolynomLib, polynom_assignment_operator) {
//    // Arrange
//    Monom monom1(10.2, 1, 3, 8);
//    Monom monom2(5.5, 2, 1, 0);
//    Polynom original(monom1);
//    Polynom other(monom2);
//    // Act
//    other = original;  // Присваивание существующему объекту
//    // Assert
//    EXPECT_EQ(original.size(), other.size());
//    std::ostringstream oss_original, oss_other;
//    oss_original << original;
//    oss_other << other;
//    EXPECT_EQ(oss_original.str(), oss_other.str());
//}
//TEST(TestPolynomLib, polynom_assignment_to_self) {
//    // Arrange
//    Monom monom(10.2, 1, 3, 8);
//    Polynom polynom(monom);
//    std::ostringstream before;
//    before << polynom;
//    // Act
//    polynom = polynom;  // Присваивание самому себе
//    // Assert
//    std::ostringstream after;
//    after << polynom;
//    EXPECT_EQ(before.str(), after.str());  // Должен остаться неизменным
//}
//TEST(TestPolynomLib, polynom_assignment_deep_copy) {
//    // Arrange
//    Polynom p1("2*x*y + 3*z");
//    Polynom p2("5*x");
//    // Act
//    p2 = p1;
//    // Изменяем оригинал
//    p1 = Polynom("100*x");  // Создаем новый полином
//    // Assert
//    std::ostringstream oss_p2;
//    oss_p2 << p2;
//    // p2 должен остаться старым значением ("2*x*y + 3*z")
//    EXPECT_EQ(oss_p2.str(), "2*x*y + 3*z");
//}
