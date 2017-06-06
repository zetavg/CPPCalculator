#ifndef DECIMAL_H_
#define DECIMAL_H_

#include <string>
#include <iostream>
#include <vector>

typedef char decimal_digit_t;
typedef std::vector<decimal_digit_t> decimal_value_t;

class Decimal {
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
    // friend Decimal operator/(Decimal &a, Decimal &b);
 private:
    /* Private members */
    bool sign;
    decimal_value_t molecular, denominator;
    /* Private methods */
    void arrange(); // Remove leading zeros from the value
    void simplify(); // Make fraction in lowest terms
};

#endif
