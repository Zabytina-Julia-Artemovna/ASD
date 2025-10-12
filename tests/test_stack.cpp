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
    // Assert
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
