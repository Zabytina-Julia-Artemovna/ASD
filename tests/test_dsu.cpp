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
