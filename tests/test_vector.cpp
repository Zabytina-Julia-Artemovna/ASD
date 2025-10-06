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
TEST(TestVectorLib, get_begin) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    // Act
    int* actual_result = vector.begin();
    // Assert
    int* expected_result = &(vector.get_data()[0]);
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, get_end) {
    // Arrange
    int data[3] = { 1,2,3 };
    size_t size = 3;
    Tvector<int> vector(data, size);
    // Act
    int* actual_result = vector.end();
    // Assert
    int* expected_result = &(vector.get_data()[0]) + size;
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
    int data[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    size_t size = 15;
    Tvector<int> vector(data, size);
    vector.erase(1);
    vector.erase(1);
    vector.erase(1);
    // Act
    bool actual_result = vector.get_deleted() == 0
        && vector.get_size() == 12
        && vector.get_capacity() == 27;
    // Assert
    bool expected_result = true;
    EXPECT_EQ(expected_result, actual_result);
}
TEST(TestVectorLib, erase3) {
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
