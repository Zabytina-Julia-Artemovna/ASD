// Copyright 2026 Julia Zabytina
#include <stdexcept>
#include <sstream>
#include <vector>
#include <gtest/gtest.h>
#include "../lib_avl_tree/avl_tree.h"
#include "../lib_polynom/polynom.h"

static void expect_polynom_equal(const Polynom& expected, const Polynom& actual) {
    std::stringstream ss_expected, ss_actual;
    ss_expected << expected;
    ss_actual << actual;
    EXPECT_EQ(ss_expected.str(), ss_actual.str());
}

TEST(TestAVLTree, default_constructor) {
    AVLTree<int, std::string> tree;
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestAVLTree, insert_and_find) {
    AVLTree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    EXPECT_FALSE(tree.is_empty());

    std::string* val = tree.find(5);
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("five", *val);

    val = tree.find(3);
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("three", *val);

    val = tree.find(7);
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("seven", *val);

    val = tree.find(10);
    EXPECT_EQ(nullptr, val);
}

TEST(TestAVLTree, insert_duplicate_throws) {
    AVLTree<int, std::string> tree;
    tree.insert(5, "five");
    EXPECT_THROW(tree.insert(5, "five again"), std::invalid_argument);
}

TEST(TestAVLTree, erase_leaf) {
    AVLTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    tree.erase(3);
    EXPECT_EQ(nullptr, tree.find(3));
    EXPECT_NE(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(7));
}

TEST(TestAVLTree, erase_one_child) {
    AVLTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(2, "two");

    tree.erase(3);
    EXPECT_EQ(nullptr, tree.find(3));
    EXPECT_NE(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(2));
}

TEST(TestAVLTree, erase_two_children) {
    AVLTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(1, "one");
    tree.insert(4, "four");

    tree.erase(3);
    EXPECT_EQ(nullptr, tree.find(3));
    EXPECT_NE(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(7));
    EXPECT_NE(nullptr, tree.find(1));
    EXPECT_NE(nullptr, tree.find(4));
}

TEST(TestAVLTree, erase_root) {
    AVLTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    tree.erase(5);
    EXPECT_EQ(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(3));
    EXPECT_NE(nullptr, tree.find(7));
}

TEST(TestAVLTree, erase_not_exists_throws) {
    AVLTree<int, std::string> tree;
    tree.insert(5, "five");
    EXPECT_THROW(tree.erase(10), std::invalid_argument);
}

TEST(TestAVLTree, clear) {
    AVLTree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(nullptr, tree.find(5));
}

TEST(TestAVLTree, copy_constructor) {
    AVLTree<int, std::string> tree1;
    tree1.insert(5, "five");
    tree1.insert(3, "three");

    AVLTree<int, std::string> tree2(tree1);

    EXPECT_NE(nullptr, tree2.find(5));
    EXPECT_NE(nullptr, tree2.find(3));

    tree1.erase(5);
    EXPECT_NE(nullptr, tree2.find(5));
}
TEST(TestAVLTree, with_polynoms) {
    AVLTree<std::string, Polynom> tree;

    Polynom p1("x^2 + y");
    Polynom p2("2x + y^2");
    Polynom p3("xyz");

    tree.insert("first", p1);
    tree.insert("second", p2);
    tree.insert("third", p3);

    Polynom* found = tree.find("first");
    ASSERT_NE(nullptr, found);
    expect_polynom_equal(p1, *found);

    found = tree.find("second");
    ASSERT_NE(nullptr, found);
    expect_polynom_equal(p2, *found);

    found = tree.find("third");
    ASSERT_NE(nullptr, found);
    expect_polynom_equal(p3, *found);
}
