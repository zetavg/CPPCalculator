#include "Decimal.h"

#include <string>
#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Integer.h"

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


Decimal::Decimal(const Decimal &integer) {
    copy_value_from(integer);
}

/*
 * Getter and setters
 */

Decimal& Decimal::set_value(const char *number) {
    sign = true;
    molecular.clear();
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
                molecular.swap(denominator);
                molecular.clear();
                continue;
            }

            int n = number[i] - 48;
            if (n < 0 && n > 9) continue;

            molecular.push_back(n);

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
    if (molecular.empty()) {
        return "null";
    } else if (molecular.size() == 1 && molecular.at(0) == 0) {
        return "0";
    } else {
        unsigned long long approximate_denominator = 0;
        unsigned long long approximate_denominator_lost_digits;
        if (denominator.size() < DECIMAL_APPROXIMATE_DENOMINATOR_MAX_DIGITS) {
            approximate_denominator_lost_digits = 0;
        } else {
            approximate_denominator_lost_digits = denominator.size() + 1 - DECIMAL_APPROXIMATE_DENOMINATOR_MAX_DIGITS;
        }
        for (
            decimal_value_t::iterator it = denominator.end() - 1;
            it >= denominator.begin() && denominator.end() - it < DECIMAL_APPROXIMATE_DENOMINATOR_MAX_DIGITS;
            --it
        ) {
            approximate_denominator *= 10;
            approximate_denominator += *it;
        }

        if (approximate_denominator == 0) approximate_denominator = 1;

        unsigned long long output_value_digits_after_decimal_point = 0;
        unsigned long long output_value_multiplier = 1;
        while ((long long)std::pow(10, output_value_digits_after_decimal_point) % approximate_denominator > 0 && output_value_digits_after_decimal_point < DECIMAL_APPROXIMATE_DENOMINATOR_MAX_DIGITS) {
            ++output_value_digits_after_decimal_point;
            output_value_multiplier = std::pow(10, output_value_digits_after_decimal_point) / approximate_denominator;
        }

        output_value_digits_after_decimal_point += approximate_denominator_lost_digits;

        decimal_value_t output_value;
        int molecular_size = molecular.size();
        unsigned long long carry = 0;
        for (
            int i = 0;
            i < molecular_size || carry != 0;
            ++i
        ) {
            unsigned long long digit = carry;
            if (i < molecular_size) digit += molecular.at(i) * output_value_multiplier;
            carry = digit / 10;
            digit = digit % 10;
            output_value.push_back((decimal_digit_t)digit);
        }

        std::string str;

        bool has_point = false;

        if (!sign) str.push_back('-');

        if (output_value_digits_after_decimal_point >= output_value.size()) {
            str.push_back('0');
            if (output_value_digits_after_decimal_point > output_value.size()) {
                str.push_back('.');
                has_point = true;
                for (int i = 0; i < output_value_digits_after_decimal_point - output_value.size(); ++i) str.push_back('0');
            }
        }

        for (decimal_value_t::iterator it = output_value.end() - 1; it >= output_value.begin(); --it) {
            if (output_value_digits_after_decimal_point == it - output_value.begin() + 1) {
                str.push_back('.');
                has_point = true;
            }
            str.push_back(*it + 48);
        }

        if (has_point) for (std::string::iterator it = str.end() - 1; it >= str.begin(); --it) {
            if (*it == '0' || *it == '.') {
                *it = '\0';
            } else {
                break;
            }
        }

        return str;
    }
}

Decimal& Decimal::copy_value_from(const Decimal &reference) {
    sign = reference.sign;
    molecular = decimal_value_t(reference.molecular);
    return *this;
}

/*
 * Value calculation helpers
 */

// Currently none

/*
 * Overload operators
 */

Decimal& Decimal::operator=(const char *number) {
    set_value(number);
    return *this;
}

Decimal& Decimal::operator=(const Decimal &integer) {
    copy_value_from(integer);
    return *this;
}

std::ostream& operator<<(std::ostream &out, Decimal &integer) {
    out << integer.get_value();
    return out;
}

std::istream& operator>>(std::istream &in, Decimal &integer) {
    std::string str;
    in >> str;
    integer.set_value(str.c_str());

    return in;
}

Decimal operator+(Decimal &a, Decimal &b) {
    // TODO
}

Decimal operator-(Decimal &decimal) {
    Decimal result(decimal);
    result.sign = !decimal.sign;
    return result;
}

Decimal operator-(Decimal &a, Decimal &b) {
    Decimal negative_b = -b;
    return (a + negative_b);
}

Decimal operator*(Decimal &a, Decimal &b) {
    Decimal result;
    result.molecular = Integer::multiply_raw_value(a.molecular, b.molecular);
    result.denominator = Integer::multiply_raw_value(a.denominator, b.denominator);
    result.sign = a.sign == b.sign;
    return result;
}

/*
 * Private methods
 */

void Decimal::arrange() {
    while (molecular.size() > 1 && molecular.back() == 0) {
        molecular.pop_back();
    }
    while (denominator.size() > 1 && denominator.back() == 0) {
        denominator.pop_back();
    }
}
