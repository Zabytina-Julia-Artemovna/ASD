// Copyright 2025 Julia Zabytina
#include <gtest/gtest.h>
#include "../lib_vector/vector.h"
TEST(TestVectorLib, vector_default_constructor) {
    // Arrange & Act
    Tvector<int> vector;
    // Assert
    EXPECT_TRUE(vector.is_empty());
}
TEST(TestVectorLib, vector_constructor_with_size) {
    // Arrange & Act
    size_t size = 10;
    Tvector<int> vector(size);
    // Assert
    EXPECT_LE(vector.get_size(), vector.get_capacity());
    EXPECT_EQ(vector.get_size(), size);
}
TEST(TestVectorLib, vector_constructor_with_array_and_size) {
    // Arrange & Act
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    // Assert
    EXPECT_EQ(vector.get_size(), size);
    EXPECT_EQ(vector[0], data[0]);
    EXPECT_EQ(vector[1], data[1]);
    EXPECT_EQ(vector[2], data[2]);
    EXPECT_LE(vector.get_size(), vector.get_capacity());
}
TEST(TestVectorLib, vector_copy_constructor) {
    // Arrange & Act
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> old_vector(data, size);
    Tvector<int> new_vector(old_vector);
    // Assert
    EXPECT_EQ(old_vector, new_vector);
}
TEST(TestVectorLib, is_empty) {
    // Arrange
    Tvector<int> vector;
    // Act
    bool actual_result = vector.is_empty();
    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, get_data) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    int* data_ptr = data;
    bool different_pointers = data_ptr != vector.get_data();
    bool same_data =
        data[0] == vector.get_data()[0]
        && data[1] == vector.get_data()[1]
        && data[2] == vector.get_data()[2];
    // Act
    bool actual_result = different_pointers && same_data;
    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, front) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    // Act
    int actual_result = vector.front();
    // Assert
    int expected_result = vector.get_data()[0];
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, back) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    // Act
    int actual_result = vector.back();
    // Assert
    int expected_result = vector.get_data()[vector.get_size() - 1];
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, get_size) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    // Act
    size_t actual_result = vector.get_size();
    // Assert
    size_t expected_result = size;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, get_deleted) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    size_t deleted = 0;
    Tvector<int> vector(data, size);
    // Act
    size_t actual_result = vector.get_deleted();
    // Assert
    size_t expected_result = deleted;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, get_capacity) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    size_t capacity = 18;
    Tvector<int> vector(data, size);
    // Act
    size_t actual_result = vector.get_capacity();
    // Assert
    size_t expected_result = capacity;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, comparison_operator_true) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector1(data, size);
    Tvector<int> vector2(data, size);
    // Act
    bool actual_result = vector1 == vector2;
    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, comparison_operator_false) {
    // Arrange
    int data1[3] = { 1,2,3 };
    size_t size1 = 3;
    int data2[4] = { 1,2,3,4 };
    size_t size2 = 4;
    Tvector<int> vector1(data1, size1);
    Tvector<int> vector2(data2, size2);
    // Act
    bool actual_result = vector1 == vector2;
    // Assert
    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, not_comparison_operator_true) {
    // Arrange
    int data1[3] = { 1,2,3 };
    size_t size1 = 3;
    int data2[4] = { 1,2,3,4 };
    size_t size2 = 4;
    Tvector<int> vector1(data1, size1);
    Tvector<int> vector2(data2, size2);
    // Act
    bool actual_result = vector1 != vector2;
    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, not_comparison_operator_false) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector1(data, size);
    Tvector<int> vector2(data, size);
    // Act
    bool actual_result = vector1 != vector2;
    // Assert
    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, operator_assign) {
    // Arrange
    int data1[3] = { 1,2,3 };
    size_t size1 = 3;
    int data2[4] = { 1,2,3,4 };
    size_t size2 = 4;
    Tvector<int> vector1(data1, size1);
    Tvector<int> vector2(data2, size2);
    vector1 = vector2;
    // Act
    bool actual_result = vector1 == vector2;
    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, operator_staples) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    // Act
    int actual_result = vector[1];
    // Assert
    int expected_result = data[1];
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, at) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    // Act
    int actual_result = vector.at(1);
    // Assert
    int expected_result = data[1];
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, assign) {
    // Arrange
    int data[3] = { 1,1,1 };
    size_t size = 3;
    Tvector<int> vector1;
    Tvector<int> vector2(data, size);
    vector1.assign(vector2);
    // Act
    Tvector<int> actual_result = vector1;
    // Assert
    Tvector<int> expected_result = vector2;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, clear) {
    // Arrange
    int data[3] = { 1, 2, 3 };
    Tvector<int> vector(data, 3);

    // Act
    vector.clear();

    // Assert
    EXPECT_EQ(0, vector.get_size());
    EXPECT_EQ(0, vector.get_deleted());
}
TEST(TestVectorLib, emplace) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    vector.emplace(2, 100);
    // Act
    int actual_result = vector[2];
    // Assert
    int expected_result = 100;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, push_front1) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    vector.push_front(200);
    // Act
    int actual_result = vector[0];
    // Assert
    int expected_result = 200;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, push_front2) {
    // Arrange
    int data[1] = { 1 };
    size_t size = 1;
    Tvector<int> vector(data, size);
    for (size_t i = 1; i < 17; ++i) {
        vector.push_front(1);
    }
    // Act
    bool actual_result = vector.get_capacity() == 31
        && vector.get_size() == 17;
    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, insert1) {
    // Arrange
    int data[6] = { 1, 2, 3, 4, 5, 6 };
    size_t size = 6;
    Tvector<int> vector(data, size);
    vector.insert(225, 5);
    // Act
    int actual_result = vector[5];
    // Assert
    int expected_result = 225;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, insert2) {
    // Arrange
    size_t size = 10;
    Tvector<int> vector(size);
    vector.insert(225, 5);
    // Act
    int actual_result = vector[5];
    // Assert
    int expected_result = 225;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, insert3) {
    // Arrange
    Tvector<int> vector;
    vector.insert(225, 5);
    // Act
    int actual_result = vector[5];
    // Assert
    int expected_result = 225;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, insert4) {
    // Arrange
    bool actual_result = true;
    int data[5] = { 1, 2, 3, 4, 5 };
    size_t size = 5;
    Tvector<int> vector(data, size);
    try {
        vector.insert(225, 5);
    }
    catch (...) {
        actual_result = false;
    }
    // Assert
    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, push_back1) {
    // Arrange
    int data[1] = { 1 };
    size_t size = 1;
    Tvector<int> vector(data, size);
    for (size_t i = 1; i < 17; ++i) {
        vector.push_back(400);
    }
    // Act
    int actual_result = vector[5];
    // Assert
    int expected_result = 400;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, push_back2) {
    // Arrange
    int data[3] = { 1, 2, 3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    vector.push_back(9);
    // Act
    int actual_result = vector[3];
    // Assert
    int expected_result = 9;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, pop_back1) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    vector.pop_back();
    // Act
    bool actual_result = vector.get_size() == 2
        && vector[0] == 1
        && vector[1] == 2;
    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, pop_back2) {
    // Arrange
    bool actual_result = true;
    Tvector<int> vector;
    try {
        vector.pop_back();
    }
    catch (...) {
        actual_result = false;
    }
    // Assert
    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, erase1) {
    // Arrange
    int data[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    size_t size = 15;
    Tvector<int> vector(data, size);
    vector.erase(1);
    vector.erase(1);
    // Act
    size_t actual_result = vector.get_deleted();
    // Assert
    size_t expected_result = 2;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, erase2) {
    // Arrange
    bool actual_result = true;
    int data[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    size_t size = 15;
    Tvector<int> vector(data, size);
    try {
        vector.erase(20);
    }
    catch (...) {
        actual_result = false;
    }
    // Assert
    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, pop_front1) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    vector.pop_front();
    // Act
    bool actual_result = vector.get_size() == 2
        && vector[0] == 2
        && vector[1] == 3;
    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, pop_front2) {
    // Arrange
    bool actual_result = true;
    Tvector<int> vector;
    try {
        vector.pop_front();
    }
    catch (...) {
        actual_result = false;
    }
    // Assert
    bool expected_result = false;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, sort_of_shell) {
    // Arrange
    int data[10] = { 1223343, 1546, 8777, 1000, 2, 3, 7, 9, 888, 99 };
    size_t size = 10;
    Tvector<int> vector(data, size);
    int sorted_data[10] = { 2, 3, 7, 9, 99, 888, 1000, 1546, 8777, 1223343 };
    Tvector<int> sorted_vector(sorted_data, size);
    shell_sort(vector);
    // Act
    Tvector<int> actual_result = vector;
    // Assert
    Tvector<int> expected_result = sorted_vector;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, find_first) {
    // Arrange
    int data[6] = { 1 ,3, 3, 4, 5, 3 };
    size_t size = 6;
    Tvector<int> vector(data, size);
    // Act
    size_t actual_result = find_first_element(vector, 3);
    // Assert
    size_t expected_result = 2;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, find_last) {
    // Arrange
    int data[6] = { 1 ,3, 3, 4, 5, 3 };
    size_t size = 6;
    Tvector<int> vector(data, size);
    // Act
    size_t actual_result = find_last_element(vector, 3);
    // Assert
    size_t expected_result = 6;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, find_count_of_suitable_elements) {
    // Arrange
    int data[8] = { 1 ,3, 3, 4, 5, 3, 3, 7 };
    size_t size = 8;
    Tvector<int> vector(data, size);
    // Act
    size_t actual_result = find_count_of_all_suitable_elements(vector, 3);
    // Assert
    size_t expected_result = 4;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, vector_iterator_read) {
    // Arrange
    Tvector<int> vector;
    vector.push_back(3);
    vector.push_back(400);
    vector.push_back(109);
    vector.push_back(1);
    vector.push_back(2);
    // Act 
    auto it = vector.begin();
    it += 3;
    // Assert
    EXPECT_EQ(1, *it);
}
TEST(TestVectorLib, vector_iterator_write) {
    // Arrange
    Tvector<int> vector;
    vector.push_back(1);
    vector.push_back(34);
    vector.push_back(17);
    vector.push_back(12);
    vector.push_back(3);
    // Act 
    auto it = vector.begin();
    it += 3;
    // Assert
    EXPECT_EQ(12, *it);
    *it = 900;
    EXPECT_EQ(900, *it);
}
TEST(TestVectorLib, vector_iterator_empty_list) {
    // Arrange
    Tvector<int> vector;
    // Act & Assert
    EXPECT_EQ(vector.begin(), vector.end());

    auto it = vector.begin();
    ++it;
    EXPECT_EQ(it, vector.end());

    auto end_it = vector.end();
    ++end_it;
    EXPECT_EQ(end_it, vector.end());

    auto it2 = vector.begin();
    it2 += 7;
    EXPECT_EQ(it2, vector.end());
}
TEST(TestVectorLib, vector_iterator_prefix_increment) {
    Tvector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(30);

    auto it = vector.begin();
    ++it;
    EXPECT_EQ(20, *it);
    ++it;
    EXPECT_EQ(30, *it);
}

TEST(TestVectorLib, vector_iterator_postfix_increment) {
    Tvector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(30);

    auto it = vector.begin();
    auto it_copy = it++;

    EXPECT_EQ(10, *it_copy);
    EXPECT_EQ(20, *it);
}

TEST(TestVectorLib, vector_iterator_prefix_decrement) {
    Tvector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(30);

    auto it = vector.begin();
    ++it;
    ++it;
    --it;

    EXPECT_EQ(20, *it);
}

TEST(TestVectorLib, vector_iterator_postfix_decrement) {
    Tvector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(30);

    auto it = vector.begin();
    ++it;
    ++it;
    auto it_copy = it--;

    EXPECT_EQ(30, *it_copy);
    EXPECT_EQ(20, *it);
}

TEST(TestVectorLib, vector_iterator_compound_addition) {
    Tvector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(30);
    vector.push_back(40);
    vector.push_back(50);

    auto it = vector.begin();
    it += 3;
    EXPECT_EQ(40, *it);

    it += 1;
    EXPECT_EQ(50, *it);
}

TEST(TestVectorLib, vector_iterator_compound_subtraction) {
    Tvector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(30);
    vector.push_back(40);
    vector.push_back(50);

    auto it = vector.begin();
    it += 4;
    it -= 2;

    EXPECT_EQ(30, *it);

    it -= 2;
    EXPECT_EQ(10, *it);
}

TEST(TestVectorLib, vector_iterator_equality_operators) {
    Tvector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(30);

    auto it1 = vector.begin();
    auto it2 = vector.begin();
    EXPECT_TRUE(it1 == it2);

    ++it1;
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}

TEST(TestVectorLib, vector_iterator_dereference) {
    Tvector<int> vector;
    vector.push_back(100);
    vector.push_back(200);

    auto it = vector.begin();
    EXPECT_EQ(100, *it);

    ++it;
    EXPECT_EQ(200, *it);
}

TEST(TestVectorLib, vector_iterator_dereference_const) {
    Tvector<int> vector;
    vector.push_back(100);
    vector.push_back(200);

    const Tvector<int>& const_vector = vector;
    auto it = const_vector.begin();

    EXPECT_EQ(100, *it);
    ++it;
    EXPECT_EQ(200, *it);
}

TEST(TestVectorLib, vector_iterator_dereference_modify) {
    Tvector<int> vector;
    vector.push_back(100);
    vector.push_back(200);

    auto it = vector.begin();
    *it = 500;

    EXPECT_EQ(500, vector[0]);
}

TEST(TestVectorLib, vector_iterator_copy_constructor) {
    Tvector<int> vector;
    vector.push_back(100);
    vector.push_back(200);

    auto it1 = vector.begin();
    auto it2 = it1;

    EXPECT_TRUE(it1 == it2);
    EXPECT_EQ(100, *it1);
    EXPECT_EQ(100, *it2);

    ++it1;
    EXPECT_FALSE(it1 == it2);
    EXPECT_EQ(200, *it1);
    EXPECT_EQ(100, *it2);
}

TEST(TestVectorLib, vector_iterator_assignment_operator) {
    Tvector<int> vector;
    vector.push_back(100);
    vector.push_back(200);
    vector.push_back(300);

    auto it1 = vector.begin();
    auto it2 = vector.begin();
    ++it2;
    ++it2;

    it1 = it2;

    EXPECT_TRUE(it1 == it2);
    EXPECT_EQ(300, *it1);
    EXPECT_EQ(300, *it2);
}

TEST(TestVectorLib, vector_iterator_default_constructor) {
    Tvector<int>::Iterator it;

    Tvector<int> vector;
    vector.push_back(10);

    auto it2 = vector.begin();
    it = it2;

    EXPECT_EQ(10, *it);
}
TEST(TestVectorLib, vector_iterator_dereference_nullptr_exception) {
    Tvector<int>::Iterator it;
    EXPECT_THROW(*it, std::runtime_error);
}

TEST(TestVectorLib, vector_iterator_range_based_for_loop) {
    Tvector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    vector.push_back(4);
    vector.push_back(5);

    int sum = 0;
    for (const auto& value : vector) {
        sum += value;
    }

    EXPECT_EQ(15, sum);
}

TEST(TestVectorLib, vector_iterator_range_based_for_loop_modify) {
    Tvector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);

    for (auto& value : vector) {
        value *= 2;
    }

    auto it = vector.begin();
    EXPECT_EQ(2, *it);
    ++it;
    EXPECT_EQ(4, *it);
    ++it;
    EXPECT_EQ(6, *it);
}

