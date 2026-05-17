// Copyright 2026 Julia Zabytina
#include <stdexcept>
#include <sstream>
#include <gtest/gtest.h>
#include "../lib_table_avl_tree/table_avl_tree.h"
#include "../lib_polynom/polynom.h"

static void expect_polynom_equal(const Polynom& expected, const Polynom& actual) {
    std::stringstream ss_expected, ss_actual;
    ss_expected << expected;
    ss_actual << actual;
    EXPECT_EQ(ss_expected.str(), ss_actual.str());
}

TEST(TestTableAVLTree, default_constructor) {
    TableAVLTree<std::string, Polynom> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size());
}

TEST(TestTableAVLTree, insert_and_find) {
    TableAVLTree<std::string, Polynom> table;

    Polynom p1("2x");
    Polynom p2("x");
    Polynom p3("3x");

    table.insert("a", p1);
    table.insert("b", p2);
    table.insert("c", p3);

    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(3, table.size());

    expect_polynom_equal(p1, table.find("a"));
    expect_polynom_equal(p2, table.find("b"));
    expect_polynom_equal(p3, table.find("c"));
}

TEST(TestTableAVLTree, insert_duplicate_throws) {
    TableAVLTree<std::string, Polynom> table;
    table.insert("key", Polynom("x + y"));
    EXPECT_EQ(1, table.size());

    EXPECT_THROW(table.insert("key", Polynom("2x")), std::invalid_argument);
    EXPECT_EQ(1, table.size());
}

TEST(TestTableAVLTree, find_not_exists_throws) {
    TableAVLTree<std::string, Polynom> table;
    table.insert("existing", Polynom("x + y"));

    EXPECT_THROW(table.find("non_existent"), std::invalid_argument);
}

TEST(TestTableAVLTree, const_find) {
    TableAVLTree<std::string, Polynom> table;
    Polynom p("x + y");
    table.insert("key", p);

    const auto& const_table = table;

    expect_polynom_equal(p, const_table.find("key"));
    EXPECT_THROW(const_table.find("non_existent"), std::invalid_argument);
}

TEST(TestTableAVLTree, erase) {
    TableAVLTree<std::string, Polynom> table;

    table.insert("a", Polynom("x + y"));
    table.insert("b", Polynom("x^2 + 2y"));
    table.insert("c", Polynom("5xyz"));
    EXPECT_EQ(3, table.size());

    table.erase("b");
    EXPECT_EQ(2, table.size());

    EXPECT_THROW(table.find("b"), std::invalid_argument);
    EXPECT_NO_THROW(table.find("a"));
    EXPECT_NO_THROW(table.find("c"));
}

TEST(TestTableAVLTree, erase_not_exists_throws) {
    TableAVLTree<std::string, Polynom> table;
    table.insert("key", Polynom("x + y"));

    EXPECT_THROW(table.erase("non_existent"), std::invalid_argument);
    EXPECT_EQ(1, table.size());
}

TEST(TestTableAVLTree, is_empty) {
    TableAVLTree<std::string, Polynom> table;
    EXPECT_TRUE(table.is_empty());

    table.insert("key", Polynom("x + y"));
    EXPECT_FALSE(table.is_empty());

    table.erase("key");
    EXPECT_TRUE(table.is_empty());
}

TEST(TestTableAVLTree, size) {
    TableAVLTree<std::string, Polynom> table;
    EXPECT_EQ(0, table.size());

    table.insert("a", Polynom("x"));
    EXPECT_EQ(1, table.size());

    table.insert("b", Polynom("y"));
    EXPECT_EQ(2, table.size());

    table.insert("c", Polynom("z"));
    EXPECT_EQ(3, table.size());

    table.erase("b");
    EXPECT_EQ(2, table.size());
}

TEST(TestTableAVLTree, copy_constructor) {
    TableAVLTree<std::string, Polynom> table1;
    table1.insert("a", Polynom("x^2"));
    table1.insert("b", Polynom("y^2"));

    TableAVLTree<std::string, Polynom> table2(table1);

    EXPECT_EQ(table1.size(), table2.size());
    expect_polynom_equal(table1.find("a"), table2.find("a"));
    expect_polynom_equal(table1.find("b"), table2.find("b"));
}

TEST(TestTableAVLTree, various_polynoms) {
    TableAVLTree<std::string, Polynom> table;

    Polynom p1("1.0");
    Polynom p2("x");
    Polynom p3("y^2");
    Polynom p4("z^3");
    Polynom p5("xyz");
    Polynom p6("2x^2 + 3y^2 + 4z^2");

    table.insert("number", p1);
    table.insert("x", p2);
    table.insert("y2", p3);
    table.insert("z3", p4);
    table.insert("xyz", p5);
    table.insert("quadratic", p6);

    EXPECT_EQ(6, table.size());

    expect_polynom_equal(p1, table.find("number"));
    expect_polynom_equal(p2, table.find("x"));
    expect_polynom_equal(p3, table.find("y2"));
    expect_polynom_equal(p4, table.find("z3"));
    expect_polynom_equal(p5, table.find("xyz"));
    expect_polynom_equal(p6, table.find("quadratic"));
}

TEST(TestTableAVLTree, print_format) {
    TableAVLTree<std::string, Polynom> table;
    table.insert("b", Polynom("x"));
    table.insert("a", Polynom("y"));

    std::stringstream ss;
    EXPECT_NO_THROW(table.print(ss));
    EXPECT_FALSE(ss.str().empty());
}
TEST(TestTableAVLTreeLib, table_avl_tree_print) {
    TableAVLTree<std::string, Polynom> table;
    Polynom p1("x^2");
    Polynom p2("x^3");
    Polynom p3("x^4");
    table.insert("7", p1);
    table.insert("1", p2);
    table.insert("4", p3);
    table.insert("9", p1);
    table.insert("8", p2);
    std::stringstream s;
    table.print(s);
    EXPECT_EQ(s.str(), "Sorted table on AVL tree\n\
  1 : x^3\n\
  4 : x^4\n\
  7 : x^2\n\
  8 : x^3\n\
  9 : x^2\n");
}
