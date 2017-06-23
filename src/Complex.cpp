#include "Complex.h"

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

Complex::Complex() {
    set_value("null");
}

Complex::Complex(const char *number) {
    set_value(number);
}

Complex::Complex(const Complex &complex) {
    copy_value_from(complex);
}

/*
 * Getter and setters
 */

Complex& Complex::set_value(const char *number) {
    sign = true;
    value.clear();
    denominator.clear();
    i_sign = true;
    i_value.clear();
    i_denominator.clear();

    if (strcmp(number, "null") != 0) {
        int last, i_last;
        for (last = 0; number[last] != '\0' && number[last] != '+'; ++last) continue;
        for (i_last = last; number[i_last] != '\0' && number[i_last] != 'i'; ++i_last) continue;
        int state = 0, i_state = 0;

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

        // i part

        for (int i = i_last - 1; i > last; --i) {
            if (number[i] == '-') {
                i_sign = false;
                continue;
            }
            if (number[i] == '.') {
                i_state = 1;
                continue;
            }
            if (number[i] == '/') {
                i_state = 2;
                i_value.swap(i_denominator);
                i_value.clear();
                continue;
            }

            int n = number[i] - 48;
            if (n < 0 && n > 9) continue;

            i_value.push_back(n);

            if (i_state == 0) {
                i_denominator.push_back(0);
            }
        }

        if (i_state == 0) {
            i_denominator.clear();
            i_denominator.push_back(1);
        } else if (i_state == 1) {
            i_denominator.push_back(1);
        }

        if (i_value.empty()) {
            i_value.push_back(0);
            i_denominator.push_back(1);
        }

        arrange();
    }

    return *this;
}

std::string Complex::get_value() {
    std::string str;

    if (value.empty()) {
        str += "null";
        return str;
    } else if (value.size() == 1 && value.at(0) == 0) {
        str += "0.0";
    } else if (denominator.size() == 1 && denominator.at(0) == 1) {
        if (!sign) str.push_back('-');
        print_raw_value_to_string(value, str);
        str.push_back('.');
        str.push_back('0');
    } else {
        // calculate the value in complex format
        number_value_t molecular(value);
        number_value_t result_integer_part, decimal_part;
        result_integer_part.push_back(0);

        while (compare_raw_value(molecular, denominator) >= 0) {
            molecular = substractdown_raw_value(molecular, denominator);
            raw_value_plus(result_integer_part, 1);
        }

        for (int i = 0; i < 10; ++i) {
            if (molecular.size() == 1 && molecular.at(0) == 0) break;
            molecular.insert(molecular.begin(), 0);
            int d = 0;
            while (compare_raw_value(molecular, denominator) >= 0) {
                molecular = substractdown_raw_value(molecular, denominator);
                ++d;
            }
            decimal_part.push_back(d);
        }

        decimal_part.push_back(0);
        arrange_raw_value(decimal_part);
        std::reverse(decimal_part.begin(), decimal_part.end());

        if (!sign) str.push_back('-');
        print_raw_value_to_string(result_integer_part, str);
        str.push_back('.');
        print_raw_value_to_string(decimal_part, str);
    }

    // i part

    if (i_sign) {
        str += "+";
    } else {
        str += "-";
    }

    if (i_value.empty()) {
        str += "null";
    } else if (i_value.size() == 1 && i_value.at(0) == 0) {
        str += "0.0";
    } else if (i_denominator.size() == 1 && i_denominator.at(0) == 1) {
        print_raw_value_to_string(i_value, str);
        str.push_back('.');
        str.push_back('0');
    } else {
        // calculate the i_value in complex format
        number_value_t molecular(i_value);
        number_value_t result_integer_part, decimal_part;
        result_integer_part.push_back(0);

        while (compare_raw_value(molecular, i_denominator) >= 0) {
            molecular = substractdown_raw_value(molecular, i_denominator);
            raw_value_plus(result_integer_part, 1);
        }

        for (int i = 0; i < 10; ++i) {
            if (molecular.size() == 1 && molecular.at(0) == 0) break;
            molecular.insert(molecular.begin(), 0);
            int d = 0;
            while (compare_raw_value(molecular, i_denominator) >= 0) {
                molecular = substractdown_raw_value(molecular, i_denominator);
                ++d;
            }
            decimal_part.push_back(d);
        }

        decimal_part.push_back(0);
        arrange_raw_value(decimal_part);
        std::reverse(decimal_part.begin(), decimal_part.end());

        print_raw_value_to_string(result_integer_part, str);
        str.push_back('.');
        print_raw_value_to_string(decimal_part, str);
    }

    str += "i";

    return str;
}

