// Copyright 2025 Zabytina Julia

#include <gtest/gtest.h>
#include "../lib_list/List.h"
TEST(TestListLib, list_default_constructor) {
    // Arrange & Act
    List<int> list;
    // Assert
    EXPECT_EQ(list.get_head(), nullptr);
    EXPECT_EQ(list.get_tail(), nullptr);
    EXPECT_EQ(list.get_size(), 0);
}
TEST(TestListLib, list_copy_constructor) {
    // Arrange & Act
    List<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    List<int> list2(list1);
    // Assert
    EXPECT_NE(list1.get_head(), list2.get_head());
    EXPECT_NE(list1.get_tail(), list2.get_tail());

    EXPECT_EQ(list1.get_head()->value, list2.get_head()->value);
    EXPECT_EQ(list1.get_tail()->value, list2.get_tail()->value);
    EXPECT_EQ(list1.get_size(), list2.get_size());
}
TEST(TestListLib, list_is_empty_false) {
    // Arrange & Act
    List<int> list;
    list.push_back(10);
    list.push_back(10);
    // Assert
    EXPECT_FALSE(list.is_empty());
}
TEST(TestListLib, list_is_empty_true) {
    // Arrange & Act
    List<int> list;
    // Assert
    EXPECT_TRUE(list.is_empty());
}
TEST(TestListLib, push_front_with_empty_list) {
    // Arrange & Act
    List<int> list;
    list.push_front(10);
    // Assert
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.get_head(), list.get_tail());
}
TEST(TestListLib, push_front_with_several_elements_list) {
    // Arrange & Act
    List<int> list;
    list.push_front(100);
    list.push_front(200);
    list.push_front(300);
    list.push_front(400);
    list.push_front(500);
    // Assert
    EXPECT_EQ(list.get_head()->value, 500);
    EXPECT_EQ(list.get_size(), 5);
}
TEST(TestListLib, push_back_with_empty_list) {
    // Arrange & Act
    List<int> list;
    list.push_back(30);
    // Assert
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.get_head(), list.get_tail());
}
TEST(TestListLib, push_back_with_several_elements_list) {
    // Arrange & Act
    List<int> list;
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
TEST(TestListLib, pop_back_with_empty_list_exception) {
    // Arrange & Act
    List<int> list;
    // Assert
    ASSERT_THROW(list.pop_back(), std::logic_error);
}
TEST(TestListLib, pop_back_with_one_element_list) {
    // Arrange & Act
    List<int> list;
    list.push_back(10);
    list.pop_back();
    // Assert
    EXPECT_EQ(list.get_head(), nullptr);
    EXPECT_EQ(list.get_tail(), nullptr);
    EXPECT_EQ(list.get_size(), 0);
}
TEST(TestListLib, pop_back_with_several_elements_list) {
    // Arrange & Act
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);
    list.pop_back();
    list.pop_back();
    // Assert
    EXPECT_EQ(list.get_tail()->value, 30);
    EXPECT_EQ(list.get_size(), 3);
}
TEST(TestListLib, pop_front_with_empty_list_exception) {
    // Arrange & Act
    List<int> list;
    // Assert
    ASSERT_THROW(list.pop_front(), std::logic_error);
}
TEST(TestListLib, pop_front_with_one_element_list) {
    // Arrange & Act
    List<int> list;
    list.push_back(10);
    list.pop_front();
    // Assert
    EXPECT_EQ(list.get_head(), nullptr);
    EXPECT_EQ(list.get_tail(), nullptr);
    EXPECT_EQ(list.get_size(), 0);
}
TEST(TestListLib, pop_front_with_several_elements_list) {
    // Arrange & Act
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);
    list.push_back(60);
    list.push_back(70);

    list.pop_front();
    list.pop_front();
    list.pop_front();
    // Assert
    EXPECT_EQ(list.get_head()->value, 40);
    EXPECT_EQ(list.get_size(), 4);
}
TEST(TestListLib, list_operator_equal_true) {
    // Arrange & Act
    List<int> list1;
    List<int> list2;
    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);

    list2.push_back(10);
    list2.push_back(20);
    list2.push_back(30);
    // Assert
    EXPECT_TRUE(list1 == list2);
}
TEST(TestListLib, list_operator_equal_false) {
    // Arrange & Act
    List<int> list1;
    List<int> list2;
    list1.push_back(30);
    list1.push_back(40);
    list1.push_back(50);
    list1.push_back(100);

    list2.push_back(30);
    list2.push_back(40);
    list2.push_back(50);
    // Assert
    EXPECT_FALSE(list1 == list2);
}
TEST(TestListLib, list_operator_not_equal_true) {
    // Arrange & Act
    List<int> list1;
    List<int> list2;
    list1.push_back(70);
    list1.push_back(80);
    list1.push_back(90);
    list1.push_back(100);

    list2.push_back(10);
    list2.push_back(20);
    list2.push_back(30);
    // Assert
    EXPECT_TRUE(list1 != list2);
}
TEST(TestListLib, list_operator_not_equal_false) {
    // Arrange & Act
    List<int> list1;
    List<int> list2;
    list1.push_back(80);
    list1.push_back(80);
    list1.push_back(80);

    list2.push_back(80);
    list2.push_back(80);
    list2.push_back(80);
    // Assert
    EXPECT_FALSE(list1 != list2);
}
TEST(TestListLib, list_operator_assign) {
    // Arrange & Act
    List<int> list1;
    List<int> list2;
    list1.push_back(100);
    list1.push_back(800);
    list1.push_back(900);
    list1.push_back(600);

    list2.push_back(10);
    list2.push_back(20);
    list2.push_back(30);
    list2 = list1;
    // Assert
    EXPECT_TRUE(list1 == list2);
}
TEST(TestListLib, list_node_insert) {
    // Arrange
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);
    // Act
    Node<int>* node = list.get_head()->next;
    list.insert(node, 500);
    // Assert
    EXPECT_EQ(list.get_size(), 6);
    EXPECT_EQ(list.get_head()->value, 10);
    EXPECT_EQ(list.get_head()->next->value, 20);
    EXPECT_EQ(list.get_head()->next->next->value, 500); 
    EXPECT_EQ(list.get_head()->next->next->next->value, 30);
    EXPECT_EQ(list.get_head()->next->next->next->next->value, 40);
    EXPECT_EQ(list.get_head()->next->next->next->next->next->value, 50);
}
TEST(TestListLib, list_node_insert_with_exception) {
    // Arrange 
    List<int> list;
    Node<int>* node = list.get_head();
    // Act & Assert
    ASSERT_THROW(list.insert(node, 500), std::logic_error);
}
TEST(TestListLib, list_position_insert_in_begin) {
    // Arrange
    List<int> list;
    list.push_back(60);
    list.push_back(70);
    list.push_back(80);
    list.push_back(90);
    list.push_back(20);
    size_t position = 0;
    // Act
    list.insert(position, 700);
    // Assert
    EXPECT_EQ(list.get_size(), 6);
    EXPECT_EQ(list.get_head()->value, 700);
    EXPECT_EQ(list.get_head()->next->value, 60);
    EXPECT_EQ(list.get_head()->next->next->value, 70);
    EXPECT_EQ(list.get_head()->next->next->next->value, 80);
    EXPECT_EQ(list.get_head()->next->next->next->next->value, 90);
    EXPECT_EQ(list.get_head()->next->next->next->next->next->value, 20);
}
TEST(TestListLib, list_position_insert_in_end) {
    // Arrange
    List<int> list;
    list.push_back(30);
    list.push_back(30);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);
    size_t position = 4;
    // Act
    list.insert(position, 900);
    // Assert
    EXPECT_EQ(list.get_size(), 6);
    EXPECT_EQ(list.get_head()->value, 30);
    EXPECT_EQ(list.get_head()->next->value, 30);
    EXPECT_EQ(list.get_head()->next->next->value, 30);
    EXPECT_EQ(list.get_head()->next->next->next->value, 40);
    EXPECT_EQ(list.get_head()->next->next->next->next->value, 50);
    EXPECT_EQ(list.get_head()->next->next->next->next->next->value, 900);
}
TEST(TestListLib, list_position_insert) {
    // Arrange
    List<int> list;
    list.push_back(30);
    list.push_back(80);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);
    size_t position = 2;
    // Act
    list.insert(position, 250);
    // Assert
    EXPECT_EQ(list.get_size(), 6);
    EXPECT_EQ(list.get_head()->value, 30);
    EXPECT_EQ(list.get_head()->next->value, 80);
    EXPECT_EQ(list.get_head()->next->next->value, 250);
    EXPECT_EQ(list.get_head()->next->next->next->value, 30);
    EXPECT_EQ(list.get_head()->next->next->next->next->value, 40);
    EXPECT_EQ(list.get_head()->next->next->next->next->next->value, 50);
}
TEST(TestListLib, list_position_insert_with_exception) {
    // Arrange
    List<int> list;
    list.push_back(300);
    list.push_back(850);
    list.push_back(320);
    list.push_back(40);
    list.push_back(90);
    size_t position = 10;
    // Act & Assert
    ASSERT_THROW(list.insert(position, 500), std::invalid_argument);
}













