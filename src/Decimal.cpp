#include "Decimal.h"

#include <string>
#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define DECIMAL_APPROXIMATE_DENOMINATOR_MAX_DIGITS 16

/*
 * Constructors
 */

Decimal::Decimal() {
    set_value("null");
}

Decimal::Decimal(const char *number) {
    set_value(number);
}

Decimal::Decimal(const Decimal &decimal) {
    copy_value_from(decimal);
}

/*
 * Getter and setters
 */

Decimal& Decimal::set_value(const char *number) {
    sign = true;
    value.clear();
    denominator.clear();

    if (strcmp(number, "null") != 0) {
        int last;
        for (last = 0; number[last] != '\0'; ++last) continue;
        int state = 0;

        for (int i = last - 1; i >= 0; --i) {
            if (number[i] == '-') {
                sign = false;
                continue;
            }
            if (number[i] == '.') {
                state = 1;
                continue;
            }
            if (number[i] == '/') {
                state = 2;
                value.swap(denominator);
                value.clear();
                continue;
            }

            int n = number[i] - 48;
            if (n < 0 && n > 9) continue;

            value.push_back(n);

            if (state == 0) {
                denominator.push_back(0);
            }
        }

        if (state == 0) {
            denominator.clear();
            denominator.push_back(1);
        } else if (state == 1) {
            denominator.push_back(1);
        }

        arrange();
    }

    return *this;
}

std::string Decimal::get_value() {
    if (value.empty()) {
        return "null";
    } else if (value.size() == 1 && value.at(0) == 0) {
        return "0.0";
    } else if (denominator.size() == 1 && denominator.at(0) == 1) {
        std::string str;
        if (!sign) str.push_back('-');
        print_raw_value_to_string(value, str);
        str.push_back('.');
        str.push_back('0');
        return str;
    } else {
        // calculate the value in decimal format
        number_value_t molecular(value);
        number_value_t result_integer_part, result_decimal_part;
        result_integer_part.push_back(0);

        while (compare_raw_value(molecular, denominator) >= 0) {
            molecular = substractdown_raw_value(molecular, denominator);
            raw_value_plus(result_integer_part, 1);
        }

        for (int i = 0; i < 100; ++i) {
            if (molecular.size() == 1 && molecular.at(0) == 0) break;
            molecular.insert(molecular.begin(), 0);
            int d = 0;
            while (compare_raw_value(molecular, denominator) >= 0) {
                molecular = substractdown_raw_value(molecular, denominator);
                ++d;
            }
            result_decimal_part.push_back(d);
        }

        result_decimal_part.push_back(0);
        arrange_raw_value(result_decimal_part);
        std::reverse(result_decimal_part.begin(), result_decimal_part.end());

        std::string str;
        if (!sign) str.push_back('-');
        print_raw_value_to_string(result_integer_part, str);
        str.push_back('.');
        print_raw_value_to_string(result_decimal_part, str);

        return str;
    }
}

Decimal& Decimal::copy_value_from(const Decimal &reference) {
    sign = reference.sign;
    value = number_value_t(reference.value);
    denominator = number_value_t(reference.denominator);
    return *this;
}

/*
 * Overload operators
 */

Decimal& Decimal::operator=(const char *number) {
    set_value(number);
    return *this;
}

Decimal& Decimal::operator=(const Decimal &decimal) {
    copy_value_from(decimal);
    return *this;
}

std::ostream& operator<<(std::ostream &out, Decimal decimal) {
    out << decimal.get_value();
    return out;
}

std::istream& operator>>(std::istream &in, Decimal &decimal) {
    std::string str;
    in >> str;
    decimal.set_value(str.c_str());

    return in;
}