Complex& Complex::copy_value_from(const Complex &reference) {
    sign = reference.sign;
    value = number_value_t(reference.value);
    denominator = number_value_t(reference.denominator);
    i_sign = reference.i_sign;
    i_value = number_value_t(reference.i_value);
    i_denominator = number_value_t(reference.i_denominator);
    return *this;
}

/*
 * Overload operators
 */

Complex& Complex::operator=(const char *number) {
    set_value(number);
    return *this;
}

Complex& Complex::operator=(const Complex &complex) {
    copy_value_from(complex);
    return *this;
}

std::ostream& operator<<(std::ostream &out, Complex complex) {
    out << complex.get_value();
    return out;
}

std::istream& operator>>(std::istream &in, Complex &complex) {
    std::string str;
    in >> str;
    complex.set_value(str.c_str());

    return in;
}

Complex operator+(Complex &a, Complex &b) {
    Complex result;

    // Make the denominator same
    number_value_t result_denominator = Complex::multiply_raw_value(a.denominator, b.denominator);

    // Calculate the values after multiplication
    number_value_t a_value_after_multiplication = Complex::multiply_raw_value(a.value, b.denominator);
    number_value_t b_value_after_multiplication = Complex::multiply_raw_value(b.value, a.denominator);

    if (a.sign && b.sign) {
        // simply add the values if both a and b are both positive
        result.sign = true;
        result.value = Complex::addup_raw_value(a_value_after_multiplication, b_value_after_multiplication);
        result.denominator = result_denominator;

    } else if (!a.sign && !b.sign) {
        // add the values and set the sign to negative if both a and b are both negative
        result.sign = false;
        result.value = Complex::addup_raw_value(a_value_after_multiplication, b_value_after_multiplication);
        result.denominator = result_denominator;

    } else {
        // we need to compare the values and perform an substraction
        number_value_t positive_value_after_multiplication, negative_value_after_multiplication;

        // find the positive and negative complex
        if (a.sign && !b.sign) {
            positive_value_after_multiplication = a_value_after_multiplication;
            negative_value_after_multiplication = b_value_after_multiplication;
        } else {
            positive_value_after_multiplication = b_value_after_multiplication;
            negative_value_after_multiplication = a_value_after_multiplication;
        }

        // compare the values to decide what to do
        int comparing_result = Complex::compare_raw_value(positive_value_after_multiplication, negative_value_after_multiplication);

        if (comparing_result > 0) {
            // the positive value is larger then the negative value
            result.sign = true;
            result.value = Complex::substractdown_raw_value(positive_value_after_multiplication, negative_value_after_multiplication);
            result.denominator = result_denominator;
            result.arrange();
        } else if (comparing_result < 0) {
            // the negative value is larger then the positive value
            result.sign = false;
            result.value = Complex::substractdown_raw_value(negative_value_after_multiplication, positive_value_after_multiplication);
            result.denominator = result_denominator;
            result.arrange();
        } else {
            // the two values are same
            result.value.push_back(0);
            result.denominator.push_back(0);
        }
    }

    // i part

    // Make the i_denominator same
    number_value_t i_result_denominator = Complex::multiply_raw_value(a.i_denominator, b.i_denominator);

    // Calculate the values after multiplication
    number_value_t i_a_value_after_multiplication = Complex::multiply_raw_value(a.i_value, b.i_denominator);
    number_value_t i_b_value_after_multiplication = Complex::multiply_raw_value(b.i_value, a.i_denominator);

    if (a.i_sign && b.i_sign) {
        // simply add the values if both a and b are both positive
        result.i_sign = true;
        result.i_value = Complex::addup_raw_value(i_a_value_after_multiplication, i_b_value_after_multiplication);
        result.i_denominator = i_result_denominator;

    } else if (!a.i_sign && !b.i_sign) {
        // add the values and set the i_sign to negative if both a and b are both negative
        result.i_sign = false;
        result.i_value = Complex::addup_raw_value(i_a_value_after_multiplication, i_b_value_after_multiplication);
        result.i_denominator = i_result_denominator;

    } else {
        // we need to compare the values and perform an substraction
        number_value_t positive_value_after_multiplication, negative_value_after_multiplication;

        // find the positive and negative complex
        if (a.i_sign && !b.i_sign) {
            positive_value_after_multiplication = i_a_value_after_multiplication;
            negative_value_after_multiplication = i_b_value_after_multiplication;
        } else {
            positive_value_after_multiplication = i_b_value_after_multiplication;
            negative_value_after_multiplication = i_a_value_after_multiplication;
        }

        // compare the values to decide what to do
        int comparing_result = Complex::compare_raw_value(positive_value_after_multiplication, negative_value_after_multiplication);

        if (comparing_result > 0) {
            // the positive i_value is larger then the negative i_value
            result.i_sign = true;
            result.i_value = Complex::substractdown_raw_value(positive_value_after_multiplication, negative_value_after_multiplication);
            result.i_denominator = i_result_denominator;
            result.arrange();
        } else if (comparing_result < 0) {
            // the negative i_value is larger then the positive i_value
            result.i_sign = false;
            result.i_value = Complex::substractdown_raw_value(negative_value_after_multiplication, positive_value_after_multiplication);
            result.i_denominator = i_result_denominator;
            result.arrange();
        } else {
            // the two values are same
            result.i_value.push_back(0);
            result.i_denominator.push_back(0);
        }
    }

    return result;
}

