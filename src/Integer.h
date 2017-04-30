#ifndef INTEGER_H_
#define INTEGER_H_

#include <string>
#include <iostream>
#include <vector>

typedef char integer_digit_t;

class Integer {
 public:
    Integer();
    Integer(const char*);
    Integer& set_value(const char*);
    std::string get_value();
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
    std::vector<integer_digit_t> value;
    bool sign;
    void arrange();
};

#endif
