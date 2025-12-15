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
TEST(TestCalculatorAppLib, parse_correct_expression3_with_functions) {
    std::string expression = "sin(x)+cos(y)";
    ASSERT_NO_THROW(Parser::parse(expression));
}
TEST(TestCalculatorAppLib, parse_correct_expression4_with_abs) {
    std::string expression = "|a-b|+c";
    ASSERT_NO_THROW(Parser::parse(expression));
}
TEST(TestCalculatorAppLib, parse_correct_expression5_complex) {
    std::string expression = "a+b*(c-d)/e^2";
    ASSERT_NO_THROW(Parser::parse(expression));
}
TEST(TestCalculatorAppLib, calculate_simple_expression) {
    // Arrange
    std::string expr_str = "2+3";
    Expression expr(1, expr_str);

    // Act & Assert
    ASSERT_NO_THROW(expr.calculate());
    ASSERT_DOUBLE_EQ(expr.calculate(), 5.0);
}
TEST(TestCalculatorAppLib, calculate_with_variables) {
    // Arrange
    std::string expr_str = "a+b";
    Expression expr(1, expr_str);
    expr.set_variable("a", 2.5);
    expr.set_variable("b", 3.5);

    // Act & Assert
    ASSERT_NO_THROW(expr.calculate());
    ASSERT_DOUBLE_EQ(expr.calculate(), 6.0);
}
TEST(TestCalculatorAppLib, calculate_with_operations) {
    // Arrange
    std::string expr_str = "2+3*4";
    Expression expr(1, expr_str);

    // Act & Assert
    ASSERT_NO_THROW(expr.calculate());
    ASSERT_DOUBLE_EQ(expr.calculate(), 14.0); 
}
TEST(TestCalculatorAppLib, calculate_with_brackets) {
    // Arrange
    std::string expr_str = "(2+3)*4";
    Expression expr(1, expr_str);

    // Act & Assert
    ASSERT_NO_THROW(expr.calculate());
    ASSERT_DOUBLE_EQ(expr.calculate(), 20.0); 
}
TEST(TestCalculatorAppLib, calculate_with_division) {
    // Arrange
    std::string expr_str = "10/2";
    Expression expr(1, expr_str);

    // Act & Assert
    ASSERT_NO_THROW(expr.calculate());
    ASSERT_DOUBLE_EQ(expr.calculate(), 5.0);
}
TEST(TestCalculatorAppLib, calculate_with_power) {
    // Arrange
    std::string expr_str = "2^3";
    Expression expr(1, expr_str);

    // Act & Assert
    ASSERT_NO_THROW(expr.calculate());
    ASSERT_DOUBLE_EQ(expr.calculate(), 8.0); 
}
TEST(TestCalculatorAppLib, calculate_with_function) {
    // Arrange
    std::string expr_str = "sin(0)";
    Expression expr(1, expr_str);

    // Act & Assert
    ASSERT_NO_THROW(expr.calculate());
    ASSERT_DOUBLE_EQ(expr.calculate(), 0.0);
}
TEST(TestCalculatorAppLib, calculate_with_abs) {
    // Arrange
    std::string expr_str = "|-5|";
    Expression expr(1, expr_str);

    // Act & Assert
    ASSERT_NO_THROW(expr.calculate());
    ASSERT_DOUBLE_EQ(expr.calculate(), 5.0);
}
TEST(TestCalculatorAppLib, calculate_complex_expression) {
    // Arrange
    std::string expr_str = "2+3*sin(0)-|-5|/5";
    Expression expr(1, expr_str);

    // Act & Assert
    ASSERT_NO_THROW(expr.calculate());
    // 2 + 3*0 - 5/5 = 2 - 1 = 1
    ASSERT_DOUBLE_EQ(expr.calculate(), 1.0);
}
TEST(TestCalculatorAppLib, calculate_division_by_zero) {
    // Arrange
    std::string expr_str = "1/0";
    Expression expr(1, expr_str);

    // Act & Assert
    ASSERT_THROW(expr.calculate(), std::logic_error);
}
TEST(TestCalculatorAppLib, calculate_missing_variable) {
    // Arrange
    std::string expr_str = "a+5";
    Expression expr(1, expr_str);

    // Act & Assert
    ASSERT_THROW(expr.calculate(), std::logic_error);
}
TEST(TestCalculatorAppLib, calculate_with_unary_minus1) {
    // Arrange
    std::string expr_str = "3+(-5)";
    Expression expr(1, expr_str);

    // Act & Assert
    ASSERT_NO_THROW(expr.calculate());
    ASSERT_DOUBLE_EQ(expr.calculate(), -2.0); 
}
TEST(TestCalculatorAppLib, calculate_with_unary_minus2) {
    // Arrange
    std::string expr_str = "-5+3";
    Expression expr(1, expr_str);

    // Act & Assert
    ASSERT_NO_THROW(expr.calculate());
    ASSERT_DOUBLE_EQ(expr.calculate(), -2.0);
}
TEST(TestCalculatorAppLib, calculate_with_nested_functions) {
    // Arrange
    std::string expr_str = "sin(cos(0))";
    Expression expr(1, expr_str);

    // Act & Assert
    ASSERT_NO_THROW(expr.calculate());
    ASSERT_NEAR(expr.calculate(), 0.8414709848, 1e-9);
}
TEST(TestCalculatorAppLib, expression_getters) {
    // Arrange
    std::string expr_str = "a+b";
    Expression expr(42, expr_str);
    expr.set_variable("a", 2.0);
    expr.set_variable("b", 3.0);

    // Act & Assert
    ASSERT_EQ(expr.get_id(), 42);
    ASSERT_EQ(expr.get_expression(), "a+b");
    ASSERT_DOUBLE_EQ(expr.calculate(), 5.0);
}
TEST(TestCalculatorAppLib, expression_variables_map) {
    // Arrange
    std::string expr_str = "x+y";
    Expression expr(1, expr_str);
    expr.set_variable("x", 10.0);
    expr.set_variable("y", 20.0);
    // Act
    auto vars = expr.variables_map();
    // Assert
    ASSERT_EQ(vars.size(), 2);
    ASSERT_DOUBLE_EQ(vars["x"], 10.0);
    ASSERT_DOUBLE_EQ(vars["y"], 20.0);
}
TEST(TestCalculatorAppLib, expression_build_polish_notation_simple_addition) {
    // Arrange
    std::string expr_str = "a+b";
    Expression expr(1, expr_str); 
    // Act & Assert 
    ASSERT_NO_THROW(Expression expr(1, expr_str));
}
TEST(TestCalculatorAppLib, expression_build_polish_notation_operator_priority) {
    // Arrange & Act
    Expression expr(1, "a+b*c"); 
    // Assert
    expr.set_variable("a", 1.0);
    expr.set_variable("b", 2.0);
    expr.set_variable("c", 3.0);
    ASSERT_NO_THROW(expr.calculate());
    ASSERT_DOUBLE_EQ(expr.calculate(), 7.0); 
}
TEST(TestCalculatorAppLib, expression_build_polish_notation_with_parentheses) {
    // Arrange & Act
    Expression expr(1, "(a+b)*c"); 
    // Assert
    expr.set_variable("a", 1.0);
    expr.set_variable("b", 2.0);
    expr.set_variable("c", 3.0);
    ASSERT_DOUBLE_EQ(expr.calculate(), 9.0); 
}
TEST(TestCalculatorAppLib, expression_build_polish_notation_complex) {
    // Arrange & Act
    Expression expr(1, "a+b*(c-d)/e"); 
    // Assert
    expr.set_variable("a", 1.0);
    expr.set_variable("b", 2.0);
    expr.set_variable("c", 5.0);
    expr.set_variable("d", 3.0);
    expr.set_variable("e", 4.0);
    ASSERT_DOUBLE_EQ(expr.calculate(), 2.0);
}
TEST(TestCalculatorAppLib, expression_build_polish_notation_power_operator) {
    // Arrange & Act
    Expression expr(1, "a^b*c"); 
    // Assert
    expr.set_variable("a", 2.0);
    expr.set_variable("b", 3.0);
    expr.set_variable("c", 4.0);
    ASSERT_DOUBLE_EQ(expr.calculate(), 32.0);
}
TEST(TestCalculatorAppLib, expression_build_polish_notation_with_functions) {
    // Arrange & Act
    Expression expr(1, "sin(a)+cos(b)"); 
    // Assert
    expr.set_variable("a", 0.0);  
    expr.set_variable("b", 0.0);
    ASSERT_DOUBLE_EQ(expr.calculate(), 1.0);
}
TEST(TestCalculatorAppLib, expression_build_polish_notation_nested_functions) {
    // Arrange & Act
    Expression expr(1, "sin(cos(a))");
    // Assert
    expr.set_variable("a", 0.0); 
    ASSERT_NEAR(expr.calculate(), 0.8414709848, 1e-9);
}
TEST(TestCalculatorAppLib, expression_build_polish_notation_with_abs_bars) {
    // Arrange & Act
    Expression expr(1, "|a-b|+c"); 
    // Assert
    expr.set_variable("a", 5.0);
    expr.set_variable("b", 8.0);
    expr.set_variable("c", 2.0);
    // |5-8| + 2 = 3 + 2 = 5
    ASSERT_DOUBLE_EQ(expr.calculate(), 5.0);
}
TEST(TestCalculatorAppLib, expression_build_polish_notation_unary_minus) {
    // Arrange & Act
    Expression expr(1, "-a+b"); 
    // Assert
    expr.set_variable("a", 5.0);
    expr.set_variable("b", 3.0);
    ASSERT_DOUBLE_EQ(expr.calculate(), -2.0);
}