Complex operator-(Complex &complex) {
    Complex result(complex);
    result.sign = !complex.sign;
    result.i_sign = !complex.i_sign;
    return result;
}

Complex operator-(Complex &a, Complex &b) {
    Complex negative_b = -b;
    return (a + negative_b);
}

Complex operator*(Complex &a, Complex &b) {
    Complex result;
    result.value = Complex::multiply_raw_value(a.value, b.value);
    result.denominator = Complex::multiply_raw_value(a.denominator, b.denominator);
    result.i_value = Complex::multiply_raw_value(a.i_value, b.i_value);
    result.i_denominator = Complex::multiply_raw_value(a.i_denominator, b.i_denominator);
    result.sign = a.sign == b.sign;
    result.i_sign = a.i_sign == b.i_sign;
    return result;
}

Complex operator/(Complex &a, Complex &b) {
    Complex result;
    result.value = Complex::multiply_raw_value(a.value, b.denominator);
    result.denominator = Complex::multiply_raw_value(a.denominator, b.value);
    result.sign = a.sign == b.sign;
    result.i_value = Complex::multiply_raw_value(a.i_value, b.i_denominator);
    result.i_denominator = Complex::multiply_raw_value(a.i_denominator, b.i_value);
    result.i_sign = a.i_sign == b.i_sign;
    result.arrange();
    return result;
}

Complex operator+(Complex &a, Integer &b) {
    Complex cb = b.get_value().c_str();
    return a + cb;
}
Complex operator-(Complex &a, Integer &b) {
    Complex cb = b.get_value().c_str();
    return a + cb;
}
Complex operator*(Complex &a, Integer &b) {
    Complex cb = b.get_value().c_str();
    return a + cb;
}
Complex operator/(Complex &a, Integer &b) {
    Complex cb = b.get_value().c_str();
    return a + cb;
}
Complex operator+(Integer &a, Complex &b) {
    Complex ca = a.get_value().c_str();
    return ca + b;
}
Complex operator-(Integer &a, Complex &b) {
    Complex ca = a.get_value().c_str();
    return ca + b;
}
Complex operator*(Integer &a, Complex &b) {
    Complex ca = a.get_value().c_str();
    return ca + b;
}
Complex operator/(Integer &a, Complex &b) {
    Complex ca = a.get_value().c_str();
    return ca + b;
}

Complex operator+(Complex &a, Decimal &b) {
    Complex cb = b.get_value().c_str();
    return a + cb;
}
Complex operator-(Complex &a, Decimal &b) {
    Complex cb = b.get_value().c_str();
    return a + cb;
}
Complex operator*(Complex &a, Decimal &b) {
    Complex cb = b.get_value().c_str();
    return a + cb;
}
Complex operator/(Complex &a, Decimal &b) {
    Complex cb = b.get_value().c_str();
    return a + cb;
}
Complex operator+(Decimal &a, Complex &b) {
    Complex ca = a.get_value().c_str();
    return ca + b;
}
Complex operator-(Decimal &a, Complex &b) {
    Complex ca = a.get_value().c_str();
    return ca + b;
}
Complex operator*(Decimal &a, Complex &b) {
    Complex ca = a.get_value().c_str();
    return ca + b;
}
Complex operator/(Decimal &a, Complex &b) {
    Complex ca = a.get_value().c_str();
    return ca + b;
}

/*
 * Private methods
 */

void Complex::arrange() {
    value = Complex::arrange_raw_value(value);
    denominator = Complex::arrange_raw_value(denominator);
    i_value = Complex::arrange_raw_value(i_value);
    i_denominator = Complex::arrange_raw_value(i_denominator);
}
