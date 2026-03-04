// Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <gtest/gtest.h>
#include "../lib_unsorted_table_l/unsorted_table_l.h"
#include "../lib_polynom/polynom.h"
static void expect_polynom_equal(const Polynom& expected, const Polynom& actual) {
    std::stringstream ss_expected, ss_actual;
    ss_expected << expected;
    ss_actual << actual;
    EXPECT_EQ(ss_expected.str(), ss_actual.str());
}
TEST(TestUnsortedTableLLib, unsorted_table_l_default_constructor) {
    UnsortedTableL<std::string, Polynom> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size());
}
TEST(TestUnsortedTableLLib, unsorted_table_l_copy_constructor) {
    // Arrange
    std::string name1 = "p1";
    Polynom data1("x^2 + 2yz^7");
    std::string name2 = "p2";
    Polynom data2("x^2 + 2xz^10 + xy + yz");

    UnsortedTableL<std::string, Polynom> table1;
    table1.insert(name1, data1);
    table1.insert(name2, data2);

    UnsortedTableL<std::string, Polynom> table2(table1);

    
    EXPECT_EQ(table1.size(), table2.size());
    expect_polynom_equal(table1.find(name1), table2.find(name1));
    expect_polynom_equal(table1.find(name2), table2.find(name2));
}
TEST(TestUnsortedTableLLib, unsorted_table_l_operator_assign) {
    std::string name1 = "p1";
    Polynom data1("x^2 + 2yz^7");
    std::string name2 = "p2";
    Polynom data2("x^2 + 2xz^10 + xy + yz");

    UnsortedTableL<std::string, Polynom> table1;
    table1.insert(name1, data1);
    table1.insert(name2, data2);

     
    UnsortedTableL<std::string, Polynom> table2;
    table2 = table1;

    EXPECT_EQ(table1.size(), table2.size());
    expect_polynom_equal(table1.find(name1), table2.find(name1));
    expect_polynom_equal(table1.find(name2), table2.find(name2));
}
TEST(TestUnsortedTableLLib, unsorted_table_l_operator_assign_self_copy) {
    std::string name1 = "p1";
    Polynom data1("2.9yz^7 + x^8");
    std::string name2 = "p2";
    Polynom data2("x^2 + 2xz^10 + yz");

    UnsortedTableL<std::string, Polynom> table;
    table.insert(name1, data1);
    table.insert(name2, data2);
    EXPECT_NO_THROW(table = table);

    EXPECT_EQ(2, table.size());
    expect_polynom_equal(data1, table.find(name1));
    expect_polynom_equal(data2, table.find(name2));
}
TEST(TestUnsortedTableLLib, unsorted_table_l_insert) {
    UnsortedTableL<std::string, Polynom> table;

    table.insert("key1", Polynom("x + y"));
    EXPECT_EQ(1, table.size());
    EXPECT_FALSE(table.is_empty());

    table.insert("key2", Polynom("2x^2 + 3y"));
    EXPECT_EQ(2, table.size());

    table.insert("key3", Polynom("5xyz"));
    EXPECT_EQ(3, table.size());
}
TEST(TestUnsortedTableLLib, unsorted_table_l_insert_with_exception) {
    UnsortedTableL<std::string, Polynom> table;

    Polynom p("x + y");
    table.insert("key", p);
    EXPECT_EQ(1, table.size());

    EXPECT_THROW(table.insert("key", Polynom("2x^2 + 3y")), std::invalid_argument);
    EXPECT_EQ(1, table.size());  

    expect_polynom_equal(p, table.find("key"));
}
TEST(TestUnsortedTableLLib, unsorted_table_l_find) {
    UnsortedTableL<std::string, Polynom> table;

    Polynom p1("x^2 + 2yz^7");
    Polynom p2("x^2 + 2xz^10 + xy + yz");
    Polynom p3("5xyz");

    table.insert("poly1", p1);
    table.insert("poly2", p2);
    table.insert("poly3", p3);

    expect_polynom_equal(p1, table.find("poly1"));
    expect_polynom_equal(p2, table.find("poly2"));
    expect_polynom_equal(p3, table.find("poly3"));
}
TEST(TestUnsortedTableLLib, unsorted_table_l_find_with_exception) {
    UnsortedTableL<std::string, Polynom> table;

    table.insert("existing", Polynom("x + y"));

    EXPECT_THROW(table.find("non_existent"), std::out_of_range);
}
TEST(TestUnsortedTableLLib, unsorted_table_l_const_find) {
    UnsortedTableL<std::string, Polynom> table;
    Polynom p("x + y");
    table.insert("key", p);

    const auto& const_table = table;

    expect_polynom_equal(p, const_table.find("key"));
}
TEST(TestUnsortedTableLLib, unsorted_table_l_erase) {
    UnsortedTableL<std::string, Polynom> table;

    table.insert("key1", Polynom("x + y"));
    table.insert("key2", Polynom("x^2 + 2y"));
    table.insert("key3", Polynom("5xyz"));
    EXPECT_EQ(3, table.size());

    table.erase("key2");
    EXPECT_EQ(2, table.size());

    EXPECT_THROW(table.find("key2"), std::out_of_range);

    EXPECT_NO_THROW(table.find("key1"));
    EXPECT_NO_THROW(table.find("key3"));
}
TEST(TestUnsortedTableLLib, unsorted_table_l_erase_with_exception) {
    UnsortedTableL<std::string, Polynom> table;
    table.insert("key", Polynom("x + y"));

    EXPECT_THROW(table.erase("non_existent"), std::out_of_range);
    EXPECT_EQ(1, table.size()); 
}
TEST(TestUnsortedTableLLib, unsorted_table_l_deep_copy) {
    // Arrange
    Polynom original_value("x + y");
    UnsortedTableL<std::string, Polynom> table1;
    table1.insert("key", original_value);

    UnsortedTableL<std::string, Polynom> table2(table1);

    table2.find("key") = Polynom("x^2 + 2y");

    expect_polynom_equal(original_value, table1.find("key"));
    EXPECT_EQ(1, table1.size());
    EXPECT_EQ(1, table2.size());
}
TEST(TestUnsortedTableLLib, unsorted_table_l_various_polynoms) {
    UnsortedTableL<std::string, Polynom> table;

    Polynom p1("0");  
    Polynom p2("x");
    Polynom p3("y^2");
    Polynom p4("z^3");
    Polynom p5("xyz");
    Polynom p6("2x^2 + 3y^2 + 4z^2");

    table.insert("zero", p1);
    table.insert("x", p2);
    table.insert("y2", p3);
    table.insert("z3", p4);
    table.insert("xyz", p5);
    table.insert("quadratic", p6);

    EXPECT_EQ(6, table.size());

    expect_polynom_equal(p1, table.find("zero"));
    expect_polynom_equal(p2, table.find("x"));
    expect_polynom_equal(p3, table.find("y2"));
    expect_polynom_equal(p4, table.find("z3"));
    expect_polynom_equal(p5, table.find("xyz"));
    expect_polynom_equal(p6, table.find("quadratic"));
}
