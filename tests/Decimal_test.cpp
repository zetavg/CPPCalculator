#include "gtest/gtest.h"
#include "../src/Decimal.h"

#include <iostream>

// Tests Decimal

// Test constructor of Decimal
TEST(DecimalTest, Constructor) {
    Decimal decimal_0;
    EXPECT_STREQ(decimal_0.get_value().c_str(), "null");
    Decimal decimal_1 = "0.0";
    EXPECT_STREQ(decimal_1.get_value().c_str(), "0");
    Decimal decimal_2 = "9876543210";
    EXPECT_STREQ(decimal_2.get_value().c_str(), "9876543210");
    Decimal decimal_3 = "99.999";
    EXPECT_STREQ(decimal_3.get_value().c_str(), "99.999");
    Decimal decimal_4 = "-999.999900";
    EXPECT_STREQ(decimal_4.get_value().c_str(), "-999.9999");
    Decimal decimal_5 = "00123.0000";
    EXPECT_STREQ(decimal_5.get_value().c_str(), "123");
    Decimal decimal_6 = "-00123.0000";
    EXPECT_STREQ(decimal_6.get_value().c_str(), "-123");
    Decimal decimal_7 = "1/5";
    EXPECT_STREQ(decimal_7.get_value().c_str(), "0.2");
    Decimal decimal_8 = "1/104729";
    EXPECT_STREQ(decimal_8.get_value().c_str(), "0.0000095484536279349552");
    Decimal decimal_9 = "0";
    Decimal decimal_10 = decimal_9;
    decimal_9 = "1";
    EXPECT_STREQ(decimal_9.get_value().c_str(), "1");
    EXPECT_STREQ(decimal_10.get_value().c_str(), "0");
}

// Test constructor of big Decimal
TEST(DecimalTest, Constructor_BigValue) {
    Decimal big_decimal = "12345678901234567890123456789012345678901234567890123456789012345678901234567890.09876543210987654321";
    EXPECT_STREQ(big_decimal.get_value().c_str(), "12345678901234567890123456789012345678901234567890123456789012345678901234567890.09876543210987654321");
    Decimal big_decimal_18d = "123456789012345678.123456789012345678";
    EXPECT_STREQ(big_decimal_18d.get_value().c_str(), "123456789012345678.123456789012345678");
    Decimal big_decimal_17d = "12345678901234567.12345678901234567";
    EXPECT_STREQ(big_decimal_17d.get_value().c_str(), "12345678901234567.12345678901234567");
    Decimal big_decimal_16d = "1234567890123456.1234567890123456";
    EXPECT_STREQ(big_decimal_16d.get_value().c_str(), "1234567890123456.1234567890123456");
    Decimal big_decimal_15d = "123456789012345.123456789012345";
    EXPECT_STREQ(big_decimal_15d.get_value().c_str(), "123456789012345.123456789012345");
    Decimal big_decimal_14d = "12345678901234.12345678901234";
    EXPECT_STREQ(big_decimal_14d.get_value().c_str(), "12345678901234.12345678901234");
}

// Test operator << of Decimal
TEST(DecimalTest, InputOperator) {
    std::stringstream output_ss;
    Decimal decimal = "1234.5678";
    output_ss << decimal;
    EXPECT_STREQ(output_ss.str().c_str(), "1234.5678");
}

// Test operator >> of Decimal
TEST(DecimalTest, OutputOperator) {
    std::stringstream input_ss;
    Decimal decimal;
    input_ss << "1234.5678";
    input_ss >> decimal;
    EXPECT_STREQ(decimal.get_value().c_str(), "1234.5678");
    std::stringstream input_ss2;
    input_ss2 << "1234.0000";
    input_ss2 >> decimal;
    EXPECT_STREQ(decimal.get_value().c_str(), "1234");
    std::stringstream input_ss3;
    input_ss3 << "-1234.7890";
    input_ss3 >> decimal;
    EXPECT_STREQ(decimal.get_value().c_str(), "-1234.789");
}

