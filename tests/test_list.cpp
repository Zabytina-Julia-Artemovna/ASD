// Copyright 2025 Zabytina Julia

#include <gtest/gtest.h>
#include "../lib_list/List.h"
TEST(TestListLib, list_default_constructor) {
    // Arrange & Act
    List<int> list;
    // Assert
    EXPECT_EQ(list.get_head(), nullptr);
    EXPECT_EQ(list.get_tail(), nullptr);
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
}
