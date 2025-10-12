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
