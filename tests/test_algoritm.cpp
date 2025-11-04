#include "../lib_algoritm/algoritm.h"
#include <stdexcept>
#include <gtest/gtest.h>
TEST(TestAlgoritmLib, test_for_one_local_min) {
    int data[9] = { 1, 20, 30,
                    40, 50, 60 ,
                    70, 80, 90 };
    Matrix<int> matrix(data, 3, 3);
    int result = find_local_minimum(matrix);
    EXPECT_EQ(result, 1);
}
TEST(TestAlgoritmLib, test_for_many_local_min) {
    int data[9] = { 1, 4, 3,
                    8, 10, 6 ,
                    7, 9, 2 };
    Matrix<int> matrix(data, 3, 3);
    int result = find_local_minimum(matrix);
    EXPECT_TRUE(result == 1 || result == 3 || result == 7 || result == 2);
}
TEST(TestAlgoritmLib, test_top_left_corner_minimum) {
    int data[9] = { 1, 3, 4,
                    2, 5, 6,
                    7, 8, 9 };
    Matrix<int> matrix(data, 3, 3);
    int result = find_local_minimum(matrix);

    EXPECT_TRUE(result == 1); 
}
TEST(TestAlgoritmLib, test_bottom_right_corner_minimum) {
    int data[9] = { 9, 8, 7,
                    6, 5, 4,
                    3, 2, 1 }; 
    Matrix<int> matrix(data, 3, 3);
    int result = find_local_minimum(matrix);
    EXPECT_EQ(result, 1);
}
TEST(TestAlgoritmLib, test_center_minimum) {
    int data[9] = { 9, 8, 7,
                    6, 1, 5,
                    4, 2, 3 };
    Matrix<int> matrix(data, 3, 3);
    int result = find_local_minimum(matrix);
    EXPECT_EQ(result, 1);
}
TEST(TestAlgoritmLib, test_single_element) {
    int data[1] = { 5 };
    Matrix<int> matrix(data, 1, 1);
    int result = find_local_minimum(matrix);
    EXPECT_EQ(result, 5);
}
TEST(TestAlgoritmLib, test_2x2_matrix) {
    int data[4] = { 4, 3,
                    1, 2 };
    Matrix<int> matrix(data, 2, 2);
    int result = find_local_minimum(matrix);
    EXPECT_TRUE(result == 3 || result == 1);
}
TEST(TestAlgoritmLib, test_5x5_matrix) {
    int data[25] = { 10, 11, 12, 13, 14,
                     15, 16,  1, 17, 18,
                     19, 20, 21, 22, 23,
                     24, 25, 26, 27, 28,
                     29, 30, 31, 32, 33 };
    Matrix<int> matrix(data, 5, 5);
    int result = find_local_minimum(matrix);
    EXPECT_TRUE(result == 1 || result == 10 || result == 14 || result == 19 
               || result == 23 || result == 29 || result == 33);
}
TEST(TestAlgorithmLib, test_check_brackets_false1) {
    std::string string = ")";
    EXPECT_EQ(check_brackets(string), false);

}
TEST(TestAlgorithmLib, test_check_brackets_false2) {
    std::string string = "[";
    EXPECT_EQ(check_brackets(string), false);
}
TEST(TestAlgorithmLib, test_check_brackets_false3) {
    std::string string = "())";
    EXPECT_EQ(check_brackets(string), false);
}
TEST(TestAlgorithmLib, test_check_brackets_false4) {
    std::string string = "({)";
    EXPECT_EQ(check_brackets(string), false);
}
TEST(TestAlgorithmLib, test_check_brackets_false5) {
    std::string string = "({})]";
    EXPECT_EQ(check_brackets(string), false);
}
TEST(TestAlgorithmLib, test_check_brackets_true1) {
    std::string string = "()";
    EXPECT_EQ(check_brackets(string), true);
}
TEST(TestAlgorithmLib, test_check_brackets_true2) {
    std::string string = "{}";
    EXPECT_EQ(check_brackets(string), true);
}
TEST(TestAlgorithmLib, test_check_brackets_true3) {
    std::string string = "[()]";
    EXPECT_EQ(check_brackets(string), true);
}
TEST(TestAlgorithmLib, test_check_brackets_true4) {
    std::string string = "{[()]}";
    EXPECT_EQ(check_brackets(string), true);
}
TEST(TestAlgorithmLib, test_check_brackets_true5) {
    std::string string = "()[]{}";
    EXPECT_EQ(check_brackets(string), true);
}
TEST(TestAlgorithmLib, test_check_brackets_true6) {
    std::string string = "";
    EXPECT_EQ(check_brackets(string), true);
}

TEST(TestAlgorithmLib, test_read_expression_empty_brackets) {
    std::string expression = "a + b - ()";
    EXPECT_THROW(read_expression(expression), std::invalid_argument);
}
TEST(TestAlgorithmLib, test_read_expression_operator_in_wrong_position1) {
    std::string expression = "a + * b";
    EXPECT_THROW(read_expression(expression), std::invalid_argument);
}
TEST(TestAlgorithmLib, test_read_expression_operator_in_wrong_position2) {
    std::string expression = "(* a)";
    EXPECT_THROW(read_expression(expression), std::invalid_argument);
}
TEST(TestAlgorithmLib, test_read_expression_operands_without_operator1) {
    std::string expression = "(a b)";
    EXPECT_THROW(read_expression(expression), std::invalid_argument);
}
TEST(TestAlgorithmLib, test_read_expression_operands_without_operator2) {
    std::string expression = "a  b";
    EXPECT_THROW(read_expression(expression), std::invalid_argument);
}
TEST(TestAlgorithmLib, test_read_expression_operands_without_operator3) {
    std::string expression = "a + b c";
    EXPECT_THROW(read_expression(expression), std::invalid_argument);
}
TEST(TestAlgorithmLib, test_read_expression_invalid_character) {
    std::string expression = "(a@b)";
    EXPECT_THROW(read_expression(expression), std::invalid_argument);
}


TEST(TestAlgorithmLib, test_read_expression_unbalanced_brackets) {
    std::string expression = "(a-b)*c + (d + f)))";
    EXPECT_THROW(read_expression(expression), std::invalid_argument);
}
TEST(TestAlgorithmLib, test_read_expression_missing_operand_at_the_end) {
    std::string expression = "a + b - ";
    EXPECT_THROW(read_expression(expression), std::invalid_argument);
}
TEST(TestAlgorithmLib, test_read_expression_no_operands_in_expression) {
    std::string expression = "+ -";
    EXPECT_THROW(read_expression(expression), std::invalid_argument);
}
TEST(TestAlgorithmLib, test_read_expression_no_operand_before_opening_bracket) {
    std::string expression = "a ( a + b)";
    EXPECT_THROW(read_expression(expression), std::invalid_argument);
}

