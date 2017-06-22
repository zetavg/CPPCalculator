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
    // virtual NumberObject& set_value(const char*) = 0;
    // virtual std::string get_value() = 0;
    // virtual NumberObject& copy_value_from(const NumberObject &) = 0;
 // protected:
    /* Private members */
    bool sign;
    number_value_t value;
    number_value_t denominator;
};

#endif
