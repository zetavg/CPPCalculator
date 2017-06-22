#ifndef NUMBER_OBJECT_H_
#define NUMBER_OBJECT_H_

#include <string>
#include <iostream>
#include <vector>

typedef char number_digit_t;
typedef std::vector<number_digit_t> number_value_t;

class NumberObject {
 public:
    /* Getter and setters */
    virtual NumberObject& set_value(const char*) = 0;
    virtual std::string get_value() = 0;
    // virtual NumberObject& copy_value_from(const NumberObject &) = 0;
    /* Overload operators */
    friend std::ostream& operator<<(std::ostream &out, NumberObject &number) {
        out << number.get_value();
        return out;
    }
    friend std::istream& operator>>(std::istream &in, NumberObject &number) {
        std::string value;
        in >> value;
        number.set_value(value.c_str());
        return in;
    }
    /* Raw member getters */
    bool get_raw_sign() const { return sign; }
    number_value_t get_raw_value() const { return value; }
    number_value_t get_raw_denominator() const { return denominator; }
 protected:
    /* Private members */
    bool sign;
    number_value_t value;
    number_value_t denominator;
 public:
    /* Value calculation helpers */
    static number_value_t addup_raw_value(number_value_t &a, number_value_t &b);
    static number_value_t substractdown_raw_value(number_value_t &a, number_value_t &b);
    static number_value_t multiply_raw_value(number_value_t &a, number_value_t &b);
    static int compare_raw_value(number_value_t &a, number_value_t &b);
    static number_value_t arrange_raw_value(number_value_t &v);
    static number_value_t raw_value_gcd(number_value_t &a, number_value_t &b);
    static number_value_t raw_value_remainder(number_value_t &a, number_value_t &b);
};

#endif