TEST(TestListLib, list_position_erase_in_begin) {
    // Arrange
    List<int> list;
    list.push_back(60);
    list.push_back(70);
    list.push_back(80);
    list.push_back(90);
    list.push_back(20);
    size_t position = 0;
    // Act
    list.erase(position);
    // Assert
    EXPECT_EQ(list.get_size(), 4);
    EXPECT_EQ(list.get_head()->value, 70);
    EXPECT_EQ(list.get_head()->next->value, 80);
    EXPECT_EQ(list.get_head()->next->next->value, 90);
    EXPECT_EQ(list.get_head()->next->next->next->value, 20);
}
TEST(TestListLib, list_erase_erase_in_end) {
    // Arrange
    List<int> list;
    list.push_back(680);
    list.push_back(70);
    list.push_back(80);
    list.push_back(920);
    list.push_back(20);
    size_t position = 4;
    // Act
    list.erase(position);
    // Assert
    EXPECT_EQ(list.get_size(), 4);
    EXPECT_EQ(list.get_head()->value, 680);
    EXPECT_EQ(list.get_head()->next->value, 70);
    EXPECT_EQ(list.get_head()->next->next->value, 80);
    EXPECT_EQ(list.get_head()->next->next->next->value, 920);
}
TEST(TestListLib, list_position_erase) {
    // Arrange
    List<int> list;
    list.push_back(320);
    list.push_back(840);
    list.push_back(30);
    list.push_back(40);
    list.push_back(550);
    size_t position = 3;
    // Act
    list.erase(position);
    // Assert
    EXPECT_EQ(list.get_size(), 4);
    EXPECT_EQ(list.get_head()->value, 320);
    EXPECT_EQ(list.get_head()->next->value, 840);
    EXPECT_EQ(list.get_head()->next->next->value, 30);
    EXPECT_EQ(list.get_head()->next->next->next->value, 550);
}
TEST(TestListLib, list_position_erase_with_exception1) {
    // Arrange
    List<int> list;
    size_t position = 2;
    // Act & Assert
    ASSERT_THROW(list.erase(position), std::logic_error);
}
TEST(TestListLib, list_position_erase_with_exception2) {
    // Arrange
    List<int> list;
    list.push_back(32000);
    list.push_back(8220);
    list.push_back(320);
    list.push_back(40);
    list.push_back(50);
    size_t position = 10;
    // Act & Assert
    ASSERT_THROW(list.erase(position), std::invalid_argument);
}
TEST(TestListLib, list_node_erase) {
    // Arrange
    List<int> list;
    list.push_back(3270);
    list.push_back(840);
    list.push_back(30);
    list.push_back(40);
    list.push_back(55770);
    Node<int>* node = list.get_head()->next;
    // Act
    list.erase(node);
    // Assert
    EXPECT_EQ(list.get_size(), 4);
    EXPECT_EQ(list.get_head()->value, 3270);
    EXPECT_EQ(list.get_head()->next->value, 30);
    EXPECT_EQ(list.get_head()->next->next->value, 40);
    EXPECT_EQ(list.get_head()->next->next->next->value, 55770);
}
TEST(TestListLib, list_node_erase_with_exception1) {
    // Arrange
    List<int> list;
    Node<int>* node = list.get_head();
    // Act & Assert
    ASSERT_THROW(list.erase(node), std::logic_error);
}
TEST(TestListLib, list_node_erase_with_exception2) {
    // Arrange
    List<int> list;
    list.push_back(32000);
    list.push_back(8220);
    list.push_back(32100);
    list.push_back(10);
    list.push_back(10);
    Node<int>* node = new Node<int>(2300);
    // Act & Assert
    ASSERT_THROW(list.erase(node), std::invalid_argument);
}
