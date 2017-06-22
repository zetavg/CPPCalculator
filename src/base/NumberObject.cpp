#include "NumberObject.h"

/*
 * Value calculation helpers
 */

// Adds up two number_value_t, and return the sum
number_value_t NumberObject::addup_raw_value(const number_value_t &a, const number_value_t &b) {
    number_value_t result;
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

// Subtracts two number_value_t (a - b), and return the remaining value
//
// The first value must be larger then the second one. It is the caller's
// responsibility to ensure the inputs are valid, and to deal with the leading
// zeros of the result.
number_value_t NumberObject::substractdown_raw_value(const number_value_t &a, const number_value_t &b) {
    number_value_t result;
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

    arrange_raw_value(result);

    return result;
}

// Adds an integer to a raw value
number_value_t NumberObject::raw_value_plus(number_value_t &v, int amount) {
    int carry = amount;

    for (number_value_t::iterator it = v.begin(); it != v.end(); ++it) {
        *it += carry;
        carry = 0;
        if (*it < 10) break;
        carry = *it / 10;
        *it %= 10;
    }

    if (carry > 0) v.push_back(carry);

    return v;
}

// Multiply two number_value_t (a * b)
number_value_t NumberObject::multiply_raw_value(const number_value_t &a, const number_value_t &b) {
    number_value_t result;
    int a_size = a.size();
    int b_size = b.size();

    for (int i = 0, carry = 0; i < a_size; ++i) {
        for (int j = 0; j < b_size; ++j) {
            unsigned long p = i + j;
            number_digit_t digit = a.at(i) * b.at(j) + carry;
            if (result.size() > p) digit += result.at(p);
            carry = digit / 10;
            digit = digit % 10;
            if (result.size() > p) {
                result.at(p) = digit;
            } else {
                result.push_back(digit);
            }
        }

        if (carry > 0) {
            result.push_back(carry);
            carry = 0;
        }
    }

    return result;
}

// Compares two number_value_t
//
// Returns 1 if the first one is larger then the second, -1 if smaller,
// or 0 if same.
int NumberObject::compare_raw_value(const number_value_t &a, const number_value_t &b) {
    int a_size = a.size();
    int b_size = b.size();

    if (a_size > b_size) {
        return 1;
    } else if (b_size > a_size) {
        return -1;
    } else {
        for (
            number_value_t::const_iterator a_i = a.end() - 1,
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

number_value_t NumberObject::arrange_raw_value(number_value_t &v) {
    while (v.size() > 1 && v.back() == 0) {
        v.pop_back();
    }

    return v;
}

std::string NumberObject::print_raw_value_to_string(number_value_t &v, std::string &str) {
    if (v.empty()) return str;
    for (number_value_t::iterator it = v.end() - 1; it >= v.begin(); --it) {
        str.push_back(*it + 48);
    }

    return str;
}
