#include "Rational.h"

using namespace std;

namespace CS2124 {

Rational operator+(const Rational& lhs, const Rational& rhs){
    Rational result(lhs);
    result += rhs;
    return result;
}

bool operator==(const Rational& lhs, const Rational& rhs){
    return (lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator);
}

bool operator<(const Rational& lhs, const Rational& rhs){
    return ((lhs.numerator * rhs.denominator) < (rhs.numerator * lhs.denominator));
}

Rational& operator--(Rational& aRational){
    aRational += -1;
    return aRational;
}

Rational operator--(Rational& aRational, int){
    Rational original(aRational);
    aRational += -1;
    return original;
}

bool operator!=(const Rational& lhs, const Rational& rhs){
    return (!(lhs==rhs));
}

bool operator<=(const Rational& lhs, const Rational& rhs){
    return (lhs < rhs || lhs == rhs);
}

bool operator>(const Rational& lhs, const Rational& rhs){
    return (!(lhs < rhs) && !(lhs == rhs));
}

bool operator>=(const Rational& lhs, const Rational& rhs){
    return (lhs > rhs || lhs == rhs);
}

ostream& operator<<(ostream& os, const Rational& rhs){
    os << rhs.numerator << "/" << rhs.denominator;
    return os;
};

istream& operator>>(istream& is, Rational& rhs){
    int n, d;
    char slash;
    is >> n >> slash >> d;

    if (d == 0){
        cout << "zero denominator error";
        return is;
    }

    rhs.numerator = n;
    rhs.denominator = d;
    rhs.normalize();
    return is;
}

int Rational::greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

void Rational::normalize(){
    if (denominator < 0){
        numerator *= -1;
        denominator *= -1;
    }

    int n = numerator;

    if (numerator < 0){
        n *= -1;
    }

    int gcd = greatestCommonDivisor(n, denominator);
    numerator /= gcd;
    denominator /= gcd;
}

Rational::Rational(int n, int d){
    if (d == 0){
        cout << "zero denominator error";
        return;
    }

    numerator = n;
    denominator = d;
    normalize();
}

Rational& Rational::operator+=(const Rational& other){
    numerator = numerator * other.denominator + other.numerator * denominator;
    denominator *= other.denominator;
    normalize();
    return *this;
}

Rational& Rational::operator++(){
    numerator += denominator;
    return *this;
}

Rational Rational::operator++(int){
    Rational original(*this);
    numerator += denominator;
    return original;
}

Rational::operator bool() const {
    return (numerator);
}

}
