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
