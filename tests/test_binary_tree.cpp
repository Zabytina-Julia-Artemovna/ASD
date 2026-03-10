// Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <sstream>
#include <gtest/gtest.h>
#include "../lib_binary_tree/binary_tree.h"
#include "../lib_polynom/polynom.h"

static void expect_polynom_equal(const Polynom& expected, const Polynom& actual) {
    std::stringstream ss_expected, ss_actual;
    ss_expected << expected;
    ss_actual << actual;
    EXPECT_EQ(ss_expected.str(), ss_actual.str());
}

TEST(TestBinaryTreeLib, binary_tree_default_constructor) {
    // Arrange & Act
    BinaryTree<std::string, Polynom> tree;
    // Assert
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestBinaryTreeLib, binary_tree_insert) {
    // Arrange
    BinaryTree<std::string, Polynom> tree;
    std::string key = "polynom1";
    Polynom value("x^2 + y");

    // Act
    tree.insert(key, value);

    // Assert
    Polynom* result = tree.find(key);
    ASSERT_NE(result, nullptr);
    expect_polynom_equal(value, *result);
}
TEST(TestBinaryTreeLib, binary_tree_insert_and_erase) {
    // Arrange
    BinaryTree<std::string, Polynom> tree;
    std::string key1 = "polynom1";
    Polynom value1("x^2 + y");
    std::string key2 = "polynom2";
    Polynom value2("x + y");
    std::string key3 = "polynom3";
    Polynom value3("10.8x^3 + z^2");

    // Act & Assert - вставка
    tree.insert(key1, value1);
    tree.insert(key2, value2);
    tree.insert(key3, value3);

    Polynom* result1 = tree.find(key1);
    ASSERT_NE(result1, nullptr);
    expect_polynom_equal(value1, *result1);

    Polynom* result2 = tree.find(key2);
    ASSERT_NE(result2, nullptr);
    expect_polynom_equal(value2, *result2);

    Polynom* result3 = tree.find(key3);
    ASSERT_NE(result3, nullptr);
    expect_polynom_equal(value3, *result3);

    // Act 
    tree.erase(key2);
    tree.erase(key1);

    // Assert 
    EXPECT_EQ(tree.find(key1), nullptr);
    EXPECT_EQ(tree.find(key2), nullptr);

    ASSERT_THROW(tree.erase(key1), std::invalid_argument);
    ASSERT_THROW(tree.erase(key2), std::invalid_argument);

    Polynom* result3_after = tree.find(key3);
    ASSERT_NE(result3_after, nullptr);
    expect_polynom_equal(value3, *result3_after);

    // Act 
    tree.insert(key1, value1);

    // Assert 
    Polynom* result1_again = tree.find(key1);
    ASSERT_NE(result1_again, nullptr);
    expect_polynom_equal(value1, *result1_again);
}
TEST(TestBinaryTreeLib, binary_tree_find_nonexistent) {
    // Arrange
    BinaryTree<std::string, Polynom> tree;
    tree.insert("key1", Polynom("x + y"));

    // Act & Assert
    EXPECT_EQ(tree.find("nonexistent"), nullptr);
}
TEST(TestBinaryTreeLib, binary_tree_empty) {
    // Arrange
    BinaryTree<std::string, Polynom> tree;

    // Assert 
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.find("anything"), nullptr);
    EXPECT_THROW(tree.erase("anything"), std::logic_error);

    // Act 
    tree.insert("only", Polynom("x"));
    EXPECT_FALSE(tree.is_empty());

    tree.erase("only");

    // Assert 
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.find("only"), nullptr);
}
TEST(TestBinaryTreeLib, binary_tree_clear) {
    // Arrange
    BinaryTree<std::string, Polynom> tree;
    tree.insert("key1", Polynom("x + y"));
    tree.insert("key2", Polynom("x^2"));

    // Act
    tree.clear();

    // Assert
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.find("key1"), nullptr);
    EXPECT_EQ(tree.find("key2"), nullptr);
}