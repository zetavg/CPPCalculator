#ifndef INTEGER_H_
#define INTEGER_H_

#include <string>
#include <iostream>
#include <vector>

#include "base/NumberObject.h"

class Integer : public NumberObject {
 public:
    /* Constructors */
    Integer();
    Integer(const char*);
    Integer(const Integer &);
    /* Getter and setters */
    Integer& set_value(const char*);
    std::string get_value();
    Integer& copy_value_from(const NumberObject &);
    /* Overload operators */
    Integer& operator=(const char*);
    Integer& operator=(const Integer &);
    friend std::ostream& operator<<(std::ostream &out, Integer integer);
    friend std::istream& operator>>(std::istream &in, Integer &integer);
    friend Integer operator-(Integer &integer);
    friend Integer operator+(Integer a, Integer b);
    friend Integer operator-(Integer a, Integer b);
    friend Integer operator*(Integer a, Integer b);
    friend bool operator<(Integer &a, Integer &b);
    friend bool operator>(Integer &a, Integer &b);
    // friend Integer operator/(Integer &a, Integer &b);
 private:
    /* Private methods */
    void arrange(); // Remove leading zeros from the value
};

#endif
