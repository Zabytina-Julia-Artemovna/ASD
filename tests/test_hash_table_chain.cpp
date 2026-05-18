// Copyright 2026 Julia Zabytina
#include <stdexcept>
#include <gtest/gtest.h>
#include "../lib_hash_table_chain/hash_table_chain.h"
#include "../lib_polynom/polynom.h"

static void expect_polynom_equal(const Polynom& expected, const Polynom& actual) {
    std::stringstream ss_expected, ss_actual;
    ss_expected << expected;
    ss_actual << actual;
    EXPECT_EQ(ss_expected.str(), ss_actual.str());
}
TEST(TestHashTableChainLib, hash_table_chain_default_constructor) {
    HashTableChain<Polynom> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size());
}

TEST(TestHashTableChainLib, hash_table_chain_constructor_with_size) {
    HashTableChain<Polynom> table(50);
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size());
}

TEST(TestHashTableChainLib, hash_table_chain_insert_single) {
    HashTableChain<Polynom> table;

    table.insert("p1", Polynom("x + y"));
    EXPECT_EQ(1, table.size());
    EXPECT_FALSE(table.is_empty());
}

TEST(TestHashTableChainLib, hash_table_chain_insert_multiple) {
    HashTableChain<Polynom> table;

    table.insert("p1", Polynom("x + y"));
    table.insert("p2", Polynom("x^2 + 2yz^7"));
    table.insert("p3", Polynom("3xyz"));

    EXPECT_EQ(3, table.size());
}
TEST(TestHashTableChainLib, hash_table_chain_insert_with_exception) {
    HashTableChain<Polynom> table;

    table.insert("key", Polynom("x + y"));
    EXPECT_EQ(1, table.size());

    EXPECT_THROW(table.insert("key", Polynom("new value")), std::logic_error);
    EXPECT_EQ(1, table.size()); 
}

TEST(TestHashTableChainLib, hash_table_chain_find) {
    HashTableChain<Polynom> table;

    Polynom p1("x^2 + 2.9yz^7");
    Polynom p2("x^2 + 2xz^11 + xz + yz");
    Polynom p3("9xyz");

    table.insert("poly1", p1);
    table.insert("poly2", p2);
    table.insert("poly3", p3);

    expect_polynom_equal(p1, table.find("poly1"));
    expect_polynom_equal(p2, table.find("poly2"));
    expect_polynom_equal(p3, table.find("poly3"));
}

TEST(TestHashTableChainLib, hash_table_chain_find_with_exception) {
    HashTableChain<Polynom> table;

    table.insert("existing", Polynom("x + y"));

    EXPECT_THROW(table.find("non_existent"), std::logic_error);
}
TEST(TestHashTableChainLib, hash_table_chain_erase_existing) {
    HashTableChain<Polynom> table;

    table.insert("key1", Polynom("x + z"));
    table.insert("key2", Polynom("x^2 + 3.8y"));
    table.insert("key3", Polynom("7xyz"));

    EXPECT_EQ(3, table.size());

    table.erase("key2");

    EXPECT_EQ(2, table.size());
    EXPECT_THROW(table.find("key2"), std::logic_error);
    EXPECT_NO_THROW(table.find("key1"));
    EXPECT_NO_THROW(table.find("key3"));
}

TEST(TestHashTableChainLib, hash_table_chain_erase_first_element) {
    HashTableChain<Polynom> table;

    table.insert("first", Polynom("x"));
    table.insert("second", Polynom("y"));
    table.insert("third", Polynom("z"));

    table.erase("first");

    EXPECT_EQ(2, table.size());
    EXPECT_THROW(table.find("first"), std::logic_error);
    EXPECT_NO_THROW(table.find("second"));
    EXPECT_NO_THROW(table.find("third"));
}

