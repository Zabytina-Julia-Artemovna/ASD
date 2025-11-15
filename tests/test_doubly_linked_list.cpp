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
    list.push_back(19);
    // Assert
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.get_head(), list.get_tail());
}
TEST(TestDoublyLinkedListLib, push_back_with_several_elements_doubly_linked_list) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    list.push_back(300);
    list.push_back(0);
    list.push_back(500);
    list.push_back(3);
    list.push_back(5);
    list.push_back(800);
    list.push_back(2);
    // Assert
    EXPECT_EQ(list.get_tail()->value, 2);
    EXPECT_EQ(list.get_size(), 7);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_operator_equal_true) {
    // Arrange & Act
    DoublyLinkedList<int> list1;
    DoublyLinkedList<int> list2;
    list1.push_back(20);
    list1.push_back(20);
    list1.push_back(20);

    list2.push_back(20);
    list2.push_back(20);
    list2.push_back(20);
    // Assert
    EXPECT_TRUE(list1 == list2);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_operator_equal_false) {
    // Arrange & Act
    DoublyLinkedList<int> list1;
    DoublyLinkedList<int> list2;
    list1.push_back(29);
    list1.push_back(40);
    list1.push_back(22);
    list1.push_back(100);

    list2.push_back(30);
    list2.push_back(88);
    list2.push_back(66);
    // Assert
    EXPECT_FALSE(list1 == list2);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_operator_not_equal_true) {
    // Arrange & Act
    DoublyLinkedList<int> list1;
    DoublyLinkedList<int> list2;
    list1.push_back(70);
    list1.push_back(80);
    list1.push_back(90);
    list1.push_back(700);

    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);
    // Assert
    EXPECT_TRUE(list1 != list2);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_operator_not_equal_false) {
    // Arrange & Act
    DoublyLinkedList<int> list1;
    DoublyLinkedList<int> list2;
    list1.push_back(70);
    list1.push_back(70);
    list1.push_back(70);

    list2.push_back(70);
    list2.push_back(70);
    list2.push_back(70);
    // Assert
    EXPECT_FALSE(list1 != list2);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_operator_assign) {
    // Arrange & Act
    DoublyLinkedList<int> list1;
    DoublyLinkedList<int> list2;
    list1.push_back(30);
    list1.push_back(800);
    list1.push_back(70);
    list1.push_back(600);

    list2.push_back(30);
    list2.push_back(20);
    list2.push_back(30);
    list2 = list1;
    // Assert
    EXPECT_TRUE(list1 == list2);
}
TEST(TestDoublyLinkedListLib, push_front_with_empty_doubly_linked_list) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    list.push_front(10);
    // Assert
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.get_head(), list.get_tail());
}
TEST(TestDoublyLinkedListLib, push_front_with_several_elements_doubly_linked_list) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    list.push_front(100);
    list.push_front(550);
    list.push_front(39);
    list.push_front(400);
    list.push_front(30);
    // Assert
    EXPECT_EQ(list.get_head()->value, 30);
    EXPECT_EQ(list.get_size(), 5);
}
TEST(TestDoublyLinkedListLib, push_back_check_ñonnections_between_nodes_doubly_linked_list) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    // Assert
    EXPECT_EQ(list.get_head()->value, 10);
    EXPECT_EQ(list.get_head()->next->value, 20);
    EXPECT_EQ(list.get_head()->next->next->value, 30);

    EXPECT_EQ(list.get_tail()->value, 30);
    EXPECT_EQ(list.get_tail()->previous->value, 20);
    EXPECT_EQ(list.get_tail()->previous->previous->value, 10);
}
TEST(TestDoublyLinkedListLib, push_back_check_boundary_conditions_doubly_linked_list) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    // Assert
    EXPECT_EQ(list.get_head()->previous, nullptr);
    EXPECT_EQ(list.get_tail()->next, nullptr);
}
TEST(TestDoublyLinkedListLib, push_front_check_ñonnections_between_nodes_doubly_linked_list) {
    DoublyLinkedList<int> list; 
    list.push_front(10);
    list.push_front(20); 
    list.push_front(30);

    EXPECT_EQ(list.get_head()->value, 30);
    EXPECT_EQ(list.get_head()->next->value, 20);
    EXPECT_EQ(list.get_head()->next->next->value, 10);

    EXPECT_EQ(list.get_tail()->value, 10);
    EXPECT_EQ(list.get_tail()->previous->value, 20);
    EXPECT_EQ(list.get_tail()->previous->previous->value, 30);
}
TEST(TestDoublyLinkedListLib, push_front_check_boundary_conditions_doubly_linked_list) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    // Assert
    EXPECT_EQ(list.get_head()->previous, nullptr);
    EXPECT_EQ(list.get_tail()->next, nullptr);
}
TEST(TestDoublyLinkedListLib, pop_back_with_empty_doubly_linked_list_exception) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    // Assert
    ASSERT_THROW(list.pop_back(), std::logic_error);
}
TEST(TestDoublyLinkedListLib, pop_back_with_one_doubly_linked_list_list) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    list.push_back(30);
    list.pop_back();
    // Assert
    EXPECT_EQ(list.get_head(), nullptr);
    EXPECT_EQ(list.get_tail(), nullptr);
    EXPECT_EQ(list.get_size(), 0);
}
TEST(TestDoublyLinkedListLib, pop_back_with_several_elements_doubly_linked_list) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    list.push_back(40);
    list.push_back(44);
    list.push_back(43);
    list.push_back(1);
    list.push_back(5);
    list.pop_back();
    list.pop_back();
    // Assert
    EXPECT_EQ(list.get_tail()->value, 43);
    EXPECT_EQ(list.get_size(), 3);
}
TEST(TestDoublyLinkedListLib, pop_front_with_empty_doubly_linked_list_exception) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    // Assert
    ASSERT_THROW(list.pop_front(), std::logic_error);
}
TEST(TestDoublyLinkedListLib, pop_front_with_one_element_doubly_linked_list) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    list.push_back(79);
    list.pop_front();
    // Assert
    EXPECT_EQ(list.get_head(), nullptr);
    EXPECT_EQ(list.get_tail(), nullptr);
    EXPECT_EQ(list.get_size(), 0);
}
TEST(TestDoublyLinkedListLib, pop_front_with_several_elements_doubly_linked_list) {
    // Arrange & Act
    DoublyLinkedList<int> list;
    list.push_back(1110);
    list.push_back(20);
    list.push_back(52);
    list.push_back(4);
    list.push_back(5220);
    list.push_back(50);
    list.push_back(50);

    list.pop_front();
    list.pop_front();
    list.pop_front();
    // Assert
    EXPECT_EQ(list.get_head()->value, 4);
    EXPECT_EQ(list.get_size(), 4);
}
