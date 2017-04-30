#ifndef INTEGER_H_
#define INTEGER_H_

#include <string>
#include <iostream>
#include <vector>

typedef char integer_digit_t;
typedef std::vector<integer_digit_t> integer_value_t;

class Integer {
 public:
    /* Constructors */
    Integer();
    Integer(const char*);
    /* Getter and setters */
    Integer& set_value(const char*);
    std::string get_value();
    /* Overload operators */
    Integer& operator=(const char*);
    friend std::ostream& operator<<(std::ostream &out, Integer &integer);
    friend std::istream& operator>>(std::istream &in, Integer &integer);
    friend Integer operator+(Integer &a, Integer &b);
    friend Integer operator-(Integer &a, Integer &b);
    friend Integer operator*(Integer &a, Integer &b);
    friend bool operator<(Integer &a, Integer &b);
    friend bool operator>(Integer &a, Integer &b);
    // friend Integer operator/(Integer &a, Integer &b);
 private:
    /* Private members */
    integer_value_t value;
    bool sign;
    /* Private methods */
    void arrange(); // Remove leading zeros from the value
};

#endif
