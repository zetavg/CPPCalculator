#include "Integer.h"

#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

Integer::Integer() {
    set_value("null");
}

Integer::Integer(const char *number) {
    set_value(number);
}

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

        for (std::vector<integer_digit_t>::iterator it = value.end() - 1; it >= value.begin(); --it) {
            str.push_back(*it + 48);
        }

        return str;
    }
}

void Integer::arrange() {
    while (value.size() > 1 && value.back() == 0) {
        value.pop_back();
    }
}

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

std::vector<integer_digit_t> add_value(std::vector<integer_digit_t> &a, std::vector<integer_digit_t> &b) {
    std::vector<integer_digit_t> result;
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

std::vector<integer_digit_t> subtract_value(std::vector<integer_digit_t> &a, std::vector<integer_digit_t> &b) {
    std::vector<integer_digit_t> result;
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

int compare_value(std::vector<integer_digit_t> &a, std::vector<integer_digit_t> &b) {
    int a_size = a.size();
    int b_size = b.size();

    if (a_size > b_size) {
        return 1;
    } else if (b_size > a_size) {
        return -1;
    } else {
        for (std::vector<integer_digit_t>::iterator a_i = a.end() - 1, b_i = b.end() - 1; a_i >= a.begin() && b_i >= b.begin(); --a_i, --b_i) {
            if (*a_i > *b_i) {
                return 1;
            } else if (*b_i > *a_i) {
                return -1;
            }
        }

        return 0;
    }
}

Integer operator+(Integer &a, Integer &b) {
    if (a.sign && b.sign) {
        Integer result;
        result.sign = true;
        result.value = add_value(a.value, b.value);
        return result;
    } else if (a.sign && !b.sign) {
        int c = compare_value(a.value, b.value);

        if (c > 0) {
            Integer result;
            result.sign = true;
            result.value = subtract_value(a.value, b.value);
            result.arrange();
            return result;
        } else if (c < 0) {
            Integer result;
            result.sign = false;
            result.value = subtract_value(b.value, a.value);
            result.arrange();
            return result;
        } else {
            Integer result("0");
            return result;
        }
    } else if (!a.sign && b.sign) {
        int c = compare_value(a.value, b.value);

        if (c > 0) {
            Integer result;
            result.sign = false;
            result.value = subtract_value(a.value, b.value);
            result.arrange();
            return result;
        } else if (c < 0) {
            Integer result;
            result.sign = true;
            result.value = subtract_value(b.value, a.value);
            result.arrange();
            return result;
        } else {
            Integer result("0");
            return result;
        }
    } else if (!a.sign && !b.sign) {
        Integer result;
        result.sign = false;
        result.value = add_value(a.value, b.value);
        return result;
    }
}

Integer operator-(Integer &a, Integer &b) {
    return Integer();
}

Integer operator*(Integer &a, Integer &b) {
    return Integer();
}
