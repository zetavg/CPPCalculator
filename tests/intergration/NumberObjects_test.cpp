#include "gtest/gtest.h"
#include "../../src/Integer.h"
#include "../../src/Decimal.h"
#include "../../src/Complex.h"

#include <iostream>
#include <vector>

using namespace std;

// Test NumberObjects

// Test polymorphism output (<<) of NumberObjects
TEST(NumberObjectsTest, PolymorphismOutput) {
    Integer i = "123";
    Decimal d = "123.3";

    vector<NumberObject*> nums;
    nums.push_back(&i);
    nums.push_back(&d);

    std::stringstream output_ss_0;
    output_ss_0 << *nums.at(0);
    EXPECT_STREQ(output_ss_0.str().c_str(), "123");

    std::stringstream output_ss_1;
    output_ss_1 << *nums.at(1);
    EXPECT_STREQ(output_ss_1.str().c_str(), "123.3");
}

// Test polymorphism input (>>) of NumberObjects
TEST(NumberObjectsTest, PolymorphismInput) {
    Integer i;
    Decimal d;

    vector<NumberObject*> nums;
    nums.push_back(&i);
    nums.push_back(&d);

    std::stringstream input_ss_0, output_ss_0;
    input_ss_0 << "123";
    input_ss_0 >> *nums.at(0);
    output_ss_0 << *nums.at(0);
    EXPECT_STREQ(output_ss_0.str().c_str(), "123");

    std::stringstream input_ss_1, output_ss_1;
    input_ss_1 << "123.456";
    input_ss_1 >> *nums.at(1);
    output_ss_1 << *nums.at(1);
    EXPECT_STREQ(output_ss_1.str().c_str(), "123.456");
}

// Test calculation of NumberObjects
TEST(NumberObjectsTest, Calculation) {
    Integer i;
    Decimal d;
    Complex c;

    std::stringstream input_ss_0, input_ss_1, input_ss_2;
    input_ss_0 << "123";
    input_ss_1 << "321.321";
    input_ss_2 << "123.123+321.321i";

    input_ss_0 >> i;
    input_ss_1 >> d;
    input_ss_2 >> c;

    std::stringstream output_ss_0;
    output_ss_0 << d + i;
    EXPECT_STREQ(output_ss_0.str().c_str(), "444.321");

    std::stringstream output_ss_1;
    output_ss_1 << i + c;
    EXPECT_STREQ(output_ss_1.str().c_str(), "246.123+321.321i");

    std::stringstream output_ss_2;
    output_ss_2 << d + c;
    EXPECT_STREQ(output_ss_2.str().c_str(), "444.444+321.321i");
}
