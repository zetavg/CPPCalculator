#ifndef DECIMAL_H_
#define DECIMAL_H_

#include <string>
#include <iostream>
#include <vector>

#include "headers/NumberObject.h"

typedef char decimal_digit_t;
typedef std::vector<decimal_digit_t> decimal_value_t;

class Decimal : public NumberObject {
 public:
    /* Constructors */
    Decimal();
    Decimal(const char*);
    Decimal(const Decimal &);
    /* Getter and setters */
    Decimal& set_value(const char*);
    std::string get_value();
    Decimal& copy_value_from(const Decimal &);
    /* Overload operators */
    Decimal& operator=(const char*);
    Decimal& operator=(const Decimal &);
    friend std::ostream& operator<<(std::ostream &out, Decimal &decimal);
    friend std::istream& operator>>(std::istream &in, Decimal &decimal);
    friend Decimal operator+(Decimal &a, Decimal &b);
    friend Decimal operator-(Decimal &decimal);
    friend Decimal operator-(Decimal &a, Decimal &b);
    friend Decimal operator*(Decimal &a, Decimal &b);
    friend bool operator<(Decimal &a, Decimal &b);
    friend bool operator>(Decimal &a, Decimal &b);
    friend Decimal operator/(Decimal &a, Decimal &b);
 private:
    /* Private methods */
    void arrange(); // Remove leading zeros from the value
    void simplify(); // Make fraction in lowest terms
 public:
    /* Value calculation helpers */
    static decimal_value_t raw_value_gcd(decimal_value_t &a, decimal_value_t &b);
    static decimal_value_t raw_value_remainder(decimal_value_t &a, decimal_value_t &b);
};

#endif
