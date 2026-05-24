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
TEST(TestAVLTree, erase_with_double_rotation) {
    AVLTree<int, std::string> tree;
    tree.insert(40, "40");
    tree.insert(20, "20");
    tree.insert(60, "60");
    tree.insert(15, "15");
    tree.insert(25, "25");
    tree.insert(50, "50");
    tree.insert(70, "70");
    tree.insert(5, "5");
    tree.insert(45, "45");
    tree.insert(55, "55");
    tree.insert(65, "65");
    tree.insert(80, "80");
    tree.insert(75, "75");
    tree.erase(25);
    EXPECT_EQ(tree.get_root()->data_.first, 60);

}


TEST(TestAVLTree, insert_with_double_rotation_big_tree) {
    AVLTree<int, std::string> tree;

    // правое поддерево значительно тяжелее
    tree.insert(50, "50");
    tree.insert(30, "30");
    tree.insert(70, "70");
    tree.insert(20, "20");
    tree.insert(40, "40");
    tree.insert(60, "60");
    tree.insert(80, "80");
    tree.insert(10, "10");
    tree.insert(25, "25");
    tree.insert(35, "35");
    tree.insert(45, "45");
    tree.insert(55, "55");
    tree.insert(65, "65");
    tree.insert(75, "75");
    tree.insert(85, "85");
    tree.insert(5, "5");
    tree.insert(15, "15");
    tree.insert(33, "33");
    tree.insert(37, "37");
    tree.insert(43, "43");
    tree.insert(47, "47");
    tree.insert(53, "53");
    tree.insert(57, "57");
    tree.insert(63, "63");
    tree.insert(67, "67");
    tree.insert(73, "73");
    tree.insert(77, "77");
    tree.insert(83, "83");
    tree.insert(87, "87");

    //  RL поворот
    // Вставляем - дисбаланс
    tree.insert(72, "72"); //произойдет двойной поворот на уровне 70

     EXPECT_NE(nullptr, tree.find(72));

    // Проверяем, что остальные элементы на месте
    EXPECT_NE(nullptr, tree.find(50));
    EXPECT_NE(nullptr, tree.find(30));
    EXPECT_NE(nullptr, tree.find(70));
    EXPECT_NE(nullptr, tree.find(80));
    EXPECT_NE(nullptr, tree.find(75));
    //корень при вставках редко меняется, потому что даже в больших деревьях дисбаланс чаще возникает не в root 
    // а в более нижних узлах? и тут корень не изменился но повороты произошли
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
// Повороты

TEST(TestAVLTree, ll_rotation) {
    AVLTree<int, std::string> tree;

    // Последовательность: 30, 20, 10
    // Должен произойти правый поворот вокруг 30
    tree.insert(30, "thirty");
    tree.insert(20, "twenty");
    tree.insert(10, "ten");

    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(30));

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

TEST(TestAVLTree, rr_rotation) {
    AVLTree<int, std::string> tree;

    // Последовательность: 10, 20, 30
    // Должен произойти левый поворот вокруг 10
    tree.insert(10, "ten");
    tree.insert(20, "twenty");
    tree.insert(30, "thirty");

    // Проверяем, что дерево сбалансировано
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(30));

    std::string* val = tree.find(20);
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("twenty", *val);
}

TEST(TestAVLTree, lr_rotation) {
    AVLTree<int, std::string> tree;
    // Последовательность: 30, 10, 20
    // Должен произойти левый поворот вокруг 10, затем правый вокруг 30
    tree.insert(30, "thirty");
    tree.insert(10, "ten");
    tree.insert(20, "twenty");

    // Проверяем, что дерево сбалансировано
    // Ожидаемая структура: корень 20, левый 10, правый 30
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(30));

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

TEST(TestAVLTree, rl_rotation) {
    AVLTree<int, std::string> tree;

    // Последовательность: 10, 30, 20
    // Должен произойти правый поворот вокруг 30, затем левый вокруг 10
    tree.insert(10, "ten");
    tree.insert(30, "thirty");
    tree.insert(20, "twenty");

    // Проверяем, что дерево сбалансировано
    //  корень 20, левый 10, правый 30
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(30));

    std::string* val = tree.find(20);
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("twenty", *val);
}

TEST(TestAVLTree, multiple_rotations) {
    AVLTree<int, std::string> tree;

    tree.insert(50, "fifty");
    tree.insert(30, "thirty");
    tree.insert(70, "seventy");
    tree.insert(20, "twenty");
    tree.insert(40, "forty");
    tree.insert(60, "sixty");
    tree.insert(80, "eighty");
    tree.insert(10, "ten");
    tree.insert(25, "twenty_five");
    tree.insert(35, "thirty_five");
    tree.insert(45, "forty_five");
    tree.insert(55, "fifty_five");
    tree.insert(65, "sixty_five");
    tree.insert(75, "seventy_five");
    tree.insert(85, "eighty_five");

    //все элементы на месте
    EXPECT_NE(nullptr, tree.find(50));
    EXPECT_NE(nullptr, tree.find(30));
    EXPECT_NE(nullptr, tree.find(70));
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(40));
    EXPECT_NE(nullptr, tree.find(60));
    EXPECT_NE(nullptr, tree.find(80));
    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(25));
    EXPECT_NE(nullptr, tree.find(35));
    EXPECT_NE(nullptr, tree.find(45));
    EXPECT_NE(nullptr, tree.find(55));
    EXPECT_NE(nullptr, tree.find(65));
    EXPECT_NE(nullptr, tree.find(75));
    EXPECT_NE(nullptr, tree.find(85));

    // Проверяем некоторые значения
    std::string* val = tree.find(25);
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("twenty_five", *val);

    val = tree.find(55);
    ASSERT_NE(nullptr, val);
    EXPECT_EQ("fifty_five", *val);
}
