// Copyright 2026 Julia Zabytina
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
#include "../lib_rbtree/rbtree.h"
#include "../lib_polynom/polynom.h"

static void expect_polynom_equal(const Polynom& expected, const Polynom& actual) {
    std::stringstream ss_expected, ss_actual;
    ss_expected << expected;
    ss_actual << actual;
    EXPECT_EQ(ss_expected.str(), ss_actual.str());
}

TEST(TestRBTree, default_constructor) {
    RBTree<std::pair<std::string, Polynom>> tree;
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestRBTree, insert_and_find) {
    RBTree<std::pair<std::string, Polynom>> tree;

    Polynom p1("x^2 + y");
    Polynom p2("2x + y^2");
    Polynom p3("xyz");

    tree.insert({ "five", p1 });
    tree.insert({ "three", p2 });
    tree.insert({ "seven", p3 });

    EXPECT_FALSE(tree.is_empty());

    Polynom* val = tree.find("five");
    ASSERT_NE(nullptr, val);
    expect_polynom_equal(p1, *val);

    val = tree.find("three");
    ASSERT_NE(nullptr, val);
    expect_polynom_equal(p2, *val);

    val = tree.find("seven");
    ASSERT_NE(nullptr, val);
    expect_polynom_equal(p3, *val);

    val = tree.find("ten");
    EXPECT_EQ(nullptr, val);
}

TEST(TestRBTree, insert_duplicate_throws) {
    RBTree<std::pair<std::string, Polynom>> tree;
    Polynom p("x^2 + y");
    tree.insert({ "key", p });
    EXPECT_THROW(tree.insert({ "key", p }), std::invalid_argument);
}

TEST(TestRBTree, erase_leaf) {
    RBTree<std::pair<std::string, Polynom>> tree;
    Polynom p1("x^2 + y");
    Polynom p2("2x + y^2");
    Polynom p3("xyz");

    tree.insert({ "five", p1 });
    tree.insert({ "three", p2 });
    tree.insert({ "seven", p3 });

    tree.erase("three");
    EXPECT_EQ(nullptr, tree.find("three"));
    EXPECT_NE(nullptr, tree.find("five"));
    EXPECT_NE(nullptr, tree.find("seven"));
}

TEST(TestRBTree, erase_one_child) {
    RBTree<std::pair<std::string, Polynom>> tree;
    Polynom p1("x^2 + y");
    Polynom p2("2x + y^2");
    Polynom p3("xyz");

    tree.insert({ "five", p1 });
    tree.insert({ "three", p2 });
    tree.insert({ "two", p3 });

    tree.erase("three");
    EXPECT_EQ(nullptr, tree.find("three"));
    EXPECT_NE(nullptr, tree.find("five"));
    EXPECT_NE(nullptr, tree.find("two"));
}

TEST(TestRBTree, erase_two_children) {
    RBTree<std::pair<std::string, Polynom>> tree;
    Polynom p1("x^2 + y");
    Polynom p2("2x + y^2");
    Polynom p3("xyz");
    Polynom p4("5x + 3y");
    Polynom p5("z^2");

    tree.insert({ "five", p1 });
    tree.insert({ "three", p2 });
    tree.insert({ "seven", p3 });
    tree.insert({ "one", p4 });
    tree.insert({ "four", p5 });

    tree.erase("three");
    EXPECT_EQ(nullptr, tree.find("three"));
    EXPECT_NE(nullptr, tree.find("five"));
    EXPECT_NE(nullptr, tree.find("seven"));
    EXPECT_NE(nullptr, tree.find("one"));
    EXPECT_NE(nullptr, tree.find("four"));
}

TEST(TestRBTree, erase_root) {
    RBTree<std::pair<std::string, Polynom>> tree;
    Polynom p1("x^2 + y");
    Polynom p2("2x + y^2");
    Polynom p3("xyz");

    tree.insert({ "five", p1 });
    tree.insert({ "three", p2 });
    tree.insert({ "seven", p3 });

    tree.erase("five");
    EXPECT_EQ(nullptr, tree.find("five"));
    EXPECT_NE(nullptr, tree.find("three"));
    EXPECT_NE(nullptr, tree.find("seven"));
}

TEST(TestRBTree, erase_not_exists_throws) {
    RBTree<std::pair<std::string, Polynom>> tree;
    Polynom p("x^2 + y");
    tree.insert({ "key", p });
    EXPECT_THROW(tree.erase("non_existent"), std::invalid_argument);
}

