// Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <gtest/gtest.h>
#include "../lib_stack/stack.h"

TEST(TestStackLib, stack_constructor_with_size) {
    // Arrange & Act
    size_t size = 10;
    Stack<int> stack(size);
    // Assert
    EXPECT_EQ(stack.getData().get_size(), size);
    EXPECT_EQ(stack.getData().get_capacity(), size+15);
}
TEST(TestStackLib, stack_copy_constructor) {
    // Arrange & Act
    size_t size = 10;
    Stack<int> stack1(size);
    Stack<int> stack2(stack1);
    // Assert
    EXPECT_TRUE(stack1 == stack2);
}
TEST(TestStackLib, stack_push_element) {
    // Arrange 
    size_t size = 10;
    int element = 100;
    Stack<int> stack(size);
    // Act
    stack.push(element);
    // Assert
    EXPECT_EQ(stack.top(), element);
}
TEST(TestStackLib, stack_push_element_with_exception) {
    // Arrange 
    size_t size = 0;
    int element = 100;
    Stack<int> stack(size);
    // Act
    for (size_t i = 0; i < 15; ++i) {
        stack.push(element);
    }
    // Assert
    EXPECT_THROW(stack.push(element), std::logic_error);
}
TEST(TestStackLib, stack_pop_element_with_exception) {
    // Arrange & Act
    size_t size = 0;
    Stack<int> stack(size);
    // Assert
    EXPECT_THROW(stack.pop(), std::logic_error);
}
TEST(TestStackLib, stack_pop_element) {
    // Arrange 
    size_t size = 10;
    int element1 = 100;
    int element2 = 200;
    int element3 = 300;
    Stack<int> stack(size);
    // Act
    stack.push(element1);
    stack.push(element2);
    stack.push(element3);
    stack.pop();
    // Assert
    EXPECT_EQ(stack.top(), element2);
}
TEST(TestStackLib, stack_is_full) {
    // Arrange 
    size_t size = 0;
    int element = 300;
    Stack<int> stack(size);
    // Act
    for (size_t i = 0; i < 15; ++i) {
        stack.push(element);
    }
    // Assert
    EXPECT_TRUE(stack.is_full());
}
TEST(TestStackLib, stack_is_empty) {
    // Arrange 
    size_t size = 0;
    Stack<int> stack(size);
    // Assert & Act
    EXPECT_TRUE(stack.is_empty());
}
TEST(TestStackLib, stack_clear) {
    // Arrange 
    size_t size = 0;
    int element = 300;

    Stack<int> stack(size);
    // Act
    for (size_t i = 0; i < 15; ++i) {
        stack.push(element);
    }
    stack.clear();
    // Assert
    EXPECT_TRUE(stack.is_empty());
}
TEST(TestStackLib, stack_top) {
    // Arrange 
    size_t size = 0;
    int common_element = 100;
    int last_element = 999;
    Stack<int> stack(size);
    // Act
    for (size_t i = 0; i < 14; ++i) {
        stack.push(common_element);
    }
    stack.push(last_element);
    // Assert
    EXPECT_EQ(stack.top(), last_element);
}
TEST(TestStackLib, stack_top_with_exception) {
    // Arrange & Act
    size_t size = 0;
    Stack<int> stack(size);
    // Assert
    EXPECT_THROW(stack.top(), std::logic_error);
}
TEST(TestStackLib, stack_operator_compare_expect_true) {
    // Arrange & Act
    size_t size = 10;
    Stack<int> stack(size);
    Stack<int> stack_other(size);
    // Assert
    EXPECT_TRUE(stack == stack_other);
}
TEST(TestStackLib, stack_operator_compare_expect_false) {
    // Arrange & Act
    size_t size1 = 10;
    size_t size2 = 20;
    Stack<int> stack(size1);
    Stack<int> stack_other(size2);
    // Assert
    EXPECT_FALSE(stack == stack_other);
}
TEST(TestStackLib, stack_operator_assign) {
    //Arrange
    size_t size1 = 10;
    size_t size2 = 20;
    Stack<int> stack(size1);
    Stack<int> stack_other(size2);
    //Act
    stack_other.push(100);
    stack_other.push(200);
    stack = stack_other;
    //Assert
    EXPECT_TRUE(stack == stack_other);
    EXPECT_EQ(stack.top(), 200);
}
TEST(TestStackLib, stack_operator_not_compare_expect_true) {
    // Arrange & Act
    size_t size = 10;
    Stack<int> stack(size);
    Stack<int> stack_other(size);
    // Assert
    EXPECT_FALSE(stack != stack_other);
}
TEST(TestStackLib, stack_operator_not_compare_expect_false) {
    // Arrange & Act
    size_t size1 = 10;
    size_t size2 = 20;
    Stack<int> stack(size1);
    Stack<int> stack_other(size2);
    // Assert
    EXPECT_TRUE(stack != stack_other);
}
