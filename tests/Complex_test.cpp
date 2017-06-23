#include "gtest/gtest.h"
#include "../src/Complex.h"

#include <iostream>

// Tests Complex

// Test constructor of Complex
TEST(ComplexTest, Constructor) {
    Complex complex_0;
    EXPECT_STREQ(complex_0.get_value().c_str(), "null");
    Complex complex_1 = "1.0+452.11111333i";
    EXPECT_STREQ(complex_1.get_value().c_str(), "1.0+452.11111333i");
}

// Test operator - of Complex
TEST(ComplexTest, SubtractionOperator) {
    Complex a = "655.35+1.2i", b = "641.98+2.1i";
    EXPECT_STREQ((-a).get_value().c_str(), "-655.35-1.2i");
    EXPECT_STREQ(a.get_value().c_str(), "655.35+1.2i");
    EXPECT_STREQ((a - b).get_value().c_str(), "13.37-0.9i");
}
