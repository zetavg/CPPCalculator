#include "Integer.h"

#include <string>
#include <iostream>

Integer::Integer() {
    set_value("null");
}

Integer::Integer(std::string number) {
    set_value(number);
}

Integer& Integer::set_value(std::string number) {
    if (number.compare("null") == 0) {
        is_null = true;
    } else {
        is_null = false;
        value = std::stoi(number);
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

std::ostream& operator<<(std::ostream &out, Integer &integer) {
    out << integer.get_value();
    return out;
}

std::istream& operator>>(std::istream &in, Integer &integer) {
    std::string value;
    in >> value;
    integer.set_value(value);

    return in;
}

Integer operator+(Integer &a, Integer &b) {
    return Integer(std::to_string(a.value + b.value));
}

Integer operator-(Integer &a, Integer &b) {
    return Integer(std::to_string(a.value - b.value));
}

Integer operator*(Integer &a, Integer &b) {
    return Integer(std::to_string(a.value * b.value));
}