TEST(TestHashTableChainLib, hash_table_chain_erase_last_element) {
    HashTableChain<Polynom> table;

    table.insert("first", Polynom("x"));
    table.insert("second", Polynom("y"));
    table.insert("third", Polynom("z"));

    table.erase("third");

    EXPECT_EQ(2, table.size());
    EXPECT_NO_THROW(table.find("first"));
    EXPECT_NO_THROW(table.find("second"));
    EXPECT_THROW(table.find("third"), std::logic_error);
}

TEST(TestHashTableChainLib, hash_table_chain_erase_middle_element) {
    HashTableChain<Polynom> table;

    table.insert("first", Polynom("x"));
    table.insert("middle", Polynom("y"));
    table.insert("last", Polynom("z"));

    table.erase("middle");

    EXPECT_EQ(2, table.size());
    EXPECT_NO_THROW(table.find("first"));
    EXPECT_THROW(table.find("middle"), std::logic_error);
    EXPECT_NO_THROW(table.find("last"));
}

TEST(TestHashTableChainLib, hash_table_chain_erase_with_exception) {
    HashTableChain<Polynom> table;

    table.insert("key", Polynom("z + y"));

    EXPECT_THROW(table.erase("non_existent"), std::logic_error);
    EXPECT_EQ(1, table.size());
}

TEST(TestHashTableChainLib, hash_table_chain_erase_all_elements) {
    HashTableChain<Polynom> table;

    table.insert("a", Polynom("1"));
    table.insert("b", Polynom("2"));
    table.insert("c", Polynom("3"));

    EXPECT_EQ(3, table.size());

    table.erase("a");
    table.erase("b");
    table.erase("c");

    EXPECT_EQ(0, table.size());
    EXPECT_TRUE(table.is_empty());

    EXPECT_THROW(table.find("a"), std::logic_error);
    EXPECT_THROW(table.find("b"), std::logic_error);
    EXPECT_THROW(table.find("c"), std::logic_error);
}
TEST(TestHashTableChainLib, hash_table_chain_with_different_polynoms) {
    HashTableChain<Polynom> table;

    Polynom p1("0");
    Polynom p2("z");
    Polynom p3("y^3");
    Polynom p4("z^5");
    Polynom p5("xyz");
    Polynom p6("3.9x^2 + 3.1y^2 + 4.1z^3");

    table.insert("zero", p1);
    table.insert("z", p2);
    table.insert("y3", p3);
    table.insert("z5", p4);
    table.insert("xyz", p5);
    table.insert("quadratic", p6);

    EXPECT_EQ(6, table.size());

    expect_polynom_equal(p1, table.find("zero"));
    expect_polynom_equal(p2, table.find("z"));
    expect_polynom_equal(p3, table.find("y3"));
    expect_polynom_equal(p4, table.find("z5"));
    expect_polynom_equal(p5, table.find("xyz"));
    expect_polynom_equal(p6, table.find("quadratic"));
}

TEST(TestHashTableChainLib, hash_table_chain__empty_table) {
    HashTableChain<Polynom> table;

    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size());
    EXPECT_THROW(table.find("anything"), std::logic_error);
    EXPECT_THROW(table.erase("anything"), std::logic_error);
}
TEST(TestHashTableChainLib, hash_table_collision) {
    HashTableChain<Polynom> table;
    Polynom p1("x + y");
    Polynom p2("x^2 + y"); 
    Polynom p3("x^3 + y");
    table.insert("abc",p1);
    table.insert("acb", p2);
    table.insert("cba", p3);

    expect_polynom_equal(table.find("abc"), p1);
    expect_polynom_equal(table.find("acb"), p2);

    expect_polynom_equal(table.find("cba"), p3);
    table.erase("acb");

    expect_polynom_equal(table.find("abc"), p1);
    EXPECT_THROW(table.find("acb"), std::logic_error);

    expect_polynom_equal(table.find("cba"), p3);

  /*  EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size());
    EXPECT_THROW(table.find("anything"), std::logic_error);
    EXPECT_THROW(table.erase("anything"), std::logic_error);*/
}