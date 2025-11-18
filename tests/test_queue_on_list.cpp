// Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <gtest/gtest.h>
#include "../lib_queue_on_list/queue_on_list.h"

TEST(TestQueueOnListLib, queue_constructor_with_size) {
    // Arrange & Act
    size_t max_size = 10;
    QueueOnList<int> queue(max_size);
    // Assert
    EXPECT_EQ(queue.max_size(), max_size);
    EXPECT_EQ(queue.size(), 0);
    EXPECT_TRUE(queue.is_empty());
}
TEST(TestQueueOnListLib, queue_constructor_with_size_default) {
    // Arrange & Act
    QueueOnList<int> queue;
    // Assert
    EXPECT_EQ(queue.size(), 0);
    EXPECT_FALSE(queue.has_max_size());
    EXPECT_TRUE(queue.is_empty());
}
TEST(TestQueueOnListLib, queue_copy_constructor) {
    // Arrange
    size_t max_size = 5;
    QueueOnList<int> queue1(max_size);
    queue1.push(5);
    queue1.push(6);
    queue1.push(7);
    // Act
    QueueOnList<int> queue2(queue1);
    // Assert
    EXPECT_EQ(queue1.max_size(), queue2.max_size());
    EXPECT_EQ(queue1.size(), queue2.size());
    while (!queue1.is_empty()) {
        EXPECT_EQ(queue1.head(), queue2.head());
        queue1.pop();
        queue2.pop();
    }
}
TEST(TestQueueOnListLib, queue_is_empty_true) {
    // Arrange & Act
    QueueOnList<int> queue;
    // Assert
    EXPECT_TRUE(queue.is_empty());
}
TEST(TestQueueOnListLib, queue_is_empty_false) {
    // Arrange
    size_t max_size = 3;
    QueueOnList<int> queue(max_size);
    // Act
    queue.push(5);
    // Assert
    EXPECT_FALSE(queue.is_empty());
}
TEST(TestQueueOnListLib, queue_is_full_true) {
    // Arrange
    size_t max_size = 3;
    QueueOnList<int> queue(max_size);
    // Act
    queue.push(30);
    queue.push(22);
    queue.push(12);
    // Assert
    EXPECT_TRUE(queue.is_full());
}
TEST(TestQueueOnListLib, queue_is_full_false) {
    // Arrange
    size_t max_size = 5;
    QueueOnList<int> queue(max_size);
    // Act
    queue.push(1);
    queue.push(3);
    // Assert
    EXPECT_FALSE(queue.is_full());
}
TEST(TestQueueOnListLib, queue_get_head) {
    // Arrange
    size_t max_size = 6;
    QueueOnList<int> queue(max_size);
    // Act
    queue.push(10);
    queue.push(23);
    queue.push(30);
    // Assert
    EXPECT_EQ(queue.head(), 10);
}
TEST(TestQueueOnListLib, queue_get_tail) {
    // Arrange
    size_t max_size = 6;
    QueueOnList<int> queue(max_size);
    // Act
    queue.push(70);
    queue.push(5);
    queue.push(50);
    // Assert
    EXPECT_EQ(queue.tail(), 50);
}
TEST(TestQueueOnListLib, queue_empty_get_head_exception) {
    // Arrange & Act
    QueueOnList<int> queue;
    // Assert
    ASSERT_THROW(queue.head(), std::runtime_error);
}
TEST(TestQueueOnListLib, queue_empty_get_tail_exception) {
    // Arrange & Act
    size_t max_size = 10;
    QueueOnList<int> queue(max_size);
    // Assert
    ASSERT_THROW(queue.tail(), std::runtime_error);
}
TEST(TestQueueOnListLib, queue_push) {
    // Arrange
    QueueOnList<int> queue(5);
    // Act
    queue.push(22);
    queue.push(55);
    queue.push(77);
    // Assert
    EXPECT_EQ(queue.head(), 22);
    EXPECT_EQ(queue.tail(), 77);
    EXPECT_EQ(queue.size(), 3);
}
TEST(TestQueueOnListLib, queue_pop) {
    // Arrange
    QueueOnList<int> queue(8);
    // Act
    queue.push(22);
    queue.push(34);
    queue.push(27);
    queue.pop();
    queue.pop();
    // Assert
    EXPECT_EQ(queue.head(), queue.tail());
    EXPECT_EQ(queue.head(), 27);
    EXPECT_EQ(queue.size(), 1);
}
TEST(TestQueueOnListLib, queue_push_exception) {
    // Arrange
    QueueOnList<int> queue(3);
    // Act
    queue.push(20);
    queue.push(10);
    queue.push(30);
    // Assert
    ASSERT_THROW(queue.push(9), std::logic_error);
}
TEST(TestQueueOnListLib, queue_pop_exception) {
    // Arrange & Act
    QueueOnList<int> queue(10);
    // Assert
    ASSERT_THROW(queue.pop(), std::logic_error);
}
TEST(TestQueueOnListLib, queue_clear) {
    // Arrange
    QueueOnList<int> queue(10);
    queue.push(2);
    queue.push(76);
    queue.push(34);
    queue.push(25);
    queue.push(1);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    // Act
    queue.clear();
    // Assert
    EXPECT_TRUE(queue.is_empty());
    EXPECT_EQ(queue.max_size(), 10);
}
