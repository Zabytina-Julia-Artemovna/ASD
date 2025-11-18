// Copyright 2025 Julia Zabytina
#include <gtest/gtest.h>
#include "../lib_stack_on_list/stack_on_list.h"

TEST(TestStackOnListLib, stack_constructor_with_size_default) {
    // Arrange & Act
    StackOnList<int> stack;
    // Assert
    EXPECT_EQ(stack.size(), 0);
    EXPECT_FALSE(stack.has_max_size());
    EXPECT_TRUE(stack.is_empty());
}
TEST(TestStackOnListLib, stack_constructor_with_size) {
    // Arrange & Act
    size_t max_size = 10;
    StackOnList<int> stack(max_size);
    // Assert
    EXPECT_EQ(stack.max_size(), max_size);
    EXPECT_EQ(stack.size(), 0);
    EXPECT_TRUE(stack.is_empty());
}
TEST(TestStackOnListLib, stack_copy_constructor) {
    // Arrange
    size_t max_size = 5;
    StackOnList<int> stack1(max_size);
    stack1.push(5);
    stack1.push(6);
    stack1.push(7);
    // Act
    StackOnList<int> stack2(stack1);
    // Assert
    EXPECT_EQ(stack1.max_size(), stack2.max_size());
    EXPECT_EQ(stack1.size(), stack2.size());
    while (!stack1.is_empty()) {
        EXPECT_EQ(stack1.top(), stack2.top());
        stack1.pop();
        stack2.pop();
    }
}
TEST(TestStackOnListLib, stack_is_empty_true) {
    // Arrange & Act
    StackOnList<int> stack;
    // Assert
    EXPECT_TRUE(stack.is_empty());
}
TEST(TestStackOnListLib, stack_is_empty_false) {
    // Arrange
    size_t max_size = 5;
    StackOnList<int> stack(max_size);
    // Act
    stack.push(10);
    // Assert
    EXPECT_FALSE(stack.is_empty());
}
TEST(TestStackOnListLib, stack_is_full_true) {
    // Arrange
    size_t max_size = 3;
    StackOnList<int> stack(max_size);
    // Act
    stack.push(4);
    stack.push(3);
    stack.push(7);
    // Assert
    EXPECT_TRUE(stack.is_full());
}
TEST(TestStackOnListLib, stack_is_full_false) {
    // Arrange
    size_t max_size = 7;
    StackOnList<int> stack(max_size);
    // Act
    stack.push(1);
    stack.push(9);
    // Assert
    EXPECT_FALSE(stack.is_full());
}
TEST(TestStackOnListLib, stack_push_element) {
    // Arrange 
    int element = 55;
    StackOnList<int> stack;
    // Act
    stack.push(element);
    // Assert
    EXPECT_EQ(stack.top(), element);
}
TEST(TestStackOnListLib, stack_push_element_with_exception) {
    // Arrange 
    size_t max_size = 1;
    int element = 100;
    StackOnList<int> stack(max_size);
    // Act
    stack.push(element);
    // Assert
    EXPECT_THROW(stack.push(200), std::logic_error);
}
TEST(TestStackOnListLib, stack_pop_element_with_exception) {
    // Arrange & Act
    StackOnList<int> stack;
    // Assert
    EXPECT_THROW(stack.pop(), std::logic_error);
}
TEST(TestStackOnListLib, stack_pop_element) {
    // Arrange 
    int element1 = 100;
    int element2 = 200;
    int element3 = 300;
    StackOnList<int> stack;
    // Act
    stack.push(element1);
    stack.push(element2);
    stack.push(element3);
    stack.pop();
    // Assert
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), element2);
}
TEST(TestStackOnListLib, stack_clear) {
    // Arrange 
    int element = 300;
    StackOnList<int> stack;
    // Act
    for (size_t i = 0; i < 15; ++i) {
        stack.push(element);
    }
    stack.clear();
    // Assert
    EXPECT_TRUE(stack.is_empty());
}
TEST(TestStackOnListLib, stack_operator_equall_expect_true) {
    // Arrange & Act
    StackOnList<int> stack;
    StackOnList<int> stack_other;
    // Assert
    EXPECT_TRUE(stack == stack_other);
}
TEST(TestStackOnListLib, stack_operator_equall_expect_false) {
    // Arrange & Act
    StackOnList<int> stack;
    stack.push(10);
    StackOnList<int> stack_other;
    stack_other.push(20);
    stack_other.push(25);
    // Assert
    EXPECT_FALSE(stack == stack_other);
}
TEST(TestStackOnListLib, stack_operator_assign) {
    //Arrange
    StackOnList<int> stack;
    StackOnList<int> stack_other;
    //Act
    stack_other.push(100);
    stack_other.push(200);
    stack = stack_other;
    //Assert
    EXPECT_TRUE(stack == stack_other);
}
TEST(TestStackOnListLib, stack_operator_not_equal_expect_true) {
    // Arrange & Act
    StackOnList<int> stack;
    stack.push(100);
    StackOnList<int> stack_other;
    stack_other.push(20);
    stack_other.push(35);
    // Assert
    EXPECT_TRUE(stack != stack_other);
}
TEST(TestStackOnListLib, stack_operator_not_equal_expect_false) {
    // Arrange & Act
    StackOnList<int> stack;
    stack.push(20);
    StackOnList<int> stack_other;
    stack_other.push(20);
    // Assert
    EXPECT_FALSE(stack != stack_other);
}
