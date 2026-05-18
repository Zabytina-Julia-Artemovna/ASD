// Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <sstream>
#include <gtest/gtest.h>
#include "../lib_binary_search_tree/binary_search_tree.h"
#include "../lib_polynom/polynom.h"

static void expect_polynom_equal(const Polynom& expected, const Polynom& actual) {
    std::stringstream ss_expected, ss_actual;
    ss_expected << expected;
    ss_actual << actual;
    EXPECT_EQ(ss_expected.str(), ss_actual.str());
}

TEST(TestBinarySearchTreeLib, binary_search_tree_default_constructor) {
    // Arrange & Act
    BinarySearchTree<std::pair<std::string, Polynom>> tree;
    // Assert
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestBinarySearchTreeLib, binary_search_tree_copy_constructor) {
    // Arrange & Act
    BinarySearchTree<std::pair<std::string, Polynom>> tree1;
    Polynom p("x^2");
    std::string key = "p";
    tree1.insert({ key, p });
    BinarySearchTree<std::pair<std::string, Polynom>> tree2(tree1);
    // Assert
    EXPECT_FALSE(tree1.is_empty());
    EXPECT_FALSE(tree2.is_empty());
    Polynom* in_tree1 = tree1.find(key);
    Polynom* in_tree2 = tree2.find(key);
    expect_polynom_equal(*in_tree1, *in_tree2);
}

TEST(TestBinarySearchTreeLib, binary_search_tree_insert) {
    // Arrange
    BinarySearchTree<std::pair<std::string, Polynom>> tree;
    std::string key = "polynom1";
    Polynom value("x^2 + y");
    // Act
    tree.insert({ key, value });
    // Assert
    Polynom* result = tree.find(key);
    ASSERT_NE(result, nullptr);
    expect_polynom_equal(value, *result);
}

TEST(TestBinarySearchTreeLib, binary_search_tree_erase_root) {
    // Arrange
    BinarySearchTree<std::pair<std::string, Polynom>> tree;
    std::string key = "root";
    Polynom value("x^2 + y");
    tree.insert({ key, value });

    // Act
    tree.erase(key);

    // Assert
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.find(key), nullptr);
}

TEST(TestBinarySearchTreeLib, binary_search_tree_erase_nonexistent) {
    // Arrange
    BinarySearchTree<std::pair<std::string, Polynom>> tree;
    tree.insert({ "key1", Polynom("x + y") });

    // Act & Assert
    ASSERT_THROW(tree.erase("nonexistent"), std::invalid_argument);
}

TEST(TestBinarySearchTreeLib, binary_search_tree_find) {
    // Arrange
    BinarySearchTree<std::pair<std::string, Polynom>> tree;
    std::string key1 = "key1";
    Polynom p1 = "x + y";
    std::string key2 = "key2";
    Polynom p2 = "y";
    std::string key3 = "key3";
    Polynom p3 = "x^10 + z^2";
    tree.insert({ key1, p1 });
    tree.insert({ key2, p2 });
    tree.insert({ key3, p3 });

    // Act & Assert
    Polynom* found = tree.find(key3);
    ASSERT_NE(found, nullptr);
    expect_polynom_equal(*found, p3);
}

TEST(TestBinarySearchTreeLib, binary_search_tree_find_nonexistent) {
    // Arrange
    BinarySearchTree<std::pair<std::string, Polynom>> tree;
    std::string key = "key";
    Polynom p = "x + y + z";
    tree.insert({ key, p });

    // Act & Assert
    EXPECT_EQ(tree.find("nonexistent"), nullptr);
}

TEST(TestBinarySearchTreeLib, binary_search_tree_empty) {
    // Arrange
    BinarySearchTree<std::pair<std::string, Polynom>> tree;

    // Assert 
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.find("anything"), nullptr);
    ASSERT_THROW(tree.erase("anything"), std::invalid_argument);

    // Act 
    tree.insert({ "only", Polynom("x") });
    EXPECT_FALSE(tree.is_empty());

    tree.erase("only");

    // Assert 
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.find("only"), nullptr);
}

