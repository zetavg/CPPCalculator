#include "gtest/gtest.h"
#include "Integer.h"

#include <iostream>

// Tests Integer

// Test constructor of Integer
TEST(IntegerTest, Constructor) {
    Integer i0;
    EXPECT_STREQ(i0.get_value().c_str(), "null");
    Integer i1 { "0" };
    EXPECT_STREQ(i1.get_value().c_str(), "0");
    Integer i2 { "99" };
    EXPECT_STREQ(i2.get_value().c_str(), "99");
    Integer i3 { "99+9" };
    EXPECT_STREQ(i3.get_value().c_str(), "99");
    Integer i4 { "0123" };
    EXPECT_STREQ(i4.get_value().c_str(), "123");
}

// Test operator << of Integer
TEST(IntegerTest, InputOperator) {
    std::stringstream output_ss;
    Integer integer { "1234" };
    output_ss << integer;
    EXPECT_STREQ(output_ss.str().c_str(), "1234");
}

// Test operator >> of Integer
TEST(IntegerTest, OutputOperator) {
    std::stringstream input_ss;
    Integer integer;
    input_ss << "1234";
    input_ss >> integer;
    EXPECT_STREQ(integer.get_value().c_str(), "1234");
}

// Test operator + of Integer
TEST(IntegerTest, AdditionOperator) {
    Integer a { "1024" }, b { "313" };
    EXPECT_STREQ((a + b).get_value().c_str(), "1337");
}

// Test operator - of Integer
TEST(IntegerTest, SubtractionOperator) {
    Integer a { "65535" }, b { "64198" };
    EXPECT_STREQ((a - b).get_value().c_str(), "1337");
}

// Test operator * of Integer
TEST(IntegerTest, MultiplicationOperator) {
    Integer a { "1024" }, b { "768" };
    EXPECT_STREQ((a * b).get_value().c_str(), "786432");
}

// Test operator / of Integer
// TEST(IntegerTest, DivisionOperator) {
//     Integer a { "64" }, b { "8" };
//     EXPECT_STREQ((a + b).get_value().c_str(), "8");
// }
