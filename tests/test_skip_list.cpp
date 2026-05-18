// Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <gtest/gtest.h>
#include "../lib_skip_list/skip_list.h"
#include "../lib_polynom/polynom.h"

static void expect_polynom_equal(const Polynom& expected, const Polynom& actual) {
    std::stringstream ss_expected, ss_actual;
    ss_expected << expected;
    ss_actual << actual;
    EXPECT_EQ(ss_expected.str(), ss_actual.str());
}
TEST(TestSkipListLib, skip_list_constructor_default) {
    SkipList<int, Polynom> list;
    EXPECT_THROW(list.find(1), std::runtime_error);
}

TEST(TestSkipListLib, skip_list_constructor_with_max_levels) {
    size_t max_levels = 8;
    SkipList<int, Polynom> list(max_levels);

    Polynom p("x + y");
    list.insert(5, p);
    expect_polynom_equal(p, list.find(5));
}

TEST(TestSkipListLib, skip_list_insert_single_element) {
    SkipList<int, Polynom> list;
    Polynom p("x^2 + 2yz^7");

    list.insert(5, p);
    expect_polynom_equal(p, list.find(5));
}

TEST(TestSkipListLib, skip_list_insert_multiple_elements) {
    SkipList<int, Polynom> list;

    Polynom p1("x^2 + 2yz^7");
    Polynom p2("x^2 + 2xz^10 + xy + yz");
    Polynom p3("9xyz");
    Polynom p4("0");

    list.insert(5, p1);
    list.insert(3, p2);
    list.insert(7, p3);
    list.insert(1, p4);

    expect_polynom_equal(p1, list.find(5));
    expect_polynom_equal(p2, list.find(3));
    expect_polynom_equal(p3, list.find(7));
    expect_polynom_equal(p4, list.find(1));
}

TEST(TestSkipListLib, skip_list_insert_update_existing_key) {
    SkipList<int, Polynom> list;

    Polynom p1("x + y");
    Polynom p2("x^2 + 2y");

    list.insert(5, p1);
    expect_polynom_equal(p1, list.find(5));

    list.insert(5, p2);
    expect_polynom_equal(p2, list.find(5));
}
TEST(TestSkipListLib, skip_list_find_existing_key) {
    SkipList<int, Polynom> list;

    Polynom p1("x + y");
    Polynom p2("x^2 + 2y");
    Polynom p3("9xyz");

    list.insert(5, p1);
    list.insert(3, p2);
    list.insert(7, p3);

    expect_polynom_equal(p1, list.find(5));
    expect_polynom_equal(p2, list.find(3));
    expect_polynom_equal(p3, list.find(7));
    list.print();
}

TEST(TestSkipListLib, skip_list_find_non_existing_key) {
    SkipList<int, Polynom> list;

    list.insert(5, Polynom("x + y"));
    list.insert(3, Polynom("x^2 + 2y"));

    EXPECT_THROW(list.find(10), std::runtime_error);
    EXPECT_THROW(list.find(0), std::runtime_error);
}

TEST(TestSkipListLib, skip_list_find_in_empty_list) {
    SkipList<int, Polynom> list;
    EXPECT_THROW(list.find(5), std::runtime_error);
}
