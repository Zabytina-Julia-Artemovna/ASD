// Copyright 2025 Zabytina Julia
#include <gtest/gtest.h>
#include "../lib_queue/queue.h"
TEST(TestQueueLib, queue_constructor_with_size) {
    // Arrange & Act
    size_t size = 10;
    Queue<int> queue(size);
    // Assert
    EXPECT_EQ(queue.size(), size);
    EXPECT_EQ(queue.count(), 0);
    EXPECT_TRUE(queue.is_empty());
}
TEST(TestQueueLib, queue_copy_constructor) {
    // Arrange
    size_t size = 5;
    Queue<int> queue1(size);
    queue1.push(10);
    queue1.push(20);
    queue1.push(30);
    // Act
    Queue<int> queue2(queue1);
    // Assert
    EXPECT_EQ(queue1.size(), queue2.size());
    EXPECT_EQ(queue1.count(), queue2.count());
    while (!queue1.is_empty()) {
        EXPECT_EQ(queue1.head(), queue2.head());
        queue1.pop();
        queue2.pop();
    }
}
TEST(TestQueueLib, queue_is_empty_true) {
    // Arrange & Act
    Queue<int> queue(10);
    // Assert
    EXPECT_TRUE(queue.is_empty());
}
TEST(TestQueueLib, queue_is_empty_false) {
    // Arrange
    size_t size = 3;
    Queue<int> queue(size);
    // Act
    queue.push(10);
    // Assert
    EXPECT_FALSE(queue.is_empty());
}
TEST(TestQueueLib, queue_is_full_true) {
    // Arrange
    size_t size = 3;
    Queue<int> queue(size);
    // Act
    queue.push(30);
    queue.push(240);
    queue.push(190);
    // Assert
    EXPECT_TRUE(queue.is_full());
}
TEST(TestQueueLib, queue_is_full_false) {
    // Arrange
    size_t size = 5;
    Queue<int> queue(size);
    // Act
    queue.push(10);
    queue.push(30);
    // Assert
    EXPECT_FALSE(queue.is_full());
}
TEST(TestQueueLib, queue_get_head) {
    // Arrange
    size_t size = 6;
    Queue<int> queue(size);
    // Act
    queue.push(10);
    queue.push(20);
    queue.push(30);
    // Assert
    EXPECT_EQ(queue.head(), 10);
}
TEST(TestQueueLib, queue_get_tail) {
    // Arrange
    size_t size = 6;
    Queue<int> queue(size);
    // Act
    queue.push(70);
    queue.push(230);
    queue.push(50);
    // Assert
    EXPECT_EQ(queue.tail(), 50);
}
TEST(TestQueueLib, queue_empty_get_head_exception) {
    // Arrange & Act
    size_t size = 5;
    Queue<int> queue(size);
    // Assert
    ASSERT_THROW(queue.head(), std::runtime_error);
}
TEST(TestQueueLib, queue_empty_get_tail_exception) {
    // Arrange & Act
    size_t size = 9;
    Queue<int> queue(size);
    // Assert
    ASSERT_THROW(queue.tail(), std::runtime_error);
}
TEST(TestQueueLib, queue_circular_behavior) {
    // Arrange
    Queue<int> queue(3);
    // Act
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.pop();
    queue.push(4); 
    // Assert
    EXPECT_EQ(queue.head(), 2);
    EXPECT_EQ(queue.tail(), 4);
}