TEST(TestBinarySearchTreeLib, binary_search_tree_clear) {
    // Arrange
    BinarySearchTree<std::pair<std::string, Polynom>> tree;
    tree.insert({ "key1", Polynom("x + y") });
    tree.insert({ "key2", Polynom("x^2") });

    // Act
    tree.clear();

    // Assert
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(tree.find("key1"), nullptr);
    EXPECT_EQ(tree.find("key2"), nullptr);
}

TEST(TestBinarySearchTreeLib, simple_test) {
    BinarySearchTree<std::pair<std::string, int>> tree;
    tree.insert({ "a", 1 });

    int* found = tree.find("a");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(*found, 1);
}

TEST(TestBinarySearchTreeLib, binary_search_tree_insert_duplicate) {
    BinarySearchTree<std::pair<std::string, Polynom>> tree;
    std::string key = "polynom1";
    Polynom value1("x^2 + y");
    Polynom value2("x^3 + z");

    tree.insert({ key, value1 });
    ASSERT_THROW(tree.insert({ key, value2 }), std::invalid_argument);
}

TEST(TestBinarySearchTreeLib, binary_search_tree_insert_and_erase) {
    BinarySearchTree<std::pair<std::string, Polynom>> tree;
    std::string key1 = "polynom1";
    Polynom value1("x^2 + y");
    std::string key2 = "polynom2";
    Polynom value2("x + y");

    tree.insert({ key1, value1 });
    tree.insert({ key2, value2 });

    EXPECT_NE(tree.find(key1), nullptr);
    EXPECT_NE(tree.find(key2), nullptr);

    tree.erase(key2);
    tree.erase(key1);

    EXPECT_EQ(tree.find(key1), nullptr);
    EXPECT_EQ(tree.find(key2), nullptr);

    tree.insert({ key1, value1 });
    EXPECT_NE(tree.find(key1), nullptr);
}

TEST(TestBinarySearchTreeLib, binary_search_tree_complex_operations) {
    BinarySearchTree<std::pair<std::string, Polynom>> tree;

    tree.insert({ "50", Polynom("x^50") });
    tree.insert({ "30", Polynom("x^30") });
    tree.insert({ "70", Polynom("x^70") });
    tree.insert({ "20", Polynom("x^20") });
    tree.insert({ "40", Polynom("x^40") });
    tree.insert({ "60", Polynom("x^60") });
    tree.insert({ "80", Polynom("x^80") });

    // Проверяем, что все элементы на месте
    EXPECT_NE(tree.find("20"), nullptr);
    EXPECT_NE(tree.find("40"), nullptr);
    EXPECT_NE(tree.find("60"), nullptr);
    EXPECT_NE(tree.find("80"), nullptr);

    // Удаляем узел с двумя детьми (30)
    tree.erase("30");
    EXPECT_EQ(tree.find("30"), nullptr);

    // Удаляем корень (50)
    tree.erase("50");
    EXPECT_EQ(tree.find("50"), nullptr);

    EXPECT_NE(tree.find("20"), nullptr);
    EXPECT_NE(tree.find("40"), nullptr);
    EXPECT_NE(tree.find("60"), nullptr);
    EXPECT_NE(tree.find("70"), nullptr);
    EXPECT_NE(tree.find("80"), nullptr);
}

TEST(TestBinarySearchTreeLib, simple_test_int_multiple) {
    BinarySearchTree<std::pair<std::string, int>> tree;
    tree.insert({ "first", 100 });
    tree.insert({ "second", 200 });
    tree.insert({ "third", 300 });

    int* found = tree.find("second");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(*found, 200);

    tree.erase("second");
    EXPECT_EQ(tree.find("second"), nullptr);

    found = tree.find("first");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(*found, 100);

    found = tree.find("third");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(*found, 300);
}