TEST(TestVectorLib, vector_iterator_manual_for_loop) {
    Tvector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(30);
    vector.push_back(40);

    std::vector<int> values;
    for (auto it = vector.begin(); it != vector.end(); ++it) {
        values.push_back(*it);
    }

    ASSERT_EQ(4, values.size());
    EXPECT_EQ(10, values[0]);
    EXPECT_EQ(20, values[1]);
    EXPECT_EQ(30, values[2]);
    EXPECT_EQ(40, values[3]);
}

TEST(TestVectorLib, vector_iterator_begin_end_empty) {
    Tvector<int> vector;

    EXPECT_EQ(vector.begin(), vector.end());

    auto it = vector.begin();
    ++it;
    EXPECT_EQ(it, vector.end());
}

TEST(TestVectorLib, vector_iterator_begin_end_non_empty) {
    Tvector<int> vector;
    vector.push_back(10);
    vector.push_back(20);

    auto begin = vector.begin();
    auto end = vector.end();

    EXPECT_NE(begin, end);

    auto it = begin;
    ++it;
    ++it;
    EXPECT_EQ(it, end);
}

TEST(TestVectorLib, vector_iterator_reverse_iteration) {
    Tvector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    vector.push_back(4);
    vector.push_back(5);

    std::vector<int> reversed;

    auto it = vector.end();
    --it;

    while (true) {
        reversed.push_back(*it);
        if (it == vector.begin()) {
            break;
        }
        --it;
    }

    ASSERT_EQ(5, reversed.size());
    EXPECT_EQ(5, reversed[0]);
    EXPECT_EQ(4, reversed[1]);
    EXPECT_EQ(3, reversed[2]);
    EXPECT_EQ(2, reversed[3]);
    EXPECT_EQ(1, reversed[4]);
}

TEST(TestVectorLib, vector_iterator_arithmetic_mixed) {
    Tvector<int> vector;
    for (int i = 0; i < 10; ++i) {
        vector.push_back(i * 10);
    }

    auto it = vector.begin();
    it += 5;
    EXPECT_EQ(50, *it);

    --it;
    EXPECT_EQ(40, *it);

    it -= 2;
    EXPECT_EQ(20, *it);

    it++;
    EXPECT_EQ(30, *it);

    ++it;
    EXPECT_EQ(40, *it);
}

TEST(TestVectorLib, vector_iterator_self_assignment) {
    Tvector<int> vector;
    vector.push_back(100);
    vector.push_back(200);

    auto it = vector.begin();
    it = it;  

    EXPECT_EQ(100, *it);
}

TEST(TestVectorLib, vector_iterator_comparison_with_different_vectors) {
    Tvector<int> vector1;
    vector1.push_back(10);

    Tvector<int> vector2;
    vector2.push_back(10);

    auto it1 = vector1.begin();
    auto it2 = vector2.begin();

  
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}
