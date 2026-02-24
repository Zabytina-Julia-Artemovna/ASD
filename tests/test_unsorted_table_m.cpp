// Copyright 2025 Julia Zabytina
#include <stdexcept>
#include <gtest/gtest.h>
#include "../lib_unsorted_table_m/unsorted_table_m.h"
#include "../lib_polynom/polynom.h"
TEST(TestUnsortedTableMLib, unsorted_table_m_default_constructor) {
    // Arrange & Act
    UnsortedTableM<std::string, Polynom> table;
    // Assert
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(0, table.size());
}
TEST(TestUnsortedTableMLib, unsorted_table_m_copy_constructor) {
    // Arrange
    std::string name1 = "polinom1";
    Polynom data1("x^2+2yz^7");
    std::string name2 = "polinom2";
    Polynom data2("x^2+2xz^10+xy+yz");
    UnsortedTableM<std::string, Polynom> table1;
    table1.insert(name1, data1);
    table1.insert(name2, data2);

    // Act 
    UnsortedTableM<std::string, Polynom> table2(table1);

    // Assert - сравниваем строковые представления
    EXPECT_EQ(table1.size(), table2.size());
    std::stringstream ss1, ss2;
    ss1 << table1.find(name1);
    ss2 << table2.find(name1);
    EXPECT_EQ(ss1.str(), ss2.str());
}
//TEST(TestUnsortedTableMLib, unsorted_table_m_operator_assign) {
//    // Arrange & Act
//
//    // Assert
//}
//TEST(TestUnsortedTableMLib, unsorted_table_m_operator_assign_self_copy) {
//    // Arrange & Act
//
//    // Assert
//}
//TEST(TestUnsortedTableMLib, unsorted_table_m_insert) {
//    // Arrange & Act
//
//    // Assert
//}
//TEST(TestUnsortedTableMLib, unsorted_table_m_insert_with_exception) {
//    // Arrange & Act
//
//    // Assert
//}
