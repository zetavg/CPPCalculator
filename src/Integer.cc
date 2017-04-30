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

/*
 * Getter and setters
 */

Integer& Integer::set_value(const char *number) {
    sign = true;
    value.clear();

    if (strcmp(number, "null") != 0) {
        int last;
        for (last = 0; number[last] != '\0'; ++last);

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

        for (integer_value_t::iterator it = value.end() - 1; it >= value.begin(); --it) {
            str.push_back(*it + 48);
        }

        return str;
    }
}

/*
 * Value calculation helpers
 */

integer_value_t add_value(integer_value_t &a, integer_value_t &b) {
    integer_value_t result;
    int a_size = a.size();
    int b_size = b.size();
    int max_size = std::max(a_size, b_size);


    for (int i = 0, carry = 0; i < max_size || carry > 0; ++i) {
        int digit = carry;
        if (i < a_size) digit += a.at(i);
        if (i < b_size) digit += b.at(i);
        carry = digit / 10;
        digit = digit % 10;
        result.push_back(digit);
    }

    return result;
}

integer_value_t subtract_value(integer_value_t &a, integer_value_t &b) {
    integer_value_t result;
    int a_size = a.size();
    int b_size = b.size();

    for (int i = 0, carry = 0; i < a_size; ++i) {
        int digit = a.at(i) + carry;
        carry = 0;
        if (i < b_size) digit -= b.at(i);
        if (digit < 0) {
            digit += 10;
            carry = -1;
        }
        result.push_back(digit);
    }

    return result;
}

int compare_value(integer_value_t &a, integer_value_t &b) {
    int a_size = a.size();
    int b_size = b.size();

    if (a_size > b_size) {
        return 1;
    } else if (b_size > a_size) {
        return -1;
    } else {
        for (
            integer_value_t::iterator a_i = a.end() - 1,
                                      b_i = b.end() - 1;
            a_i >= a.begin() && b_i >= b.begin();
            --a_i, --b_i
        ) {
            if (*a_i > *b_i) {
                return 1;
            } else if (*b_i > *a_i) {
                return -1;
            }
        }

        return 0;
    }
}

/*
 * Overload operators
 */

Integer& Integer::operator=(const char *number) {
    set_value(number);
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
        result.value = add_value(a.value, b.value);
        return result;

    } else if (!a.sign && !b.sign) {
        // add the values and set the sign to negative if both a and b are both negative
        Integer result;
        result.sign = false;
        result.value = add_value(a.value, b.value);
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
        int comparing_result = compare_value(positive_integer->value, negative_integer->value);

        if (comparing_result > 0) {
            // the positive value is larger then the negative value
            Integer result;
            result.sign = true;
            result.value = subtract_value(positive_integer->value, negative_integer->value);
            result.arrange();
            return result;
        } else if (comparing_result < 0) {
            // the negative value is larger then the positive value
            Integer result;
            result.sign = false;
            result.value = subtract_value(negative_integer->value, positive_integer->value);
            result.arrange();
            return result;
        } else {
            // the values are the same
            Integer result("0");
            return result;
        }
    }
}

// Integer operator-(Integer &a, Integer &b) {
//     return Integer();
// }

// Integer operator*(Integer &a, Integer &b) {
//     return Integer();
// }

/*
 * Private methods
 */

void Integer::arrange() {
    while (value.size() > 1 && value.back() == 0) {
        value.pop_back();
    }
}
