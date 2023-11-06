/*
    Adonis Garcia
    testRational.cpp
	CS2124
	Implement the class Rational, so that the following program works.
 */

#include <iostream>

// If time allows use separate compilation, otherwise just define the
// class below with the methods / functions defined after main.
// #include "Rational.h"

using namespace std;

// If time allows after implementing separate compilation, then wrap
// the class in a namespace.
// using namespace CS2124;

class Rational {
    friend ostream& operator<<(ostream& os, const Rational& rhs);

    friend istream& operator>>(istream& is, Rational& rhs);

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

int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : " 
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}

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