TEST(TestRBTree, clear) {
    RBTree<std::pair<std::string, Polynom>> tree;
    Polynom p1("x^2 + y");
    Polynom p2("2x + y^2");

    tree.insert({ "first", p1 });
    tree.insert({ "second", p2 });
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(nullptr, tree.find("first"));
}
TEST(TestRBTree, copy_constructor) {
    RBTree<std::pair<std::string, Polynom>> tree1;
    Polynom p1("x^2 + y");
    Polynom p2("2x + y^2");

    tree1.insert({ "first", p1 });
    tree1.insert({ "second", p2 });

    RBTree<std::pair<std::string, Polynom>> tree2(tree1);

    EXPECT_NE(nullptr, tree2.find("first"));
    EXPECT_NE(nullptr, tree2.find("second"));

    tree1.erase("first");
    EXPECT_NE(nullptr, tree2.find("first"));
}

TEST(TestRBTree, erase_after_clear) {
    RBTree<std::pair<std::string, Polynom>> tree;
    Polynom p("x^2 + y");
    tree.insert({ "key", p });
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
    tree.insert({ "new_key", p });
    EXPECT_NE(nullptr, tree.find("new_key"));
}

TEST(TestRBTree, various_polynoms) {
    RBTree<std::pair<std::string, Polynom>> tree;

    Polynom p1("1.0");
    Polynom p2("x");
    Polynom p3("y^2");
    Polynom p4("z^3");
    Polynom p5("xyz");
    Polynom p6("2x^2 + 3y^2 + 4z^2");

    tree.insert({ "number", p1 });
    tree.insert({ "x", p2 });
    tree.insert({ "y2", p3 });
    tree.insert({ "z3", p4 });
    tree.insert({ "xyz", p5 });
    tree.insert({ "quadratic", p6 });

    EXPECT_FALSE(tree.is_empty());

    expect_polynom_equal(p1, *tree.find("number"));
    expect_polynom_equal(p2, *tree.find("x"));
    expect_polynom_equal(p3, *tree.find("y2"));
    expect_polynom_equal(p4, *tree.find("z3"));
    expect_polynom_equal(p5, *tree.find("xyz"));
    expect_polynom_equal(p6, *tree.find("quadratic"));

    tree.erase("y2");
    EXPECT_EQ(nullptr, tree.find("y2"));

    EXPECT_NE(nullptr, tree.find("number"));
    EXPECT_NE(nullptr, tree.find("x"));
    EXPECT_NE(nullptr, tree.find("z3"));
    EXPECT_NE(nullptr, tree.find("xyz"));
    EXPECT_NE(nullptr, tree.find("quadratic"));
}

TEST(TestRBTree, erase_and_reinsert) {
    RBTree<std::pair<std::string, Polynom>> tree;
    Polynom p1("x^2 + y");
    Polynom p2("2x + y^2");

    tree.insert({ "test", p1 });
    EXPECT_NE(nullptr, tree.find("test"));
    expect_polynom_equal(p1, *tree.find("test"));

    tree.erase("test");
    EXPECT_EQ(nullptr, tree.find("test"));

    tree.insert({ "test", p2 });
    EXPECT_NE(nullptr, tree.find("test"));
    expect_polynom_equal(p2, *tree.find("test"));
}
TEST(TestRBTree, recolor_check) {
    RBTree<std::pair<int, std::string>> tree;

    // Дядя - красный
    tree.insert({ 50, "fifty" });      // корень чёрный
    tree.insert({ 30, "thirty" });     // левый красный
    tree.insert({ 70, "seventy" });    // правый красный
    tree.insert({ 20, "twenty" });     // должен вызвать перекрашивание

    EXPECT_NE(nullptr, tree.find(50));
    EXPECT_NE(nullptr, tree.find(30));
    EXPECT_NE(nullptr, tree.find(70));
    EXPECT_NE(nullptr, tree.find(20));

    std::string* val = tree.find(50);
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("fifty", *val);
}


//right_rotate - через LL ситуацию
TEST(TestRBTree, right_rotate_via_ll) {
    RBTree<std::pair<int, std::string>> tree;

    //  LL : 30, 20, 10
    //  правый поворот вокруг 30
    tree.insert({ 30, "thirty" });
    tree.insert({ 20, "twenty" });
    tree.insert({ 10, "ten" });

    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(30));

    // Проверяем значения
    std::string* val = tree.find(20);
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("twenty", *val);

    val = tree.find(10);
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("ten", *val);

    val = tree.find(30);
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("thirty", *val);
}

