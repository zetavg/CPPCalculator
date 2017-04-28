#include "Integer.h"

#include <string>
#include <cstring>
#include <iostream>

Integer::Integer() {
    set_value("null");
}

Integer::Integer(const char *number) {
    set_value(number);
}

Integer& Integer::set_value(const char *number) {
    if (strcmp(number, "null") == 0) {
        is_null = true;
    } else {
        is_null = false;
        value = std::atoi(number);
    }

    return *this;
}

std::string Integer::get_value() {
    if (is_null) {
        return "null";
    } else {
        return std::to_string(this->value);
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

Integer operator+(Integer &a, Integer &b) {
    return Integer(std::to_string(a.value + b.value).c_str());
}

Integer operator-(Integer &a, Integer &b) {
    return Integer(std::to_string(a.value - b.value).c_str());
}

Integer operator*(Integer &a, Integer &b) {
    return Integer(std::to_string(a.value * b.value).c_str());
}
