// Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <gtest/gtest.h>
#include "../lib_calculator_app/expression.h"
TEST(TestCalculatorAppLib, parse_expression_empty) {
    // Arrange & Act
    std::string expression = "";
    // Assert
    ASSERT_THROW(Parser::parse(expression), std::logic_error);
}
TEST(TestCalculatorAppLib, parse_expression_invalid_number_format) {
    // Arrange & Act
    std::string expression = "a+b-2...33";
    // Assert
    ASSERT_THROW(Parser::parse(expression), std::logic_error);
}
TEST(TestCalculatorAppLib, parse_expression_invalid_variable_format) {
    // Arrange & Act
    std::string expression = "(a+b)*9d-10";
    // Assert
    ASSERT_THROW(Parser::parse(expression), std::logic_error);
}
TEST(TestCalculatorAppLib, parse_expression_invalid_funcion_format) {
    // Arrange & Act
    std::string expression = "a+b-cos(";
    // Assert
    ASSERT_THROW(Parser::parse(expression), std::logic_error);
}
TEST(TestCalculatorAppLib, parse_expression_end_with_operator) {
    // Arrange & Act
    std::string expression = "c/d-a*(s-h)+";
    // Assert
    ASSERT_THROW(Parser::parse(expression), std::logic_error);
}
TEST(TestCalculatorAppLib, parse_expression_with_unkown_symbol) {
    // Arrange & Act
    std::string expression = "c/d-a*$";
    // Assert
    ASSERT_THROW(Parser::parse(expression), std::logic_error);
}
TEST(TestCalculatorAppLib, parse_expression_mismatched_brackets) {
    std::string expression = "(a+b";
    ASSERT_THROW(Parser::parse(expression), std::logic_error);
}
TEST(TestCalculatorAppLib, parse_correct_expression1) {
    std::string expression = "a+b*2";
    ASSERT_NO_THROW(Parser::parse(expression));
}
TEST(TestCalculatorAppLib, parse_correct_expression2) {
    std::string expression = "-a+b*2-(c-d)";
    ASSERT_NO_THROW(Parser::parse(expression));
}











//TEST(TestCalculatorAppLib, build_polish_notation) {
//    // Arrange & Act
//
//    // Assert
//}
//TEST(TestCalculatorAppLib, calculate_expression) {
//    // Arrange & Act
//
//    // Assert
//}
