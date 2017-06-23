#ifndef COMPLEX_H_
#define COMPLEX_H_

#include <string>
#include <iostream>
#include <vector>

#include "base/NumberObject.h"
#include "Integer.h"
#include "Decimal.h"

class Complex : public NumberObject {
 public:
    /* Constructors */
    Complex();
    Complex(const char*);
    Complex(const Complex &);
    /* Getter and setters */
    Complex& set_value(const char*);
    std::string get_value();
    Complex& copy_value_from(const Complex &);
    /* Overload operators */
    Complex& operator=(const char*);
    Complex& operator=(const Complex &);
    friend std::ostream& operator<<(std::ostream &out, Complex complex);
    friend std::istream& operator>>(std::istream &in, Complex &complex);
    friend Complex operator-(Complex &complex);
    friend Complex operator+(Complex a, Complex b);
    friend Complex operator-(Complex a, Complex b);
    friend Complex operator*(Complex a, Complex b);
    friend Complex operator/(Complex a, Complex b);
    friend Complex operator+(Complex a, Integer b);
    friend Complex operator-(Complex a, Integer b);
    friend Complex operator*(Complex a, Integer b);
    friend Complex operator/(Complex a, Integer b);
    friend Complex operator+(Integer a, Complex b);
    friend Complex operator-(Integer a, Complex b);
    friend Complex operator*(Integer a, Complex b);
    friend Complex operator/(Integer a, Complex b);
    friend Complex operator+(Complex a, Decimal b);
    friend Complex operator-(Complex a, Decimal b);
    friend Complex operator*(Complex a, Decimal b);
    friend Complex operator/(Complex a, Decimal b);
    friend Complex operator+(Decimal a, Complex b);
    friend Complex operator-(Decimal a, Complex b);
    friend Complex operator*(Decimal a, Complex b);
    friend Complex operator/(Decimal a, Complex b);
    friend bool operator<(Complex &a, Complex &b);
    friend bool operator>(Complex &a, Complex &b);
 private:
    /* Private methods */
    void arrange(); // Remove leading zeros from the value
    void simplify(); // Make fraction in lowest terms
};

#endif
