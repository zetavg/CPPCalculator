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
    Integer(const Integer &);
    /* Getter and setters */
    Integer& set_value(const char*);
    std::string get_value();
    Integer& copy_value_from(const Integer &);
    /* Overload operators */
    Integer& operator=(const char*);
    Integer& operator=(const Integer &);
    friend std::ostream& operator<<(std::ostream &out, Integer &integer);
    friend std::istream& operator>>(std::istream &in, Integer &integer);
    friend Integer operator+(Integer &a, Integer &b);
    friend Integer operator-(Integer &integer);
    friend Integer operator-(Integer &a, Integer &b);
    friend Integer operator*(Integer &a, Integer &b);
    friend bool operator<(Integer &a, Integer &b);
    friend bool operator>(Integer &a, Integer &b);
    // friend Integer operator/(Integer &a, Integer &b);
 private:
    /* Private members */
    bool sign;
    integer_value_t value;
    /* Private methods */
    void arrange(); // Remove leading zeros from the value
 public:
    /* Value calculation helpers */
    static integer_value_t addup_raw_value(integer_value_t &a, integer_value_t &b);
    static integer_value_t substractdown_raw_value(integer_value_t &a, integer_value_t &b);
    static integer_value_t multiply_raw_value(integer_value_t &a, integer_value_t &b);
    static int compare_raw_value(integer_value_t &a, integer_value_t &b);
    static integer_value_t arrange_raw_value(integer_value_t &v);
};

#endif
