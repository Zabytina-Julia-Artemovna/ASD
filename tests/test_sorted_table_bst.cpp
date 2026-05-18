// Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <sstream>
#include <gtest/gtest.h>
#include "../lib_sorted_table_bst/sorted_table_bst.h"
#include "../lib_polynom/polynom.h"

static void expect_polynom_equal(const Polynom& expected, const Polynom& actual) {
    std::stringstream ss_expected, ss_actual;
    ss_expected << expected;
    ss_actual << actual;
    EXPECT_EQ(ss_expected.str(), ss_actual.str());
}

TEST(TestSortedTableBSTLib, sorted_table_bst_default_constructor) {
    SortedTableBST<std::string, Polynom> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size());
}

TEST(TestSortedTableBSTLib, sorted_table_bst_copy_constructor) {
    std::string name1 = "p1";
    Polynom data1("x^2 + 2yz^7");
    std::string name2 = "p2";
    Polynom data2("x^2 + 2xz^10 + xy + yz");
    std::string name3 = "p3";
    Polynom data3("5xyz");

    SortedTableBST<std::string, Polynom> table1;
    table1.insert(name1, data1);
    table1.insert(name2, data2);
    table1.insert(name3, data3);

    SortedTableBST<std::string, Polynom> table2(table1);

    EXPECT_EQ(table1.size(), table2.size());
    expect_polynom_equal(table1.find(name1), table2.find(name1));
    expect_polynom_equal(table1.find(name2), table2.find(name2));
    expect_polynom_equal(table1.find(name3), table2.find(name3));
}

TEST(TestSortedTableBSTLib, sorted_table_bst_operator_assign_self_copy) {
    std::string name1 = "p1";
    Polynom data1("2.9yz^7 + x^8");
    std::string name2 = "p2";
    Polynom data2("x^2 + 2xz^10 + yz");

    SortedTableBST<std::string, Polynom> table;
    table.insert(name1, data1);
    table.insert(name2, data2);
    EXPECT_NO_THROW(table = table);

    EXPECT_EQ(2, table.size());
    expect_polynom_equal(data1, table.find(name1));
    expect_polynom_equal(data2, table.find(name2));
}

TEST(TestSortedTableBSTLib, sorted_table_bst_insert) {
    SortedTableBST<std::string, Polynom> table;

    table.insert("a", Polynom("2x"));
    table.insert("b", Polynom("x"));
    table.insert("c", Polynom("3x"));
    table.insert("d", Polynom("4x"));

    EXPECT_EQ(4, table.size());
    expect_polynom_equal(Polynom("2x"), table.find("a"));
    expect_polynom_equal(Polynom("x"), table.find("b"));
    expect_polynom_equal(Polynom("3x"), table.find("c"));
    expect_polynom_equal(Polynom("4x"), table.find("d"));
}

TEST(TestSortedTableBSTLib, sorted_table_bst_insert_with_exception) {
    SortedTableBST<std::string, Polynom> table;

    Polynom p("x + y");
    table.insert("key", p);
    EXPECT_EQ(1, table.size());

    EXPECT_THROW(table.insert("key", Polynom("2x^2 + 3y")), std::invalid_argument);
    EXPECT_EQ(1, table.size());
}

TEST(TestSortedTableBSTLib, sorted_table_bst_find) {
    SortedTableBST<std::string, Polynom> table;

    Polynom p1("x^2 + 2yz^7");
    Polynom p2("x^2 + 2xz^10 + xy + yz");
    Polynom p3("5xyz");

    table.insert("a", p1);
    table.insert("b", p2);
    table.insert("c", p3);

    expect_polynom_equal(p1, table.find("a"));
    expect_polynom_equal(p2, table.find("b"));
    expect_polynom_equal(p3, table.find("c"));
}

TEST(TestSortedTableBSTLib, sorted_table_bst_find_with_exception) {
    SortedTableBST<std::string, Polynom> table;

    table.insert("existing", Polynom("x + y"));

    EXPECT_THROW(table.find("non_existent"), std::invalid_argument);
}

TEST(TestSortedTableBSTLib, sorted_table_bst_const_find) {
    SortedTableBST<std::string, Polynom> table;
    Polynom p("x + y");
    table.insert("key", p);

    const auto& const_table = table;

    expect_polynom_equal(p, const_table.find("key"));
    EXPECT_THROW(const_table.find("non_existent"), std::invalid_argument);
}

TEST(TestSortedTableBSTLib, sorted_table_bst_erase) {
    SortedTableBST<std::string, Polynom> table;

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

TEST(TestSortedTableBSTLib, sorted_table_bst_erase_with_exception) {
    SortedTableBST<std::string, Polynom> table;
    table.insert("key", Polynom("x + y"));

    EXPECT_THROW(table.erase("non_existent"), std::invalid_argument);
    EXPECT_EQ(1, table.size());
}

TEST(TestSortedTableBSTLib, sorted_table_bst_is_empty) {
    SortedTableBST<std::string, Polynom> table;
    EXPECT_TRUE(table.is_empty());

    table.insert("key", Polynom("x + y"));
    EXPECT_FALSE(table.is_empty());

    table.erase("key");
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableBSTLib, sorted_table_bst_size) {
    SortedTableBST<std::string, Polynom> table;
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

TEST(TestSortedTableBSTLib, sorted_table_bst_various_polynoms) {
    SortedTableBST<std::string, Polynom> table;

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
TEST(TestSortedTableBSTLib, sorted_table_print) {
    SortedTableBST<std::string, Polynom> table;
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
    EXPECT_EQ(s.str(), "Sorted table on binary search tree\n\
  1 : x^3\n\
  4 : x^4\n\
  7 : x^2\n\
  8 : x^3\n\
  9 : x^2\n");
}
