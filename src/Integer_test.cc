#include "gtest/gtest.h"
#include "Integer.h"

#include <iostream>

// Tests Integer

// Test constructor of Integer
TEST(IntegerTest, Constructor) {
    Integer integer_0;
    EXPECT_STREQ(integer_0.get_value().c_str(), "null");
    Integer integer_1 = "0";
    EXPECT_STREQ(integer_1.get_value().c_str(), "0");
    Integer integer_2 = "99";
    EXPECT_STREQ(integer_2.get_value().c_str(), "99");
    Integer integer_3 = "-99";
    EXPECT_STREQ(integer_3.get_value().c_str(), "-99");
    Integer integer_4 = "00123";
    EXPECT_STREQ(integer_4.get_value().c_str(), "123");
    Integer integer_5 = "-00123";
    EXPECT_STREQ(integer_5.get_value().c_str(), "-123");
}

// Test constructor of big Integer
TEST(IntegerTest, Constructor_BigValue) {
    Integer big_integer = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    EXPECT_STREQ(big_integer.get_value().c_str(), "12345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

// Test operator << of Integer
TEST(IntegerTest, InputOperator) {
    std::stringstream output_ss;
    Integer integer = "1234";
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

// Test operator = of Integer
TEST(IntegerTest, AssignmentOperator) {
    Integer integer;
    integer = "1";
    EXPECT_STREQ(integer.get_value().c_str(), "1");
    integer = "2";
    EXPECT_STREQ(integer.get_value().c_str(), "2");
    integer = "878387873838970189236042384512839412865838637846182735923765917823649";
    EXPECT_STREQ(integer.get_value().c_str(), "878387873838970189236042384512839412865838637846182735923765917823649");

    integer = "0";
    Integer integer_2;
    integer_2 = integer;
    EXPECT_STREQ(integer.get_value().c_str(), "0");
    EXPECT_STREQ(integer_2.get_value().c_str(), "0");
    integer_2 = "1";
    EXPECT_STREQ(integer.get_value().c_str(), "0");
    EXPECT_STREQ(integer_2.get_value().c_str(), "1");
    integer = "-1";
    EXPECT_STREQ(integer.get_value().c_str(), "-1");
    EXPECT_STREQ(integer_2.get_value().c_str(), "1");
}

// Test operator + of Integer
TEST(IntegerTest, AdditionOperator) {
    Integer a = "1024", b = "313";
    EXPECT_STREQ((a + b).get_value().c_str(), "1337");
}

// Test operator + of Integer with big values
TEST(IntegerTest, AdditionOperator_BigValue) {
    Integer a = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    Integer b = "-12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    Integer c = "87654321098765432109876543210987654321098765432109876543210987654321098765432110";
    Integer d = "12345";
    Integer e = "0";
    EXPECT_STREQ((a + a).get_value().c_str(), "24691357802469135780246913578024691357802469135780246913578024691357802469135780");
    EXPECT_STREQ((a + b).get_value().c_str(), "0");
    EXPECT_STREQ((a + c).get_value().c_str(), "100000000000000000000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_STREQ((a + e).get_value().c_str(), "12345678901234567890123456789012345678901234567890123456789012345678901234567890");
    EXPECT_STREQ((b + a).get_value().c_str(), "0");
    EXPECT_STREQ((b + b).get_value().c_str(), "-24691357802469135780246913578024691357802469135780246913578024691357802469135780");
    EXPECT_STREQ((b + c).get_value().c_str(), "75308642197530864219753086421975308642197530864219753086421975308642197530864220");
    EXPECT_STREQ((b + d).get_value().c_str(), "-12345678901234567890123456789012345678901234567890123456789012345678901234555545");
    EXPECT_STREQ((b + e).get_value().c_str(), "-12345678901234567890123456789012345678901234567890123456789012345678901234567890");
    EXPECT_STREQ((c + b).get_value().c_str(), "75308642197530864219753086421975308642197530864219753086421975308642197530864220");
    EXPECT_STREQ((d + b).get_value().c_str(), "-12345678901234567890123456789012345678901234567890123456789012345678901234555545");
    EXPECT_STREQ((e + a).get_value().c_str(), "12345678901234567890123456789012345678901234567890123456789012345678901234567890");
    EXPECT_STREQ((e + b).get_value().c_str(), "-12345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

// Test operator - of Integer
TEST(IntegerTest, SubtractionOperator) {
    Integer a = "65535", b = "64198";
    EXPECT_STREQ((-a).get_value().c_str(), "-65535");
    EXPECT_STREQ(a.get_value().c_str(), "65535");
    EXPECT_STREQ((a - b).get_value().c_str(), "1337");
}

// Test operator - of Integer with big values
TEST(IntegerTest, SubtractionOperator_BigValue) {
    Integer a = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    Integer b = "-12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    Integer c = "87654321098765432109876543210987654321098765432109876543210987654321098765432110";
    Integer d = "12345";
    Integer e = "0";
    EXPECT_STREQ((a - a).get_value().c_str(), "0");
    EXPECT_STREQ((a - b).get_value().c_str(), "24691357802469135780246913578024691357802469135780246913578024691357802469135780");
    EXPECT_STREQ((a - c).get_value().c_str(), "-75308642197530864219753086421975308642197530864219753086421975308642197530864220");
    EXPECT_STREQ((a - e).get_value().c_str(), "12345678901234567890123456789012345678901234567890123456789012345678901234567890");
    EXPECT_STREQ((b - a).get_value().c_str(), "-24691357802469135780246913578024691357802469135780246913578024691357802469135780");
    EXPECT_STREQ((b - b).get_value().c_str(), "0");
    EXPECT_STREQ((b - c).get_value().c_str(), "-100000000000000000000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_STREQ((b - d).get_value().c_str(), "-12345678901234567890123456789012345678901234567890123456789012345678901234580235");
    EXPECT_STREQ((b - e).get_value().c_str(), "-12345678901234567890123456789012345678901234567890123456789012345678901234567890");
    EXPECT_STREQ((c - b).get_value().c_str(), "100000000000000000000000000000000000000000000000000000000000000000000000000000000");
    EXPECT_STREQ((d - b).get_value().c_str(), "12345678901234567890123456789012345678901234567890123456789012345678901234580235");
    EXPECT_STREQ((e - a).get_value().c_str(), "-12345678901234567890123456789012345678901234567890123456789012345678901234567890");
    EXPECT_STREQ((e - b).get_value().c_str(), "12345678901234567890123456789012345678901234567890123456789012345678901234567890");

}

// Test operator * of Integer
TEST(IntegerTest, MultiplicationOperator) {
    Integer a = "12", b = "12";
    EXPECT_STREQ((a * b).get_value().c_str(), "144");
    Integer c = "1024", d = "768";
    EXPECT_STREQ((c * d).get_value().c_str(), "786432");
    Integer e = "999", f = "-999";
    EXPECT_STREQ((e * f).get_value().c_str(), "-998001");
    Integer g = "-1", h = "-1";
    EXPECT_STREQ((g * h).get_value().c_str(), "1");
}

// Test operator * of Integer with big values
TEST(IntegerTest, MultiplicationOperator_BigValue) {
    Integer a = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    Integer b = "-12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    Integer c = "-1";
    EXPECT_STREQ((a * a).get_value().c_str(), "152415787532388367504953515625666819450083828733760097552251181223112635269100012193273126047859425087639153757049236500533455762536198787501905199875019052100");
    EXPECT_STREQ((a * b).get_value().c_str(), "-152415787532388367504953515625666819450083828733760097552251181223112635269100012193273126047859425087639153757049236500533455762536198787501905199875019052100");
    EXPECT_STREQ((b * c).get_value().c_str(), "12345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

// Test operator / of Integer
// TEST(IntegerTest, DivisionOperator) {
//     Integer a { "64" }, b { "8" };
//     EXPECT_STREQ((a + b).get_value().c_str(), "8");
// }
