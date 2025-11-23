// Copyright 2025 Julia Zabytina
#include <gtest/gtest.h>
#include "../lib_dsu/dsu.h"

TEST(TestDSULib, dsu_constructor_with_size) {
    // Arrange & Act
    size_t size = 6;
    DSU dsu(size);
    // Assert
    EXPECT_EQ(dsu.size(), size);
    for (size_t i = 0; i < dsu.size(); i++) {
        EXPECT_EQ(dsu.parent()[i], i);
        EXPECT_EQ(dsu.rank()[i], 0);
    }
}
TEST(TestDSULib, dsu_copy_constructor) {
    // Arrange
    size_t size = 10;
    DSU dsu1(size);
    // Act
    DSU dsu2(dsu1);
    // Assert
    EXPECT_EQ(dsu1.size(), dsu2.size());
    for (size_t i = 0; i < dsu2.size(); i++) {
        EXPECT_EQ(dsu1.parent()[i], dsu2.parent()[i]);
        EXPECT_EQ(dsu1.rank()[i], dsu2.rank()[i]);
    }
}
TEST(TestDSULib, dsu_union) {
    // Arrange & Act
    size_t size = 4;
    DSU dsu(size);
    dsu.dsu_union(1, 2);
    dsu.dsu_union(1, 3);
    // Assert
    EXPECT_EQ(dsu.size(), size);
    EXPECT_EQ(dsu.rank()[1], 1);
    EXPECT_EQ(dsu.parent()[2], 1);
    EXPECT_EQ(dsu.parent()[3], 1);
}
TEST(TestDSULib, dsu_union_with_exception) {
    // Arrange & Act
    size_t size = 5;
    DSU dsu(size);
    // Assert
    ASSERT_THROW(dsu.dsu_union(-1, 2), std::logic_error);
}
TEST(TestDSULib, dsu_find_recursive) {
    // Arrange & Act
    size_t size = 7;
    DSU dsu(size);
    dsu.dsu_union(5, 4);
    dsu.dsu_union(5, 6);
    // Assert
    EXPECT_EQ(dsu.dsu_find_recursive(6), 5);
    EXPECT_EQ(dsu.dsu_find_recursive(4), 5);
}
TEST(TestDSULib, dsu_find_recursive_with_exception) {
    // Arrange & Act
    size_t size = 3;
    DSU dsu(size);
    // Assert
    ASSERT_THROW(dsu.dsu_find_recursive(5), std::logic_error);
}
TEST(TestDSULib, dsu_operator_assign) {
    // Arrange & Act
    size_t size = 3;
    DSU dsu1(size);
    DSU dsu2 = dsu1;
    // Assert
    EXPECT_EQ(dsu1.size(), dsu2.size());
    for (size_t i = 0; i < size; i++) {
        EXPECT_EQ(dsu1.parent()[i], dsu2.parent()[i]);
        EXPECT_EQ(dsu1.rank()[i], dsu2.rank()[i]);
    }
}
