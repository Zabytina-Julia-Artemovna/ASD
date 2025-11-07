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