// Test operator = of Decimal
TEST(DecimalTest, AssignmentOperator) {
    Decimal decimal;
    decimal = "1.1";
    EXPECT_STREQ(decimal.get_value().c_str(), "1.1");
    decimal = "2.2";
    EXPECT_STREQ(decimal.get_value().c_str(), "2.2");
    decimal = "878387873838970189236042384512839412865838637846182735923765917823649.0387261087324";
    EXPECT_STREQ(decimal.get_value().c_str(), "878387873838970189236042384512839412865838637846182735923765917823649.0387261087324");

    decimal = "0";
    Decimal decimal_2;
    decimal_2 = decimal;
    EXPECT_STREQ(decimal.get_value().c_str(), "0");
    EXPECT_STREQ(decimal_2.get_value().c_str(), "0");
    decimal_2 = "1";
    EXPECT_STREQ(decimal.get_value().c_str(), "0");
    EXPECT_STREQ(decimal_2.get_value().c_str(), "1");
    decimal = "-1";
    EXPECT_STREQ(decimal.get_value().c_str(), "-1");
    EXPECT_STREQ(decimal_2.get_value().c_str(), "1");
}

// Test operator + of Decimal
TEST(DecimalTest, AdditionOperator) {
    Decimal a = "10.24", b = "3.13";
    EXPECT_STREQ((a + b).get_value().c_str(), "13.37");
}

// Test operator + of Decimal with big values
TEST(DecimalTest, AdditionOperator_BigValue) {
    Decimal a = "1234567890.0987654321";
    Decimal b = "-1234567890.0987654321";
    Decimal c = "8765432109.90123456791";
    Decimal d = "1/3";
    Decimal e = "0";
    EXPECT_STREQ((a + a).get_value().c_str(), "2469135780.1975308642");
    EXPECT_STREQ((a + b).get_value().c_str(), "0");
    EXPECT_STREQ((a + c).get_value().c_str(), "10000000000.00000000001");
    EXPECT_STREQ((a + d).get_value().c_str(), "1234567890.432098716050617716049382716");
    EXPECT_STREQ((a + e).get_value().c_str(), "1234567890.0987654321");
    EXPECT_STREQ((b + a).get_value().c_str(), "0");
    EXPECT_STREQ((b + b).get_value().c_str(), "-2469135780.1975308642");
    EXPECT_STREQ((b + c).get_value().c_str(), "7530864219.80246913581");
    EXPECT_STREQ((b + d).get_value().c_str(), "-1234567889.765432049383951076049382716");
    EXPECT_STREQ((b + e).get_value().c_str(), "-1234567890.0987654321");
    EXPECT_STREQ((c + b).get_value().c_str(), "7530864219.80246913581");
    EXPECT_STREQ((d + b).get_value().c_str(), "-1234567889.765432049383951076049382716");
    EXPECT_STREQ((d + e).get_value().c_str(), "0.33333333333333332");
    EXPECT_STREQ((e + a).get_value().c_str(), "1234567890.0987654321");
    EXPECT_STREQ((e + b).get_value().c_str(), "-1234567890.0987654321");
}

// Test operator - of Decimal
TEST(DecimalTest, SubtractionOperator) {
    Decimal a = "655.35", b = "641.98";
    EXPECT_STREQ((-a).get_value().c_str(), "-655.35");
    EXPECT_STREQ(a.get_value().c_str(), "655.35");
    EXPECT_STREQ((a - b).get_value().c_str(), "13.37");
}

// Test operator * of Decimal
TEST(DecimalTest, MultiplicationOperator) {
    Decimal a = "1.2", b = "1.2";
    EXPECT_STREQ((a * b).get_value().c_str(), "1.44");
    Decimal c = "1024", d = "768.1";
    EXPECT_STREQ((c * d).get_value().c_str(), "786534.4");
    Decimal e = "999.99", f = "-999.99";
    EXPECT_STREQ((e * f).get_value().c_str(), "-999980.0001");
    Decimal g = "-1", h = "-1";
    EXPECT_STREQ((g * h).get_value().c_str(), "1");
}

// Test operator * of Decimal with big values
TEST(DecimalTest, MultiplicationOperator_BigValue) {
    Decimal a = "1234567890.0987654321";
    Decimal b = "-1234567890.0987654321";
    Decimal c = "-1";
    EXPECT_STREQ((a * a).get_value().c_str(), "1524157875262917362.23502514857789971041");
    EXPECT_STREQ((a * b).get_value().c_str(), "-1524157875262917362.23502514857789971041");
    EXPECT_STREQ((b * c).get_value().c_str(), "1234567890.0987654321");
}

// Test operator / of Decimal
TEST(DecimalTest, DivisionOperator) {
    Decimal a = "64", b = "8";
    EXPECT_STREQ((a / b).get_value().c_str(), "8");
    Decimal c = "20", d = "0.2";
    EXPECT_STREQ((c / d).get_value().c_str(), "100");
    Decimal e = "1/3", f = "2/3";
    EXPECT_STREQ((e / f).get_value().c_str(), "0.499999999999999968");
}
