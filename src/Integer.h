#ifndef INTEGER_H_
#define INTEGER_H_

#include <string>
#include <iostream>

class Integer {
 public:
    Integer();
    Integer(std::string number);
    Integer& set_value(std::string);
    std::string get_value();
    friend std::ostream& operator<<(std::ostream &out, Integer &integer);
    friend std::istream& operator>>(std::istream &in, Integer &integer);
    friend Integer operator+(Integer &a, Integer &b);
    friend Integer operator-(Integer &a, Integer &b);
    friend Integer operator*(Integer &a, Integer &b);
    // friend Integer operator/(Integer &a, Integer &b);
 private:
    int value;
    bool is_null;
};

#endif
