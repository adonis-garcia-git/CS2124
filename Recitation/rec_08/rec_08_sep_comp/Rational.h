#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

namespace CS2124 {

class Rational {
    friend std::ostream& operator<<(std::ostream& os, const Rational& rhs);

    friend std::istream& operator>>(std::istream& is, Rational& rhs);

    friend bool operator==(const Rational& lhs, const Rational& rhs);

    friend bool operator<(const Rational& lhs, const Rational& rhs);

    int greatestCommonDivisor(int x, int y);

    void normalize();

public:
    Rational(int n = 0, int d = 1);

    Rational& operator+=(const Rational& other);

    Rational& operator++();

    Rational operator++(int);

    explicit operator bool() const;

private:
    int numerator;
    int denominator;
};

Rational operator+(const Rational& lhs, const Rational& rhs);

Rational& operator--(Rational& aRational);

Rational operator--(Rational& aRational, int);

bool operator!=(const Rational& lhs, const Rational& rhs);

bool operator<=(const Rational& lhs, const Rational& rhs);

bool operator>(const Rational& lhs, const Rational& rhs);

bool operator>=(const Rational& lhs, const Rational& rhs);

}

#endif
