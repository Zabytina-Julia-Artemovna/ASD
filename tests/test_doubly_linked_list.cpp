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
TEST(TestDoublyLinkedListLib, doubly_linked_list_position_insert_in_end) {
    // Arrange
    DoublyLinkedList<int> list;
    list.push_back(320);
    list.push_back(22);
    list.push_back(1000);
    list.push_back(42);
    list.push_back(520);
    size_t position = 4;
    // Act
    list.insert(position, 900);
    // Assert
    EXPECT_EQ(list.get_size(), 6);
    EXPECT_EQ(list.get_head()->value, 320);
    EXPECT_EQ(list.get_head()->next->value, 22);
    EXPECT_EQ(list.get_head()->next->next->value, 1000);
    EXPECT_EQ(list.get_head()->next->next->next->value, 42);
    EXPECT_EQ(list.get_head()->next->next->next->next->value, 520);
    EXPECT_EQ(list.get_head()->next->next->next->next->next->value, 900);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_position_insert) {
    // Arrange
    DoublyLinkedList<int> list;
    list.push_back(30);
    list.push_back(4);
    list.push_back(30);
    list.push_back(2);
    list.push_back(3);
    size_t position = 2;
    // Act
    list.insert(position, 250);
    // Assert
    EXPECT_EQ(list.get_size(), 6);
    EXPECT_EQ(list.get_head()->value, 30);
    EXPECT_EQ(list.get_head()->next->value, 4);
    EXPECT_EQ(list.get_head()->next->next->value, 250);
    EXPECT_EQ(list.get_head()->next->next->next->value, 30);
    EXPECT_EQ(list.get_head()->next->next->next->next->value, 2);
    EXPECT_EQ(list.get_head()->next->next->next->next->next->value, 3);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_position_insert_with_exception) {
    // Arrange
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(50);
    list.push_back(30);
    list.push_back(40);
    list.push_back(1);
    size_t position = 10;
    // Act & Assert
    ASSERT_THROW(list.insert(position, 500), std::invalid_argument);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_node_insert) {
    // Arrange
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(2);
    list.push_back(30);
    list.push_back(77);
    list.push_back(50);
    // Act
    Node<int>* node = list.get_head()->next;
    list.insert(node, 700);
    // Assert
    EXPECT_EQ(list.get_size(), 6);
    EXPECT_EQ(list.get_head()->value, 10);
    EXPECT_EQ(list.get_head()->next->value, 2);
    EXPECT_EQ(list.get_head()->next->next->value, 700);
    EXPECT_EQ(list.get_head()->next->next->next->value, 30);
    EXPECT_EQ(list.get_head()->next->next->next->next->value, 77);
    EXPECT_EQ(list.get_head()->next->next->next->next->next->value, 50);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_node_insert_with_exception) {
    // Arrange 
    DoublyLinkedList<int> list;
    Node<int>* node = list.get_head();
    // Act & Assert
    ASSERT_THROW(list.insert(node, 1), std::logic_error);
}


TEST(TestDoublyLinkedListLib, doubly_linked_list_position_erase_in_begin) {
    // Arrange
    DoublyLinkedList<int> list;
    list.push_back(3);
    list.push_back(7);
    list.push_back(830);
    list.push_back(1);
    list.push_back(20);
    size_t position = 0;
    // Act
    list.erase(position);
    // Assert
    EXPECT_EQ(list.get_size(), 4);
    EXPECT_EQ(list.get_head()->value, 7);
    EXPECT_EQ(list.get_head()->next->value, 830);
    EXPECT_EQ(list.get_head()->next->next->value, 1);
    EXPECT_EQ(list.get_head()->next->next->next->value, 20);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_position_erase_in_end) {
    // Arrange
    DoublyLinkedList<int> list;
    list.push_back(60);
    list.push_back(2);
    list.push_back(80);
    list.push_back(90);
    list.push_back(20);
    size_t position = 4;
    // Act
    list.erase(position);
    // Assert
    EXPECT_EQ(list.get_size(), 4);
    EXPECT_EQ(list.get_head()->value, 60);
    EXPECT_EQ(list.get_head()->next->value, 2);
    EXPECT_EQ(list.get_head()->next->next->value, 80);
    EXPECT_EQ(list.get_head()->next->next->next->value, 90);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_position_erase) {
    // Arrange
    DoublyLinkedList<int> list;
    list.push_back(320);
    list.push_back(4);
    list.push_back(0);
    list.push_back(40);
    list.push_back(570);
    size_t position = 3;
    // Act
    list.erase(position);
    // Assert
    EXPECT_EQ(list.get_size(), 4);
    EXPECT_EQ(list.get_head()->value, 320);
    EXPECT_EQ(list.get_head()->next->value, 4);
    EXPECT_EQ(list.get_head()->next->next->value, 0);
    EXPECT_EQ(list.get_head()->next->next->next->value, 570);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_position_erase_with_exception1) {
    // Arrange
    DoublyLinkedList<int> list;
    size_t position = 100;
    // Act & Assert
    ASSERT_THROW(list.erase(position), std::invalid_argument);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_position_erase_with_exception2) {
    // Arrange
    DoublyLinkedList<int> list;
    list.push_back(32000);
    list.push_back(8220);
    list.push_back(320);
    list.push_back(40);
    list.push_back(50);
    size_t position = 20;
    // Act & Assert
    ASSERT_THROW(list.erase(position), std::invalid_argument);
}

TEST(TestDoublyLinkedListLib, doubly_linked_list_node_erase) {
    // Arrange
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(840007);
    list.push_back(3);
    list.push_back(40);
    list.push_back(55770);
    Node<int>* node = list.get_head()->next;
    // Act
    list.erase(node);
    // Assert
    EXPECT_EQ(list.get_size(), 4);
    EXPECT_EQ(list.get_head()->value, 1);
    EXPECT_EQ(list.get_head()->next->value, 3);
    EXPECT_EQ(list.get_head()->next->next->value, 40);
    EXPECT_EQ(list.get_head()->next->next->next->value, 55770);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_node_erase_with_exception) {
    // Arrange
    DoublyLinkedList<int> list;
    Node<int>* node = list.get_head();
    // Act & Assert
    ASSERT_THROW(list.erase(node), std::logic_error);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_iterator_read) {
    // Arrange
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(3);
    list.push_back(17);
    // Act 
    auto it = list.begin();
    it += 2;
    // Assert
    EXPECT_EQ(17, *it);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_iterator_write) {
    // Arrange
    DoublyLinkedList<int> list;
    list.push_back(50);
    list.push_back(1);
    list.push_back(79876);
    list.push_back(12);
    list.push_back(300);
    // Act 
    auto it = list.begin();
    it += 3;
    // Assert
    EXPECT_EQ(12, *it);
    *it = 900;
    EXPECT_EQ(900, *it);
}
TEST(TestDoublyLinkedListLib, doubly_linked_list_iterator_empty_list) {
    // Arrange
    DoublyLinkedList<int> list;
    // Act & Assert
    EXPECT_EQ(list.begin(), list.end());

    auto it = list.begin();
    ++it;
    EXPECT_EQ(it, list.end());

    auto end_it = list.end();
    ++end_it;
    EXPECT_EQ(end_it, list.end());

    auto it2 = list.begin();
    it2 += 5;
    EXPECT_EQ(it2, list.end());
}