// left_rotate - через RR ситуацию
TEST(TestRBTree, left_rotate_via_rr) {
    RBTree<std::pair<int, std::string>> tree;

    // RR : 10, 20, 30
    // левый поворот вокруг 10
    tree.insert({ 10, "ten" });
    tree.insert({ 20, "twenty" });
    tree.insert({ 30, "thirty" });

    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(30));

    std::string* val = tree.find(20);
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("twenty", *val);
}

// большие тесты с полным деревом - на повороты и удаление
TEST(TestRBTree, large_tree_ll_rotations) {
    RBTree<std::pair<int, std::string>> tree;

    //в убывающем порядке - много LL поворотов
    for (int i = 100; i >= 1; --i) {
        tree.insert({ i, std::to_string(i) });
    }

    // Проверяем, что все элементы на месте
    for (int i = 1; i <= 100; ++i) {
        std::string* val = tree.find(i);
        ASSERT_NE(nullptr, val);
        EXPECT_EQ(std::to_string(i), *val);
    }
}

TEST(TestRBTree, large_tree_rr_rotations) {
    RBTree<std::pair<int, std::string>> tree;

    // в возрастающем порядке - много RR поворотов
    for (int i = 1; i <= 100; ++i) {
        tree.insert({ i, std::to_string(i) });
    }

    //проверяем что все элементы на месте
    for (int i = 1; i <= 100; ++i) {
        std::string* val = tree.find(i);
        ASSERT_NE(nullptr, val);
        EXPECT_EQ(std::to_string(i), *val);
    }
}

TEST(TestRBTree, large_tree_mixed_rotations) {
    RBTree<std::pair<int, std::string>> tree;

    // Случайная последовательность для смешанных поворотов
    std::vector<int> keys = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 85,
                              5, 15, 33, 37, 43, 47, 53, 57, 63, 67, 73, 77, 83, 87, 90 };

    for (int key : keys) {
        tree.insert({ key, std::to_string(key) });
    }

    // Проверяем, что все элементы на месте
    for (int key : keys) {
        std::string* val = tree.find(key);
        ASSERT_NE(nullptr, val);
        EXPECT_EQ(std::to_string(key), *val);
    }
}

TEST(TestRBTree, recolor_color_check) {
    RBTree<std::pair<int, std::string>> tree;

    tree.insert({ 100, "100" });   // корень чёрный
    tree.insert({ 50, "50" });     // левый красный
    tree.insert({ 150, "150" });   // правый красный
    tree.insert({ 25, "25" });     // вставка вызывает перекрашивание

    // Проверка корень чёрный
    EXPECT_TRUE(tree.is_black(100));

    // Проверка 50 стал чёрным (перекрасился)
    EXPECT_TRUE(tree.is_black(50));

    // Проверка 150 стал чёрным (перекрасился)
    EXPECT_TRUE(tree.is_black(150));

    // Проверка новый элемент 25 - красный
    EXPECT_TRUE(tree.is_red(25));
}
TEST(TestRBTree, recolor_large_tree_check) {
    RBTree<std::pair<int, std::string>> tree;

    tree.insert({ 40, "40" });
    tree.insert({ 20, "20" });
    tree.insert({ 60, "60" });
    tree.insert({ 15, "15" });
    tree.insert({ 25, "25" });
    tree.insert({ 50, "50" });
    tree.insert({ 70, "70" });
    tree.insert({ 5, "5" });
    tree.insert({ 45, "45" });
    tree.insert({ 55, "55" });
    tree.insert({ 65, "65" });
    tree.insert({ 80, "80" });
    tree.insert({ 75, "75" });

    // Добавляем элемент, который вызовет перекрашивание
    // 77 - создаст ситуацию с красным дядей (75 будет красным)
    tree.insert({ 77, "77" });

    // Проверяем, что все элементы на месте
    EXPECT_NE(nullptr, tree.find(40));
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(60));
    EXPECT_NE(nullptr, tree.find(15));
    EXPECT_NE(nullptr, tree.find(25));
    EXPECT_NE(nullptr, tree.find(50));
    EXPECT_NE(nullptr, tree.find(70));
    EXPECT_NE(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(45));
    EXPECT_NE(nullptr, tree.find(55));
    EXPECT_NE(nullptr, tree.find(65));
    EXPECT_NE(nullptr, tree.find(80));
    EXPECT_NE(nullptr, tree.find(75));
    EXPECT_NE(nullptr, tree.find(77));

    // Проверяем цвета (после перекрашивания)
    // Корень должен быть чёрным
    EXPECT_TRUE(tree.is_black(40));
}
