#include "Integer.h"

#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

/*
 * Constructors
 */

Integer::Integer() {
    set_value("null");
}

Integer::Integer(const char *number) {
    set_value(number);
}


Integer::Integer(const Integer &integer) {
    copy_value_from(integer);
}

/*
 * Getter and setters
 */

Integer& Integer::set_value(const char *number) {
    sign = true;
    value.clear();

    if (strcmp(number, "null") != 0) {
        int last;
        for (last = 0; number[last] != '\0'; ++last) continue;

        for (int i = last - 1; i >= 0; --i) {
            if (number[i] == '-') {
                sign = false;
            } else {
                int n = number[i] - 48;
                if (n < 0 && n > 9) continue;
                value.push_back(n);
            }
        }

        arrange();
    }

    return *this;
}

std::string Integer::get_value() {
    if (value.empty()) {
        return "null";
    } else {
        std::string str;

        if (!sign) str.push_back('-');

        for (number_value_t::iterator it = value.end() - 1; it >= value.begin(); --it) {
            str.push_back(*it + 48);
        }

        return str;
    }
}

Integer& Integer::copy_value_from(const NumberObject &reference) {
    sign = reference.get_raw_sign();
    value = number_value_t(reference.get_raw_value());
    return *this;
}

/*
 * Overload operators
 */

Integer& Integer::operator=(const char *number) {
    set_value(number);
    return *this;
}

Integer& Integer::operator=(const Integer &integer) {
    copy_value_from(integer);
    return *this;
}

std::ostream& operator<<(std::ostream &out, Integer &integer) {
    out << integer.get_value();
    return out;
}

std::istream& operator>>(std::istream &in, Integer &integer) {
    std::string value;
    in >> value;
    integer.set_value(value.c_str());

    return in;
}

Integer operator+(Integer &a, Integer &b) {
    if (a.sign && b.sign) {
        // simply add the values if both a and b are both positive
        Integer result;
        result.sign = true;
        result.value = Integer::addup_raw_value(a.value, b.value);
        return result;

    } else if (!a.sign && !b.sign) {
        // add the values and set the sign to negative if both a and b are both negative
        Integer result;
        result.sign = false;
        result.value = Integer::addup_raw_value(a.value, b.value);
        return result;

    } else {
        // we need to compare the values and perform an substraction
        Integer *positive_integer, *negative_integer;

        // find the positive and negative integer
        if (a.sign && !b.sign) {
            positive_integer = &a;
            negative_integer = &b;
        } else {
            positive_integer = &b;
            negative_integer = &a;
        }

        // compare the values to decide what to do
        int comparing_result = Integer::compare_raw_value(positive_integer->value, negative_integer->value);

        if (comparing_result > 0) {
            // the positive value is larger then the negative value
            Integer result;
            result.sign = true;
            result.value = Integer::substractdown_raw_value(positive_integer->value, negative_integer->value);
            result.arrange();
            return result;
        } else if (comparing_result < 0) {
            // the negative value is larger then the positive value
            Integer result;
            result.sign = false;
            result.value = Integer::substractdown_raw_value(negative_integer->value, positive_integer->value);
            result.arrange();
            return result;
        } else {
            // the two values are same
            Integer result("0");
            return result;
        }
    }
}

Integer operator-(Integer &integer) {
    Integer result(integer);
    result.sign = !integer.sign;
    return result;
}

Integer operator-(Integer &a, Integer &b) {
    Integer negative_b = -b;
    return (a + negative_b);
}

Integer operator*(Integer &a, Integer &b) {
    Integer result;
    result.value = Integer::multiply_raw_value(a.value, b.value);
    result.sign = a.sign == b.sign;
    return result;
}

/*
 * Private methods
 */

void Integer::arrange() {
    value = arrange_raw_value(value);
}
