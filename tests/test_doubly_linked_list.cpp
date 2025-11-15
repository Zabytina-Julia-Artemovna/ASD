#include <gtest/gtest.h>
#include "../lib_doubly_linked_list/doubly_linked_list.h"
TEST(TestDoublyLinkedListLib, doubly_linked_list_default_constructor) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    // Assert
    EXPECT_EQ(list.get_head(), nullptr);
    EXPECT_EQ(list.get_tail(), nullptr);
    EXPECT_EQ(list.get_size(), 0);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_copy_constructor) {
    // Arrange & Act
    DoublyLinkedList<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    DoublyLinkedList<int> list2(list1);
    // Assert
    EXPECT_NE(list1.get_head(), list2.get_head());
    EXPECT_NE(list1.get_tail(), list2.get_tail());

    EXPECT_EQ(list1.get_head()->value, list2.get_head()->value);
    EXPECT_EQ(list1.get_tail()->value, list2.get_tail()->value);
    EXPECT_EQ(list1.get_size(), list2.get_size());
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_is_empty_false) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(10);
    // Assert
    EXPECT_FALSE(list.is_empty());
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_is_empty_true) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    // Assert
    EXPECT_TRUE(list.is_empty());
}
TEST(TestDoublyLinkedListLib, push_back_with_empty_doubly_linked_list) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    list.push_back(30);
    // Assert
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.get_head(), list.get_tail());
}
TEST(TestDoublyLinkedListLib, push_back_with_several_elements_doubly_linked_list) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    list.push_back(300);
    list.push_back(400);
    list.push_back(500);
    list.push_back(600);
    list.push_back(700);
    list.push_back(800);
    list.push_back(900);
    // Assert
    EXPECT_EQ(list.get_tail()->value, 900);
    EXPECT_EQ(list.get_size(), 7);
}