Decimal operator+(Decimal a, Decimal b) {
    // Make the denominator same
    number_value_t result_denominator = Decimal::multiply_raw_value(a.denominator, b.denominator);

    // Calculate the values after multiplication
    number_value_t a_value_after_multiplication = Decimal::multiply_raw_value(a.value, b.denominator);
    number_value_t b_value_after_multiplication = Decimal::multiply_raw_value(b.value, a.denominator);

    if (a.sign && b.sign) {
        // simply add the values if both a and b are both positive
        Decimal result;
        result.sign = true;
        result.value = Decimal::addup_raw_value(a_value_after_multiplication, b_value_after_multiplication);
        result.denominator = result_denominator;
        return result;

    } else if (!a.sign && !b.sign) {
        // add the values and set the sign to negative if both a and b are both negative
        Decimal result;
        result.sign = false;
        result.value = Decimal::addup_raw_value(a_value_after_multiplication, b_value_after_multiplication);
        result.denominator = result_denominator;
        return result;

    } else {
        // we need to compare the values and perform an substraction
        number_value_t positive_value_after_multiplication, negative_value_after_multiplication;

        // find the positive and negative decimal
        if (a.sign && !b.sign) {
            positive_value_after_multiplication = a_value_after_multiplication;
            negative_value_after_multiplication = b_value_after_multiplication;
        } else {
            positive_value_after_multiplication = b_value_after_multiplication;
            negative_value_after_multiplication = a_value_after_multiplication;
        }

        // compare the values to decide what to do
        int comparing_result = Decimal::compare_raw_value(positive_value_after_multiplication, negative_value_after_multiplication);

        if (comparing_result > 0) {
            // the positive value is larger then the negative value
            Decimal result;
            result.sign = true;
            result.value = Decimal::substractdown_raw_value(positive_value_after_multiplication, negative_value_after_multiplication);
            result.denominator = result_denominator;
            result.arrange();
            return result;
        } else if (comparing_result < 0) {
            // the negative value is larger then the positive value
            Decimal result;
            result.sign = false;
            result.value = Decimal::substractdown_raw_value(negative_value_after_multiplication, positive_value_after_multiplication);
            result.denominator = result_denominator;
            result.arrange();
            return result;
        } else {
            // the two values are same
            Decimal result("0");
            return result;
        }
    }
}

Decimal operator-(Decimal &decimal) {
    Decimal result(decimal);
    result.sign = !decimal.sign;
    return result;
}

Decimal operator-(Decimal a, Decimal b) {
    Decimal negative_b = -b;
    return (a + negative_b);
}

Decimal operator*(Decimal a, Decimal b) {
    Decimal result;
    result.value = Decimal::multiply_raw_value(a.value, b.value);
    result.denominator = Decimal::multiply_raw_value(a.denominator, b.denominator);
    result.sign = a.sign == b.sign;
    return result;
}

Decimal operator/(Decimal a, Decimal b) {
    Decimal result;
    result.value = Decimal::multiply_raw_value(a.value, b.denominator);
    result.denominator = Decimal::multiply_raw_value(a.denominator, b.value);
    result.sign = a.sign == b.sign;
    result.arrange();
    return result;
}

Decimal operator+(Decimal a, Integer b) {
    Decimal db = b.get_value().c_str();
    return a + db;
}
Decimal operator-(Decimal a, Integer b) {
    Decimal db = b.get_value().c_str();
    return a - db;
}
Decimal operator*(Decimal a, Integer b) {
    Decimal db = b.get_value().c_str();
    return a * db;
}
Decimal operator/(Decimal a, Integer b) {
    Decimal db = b.get_value().c_str();
    return a / db;
}
Decimal operator+(Integer a, Decimal b) {
    Decimal da = a.get_value().c_str();
    return da + b;
}
Decimal operator-(Integer a, Decimal b) {
    Decimal da = a.get_value().c_str();
    return da - b;
}
Decimal operator*(Integer a, Decimal b) {
    Decimal da = a.get_value().c_str();
    return da * b;
}
Decimal operator/(Integer a, Decimal b) {
    Decimal da = a.get_value().c_str();
    return da / b;
}
Decimal operator/(Integer a, Integer b) {
    Decimal db = a.get_value().c_str();
    Decimal da = a.get_value().c_str();
    return da / db;
}

/*
 * Private methods
 */

void Decimal::arrange() {
    value = Decimal::arrange_raw_value(value);
    denominator = Decimal::arrange_raw_value(denominator);
}
