#include <iostream>

using namespace std;

class Complex {
    //operator<< as a friend
    friend ostream& operator<<(ostream& os, const Complex& rhs){
        os << rhs.real;
        if (rhs.imag >= 0) os << "+";
        os << rhs.imag << "i";
        return os;
    }

    friend bool operator==(const Complex& lhs, const Complex& rhs);

public:
    Complex(double real = 0, double imag = 0) : real(real), imag(imag) {}

    // bool operator==(const Complex& rhs) const {
    //     return (real == rhs.real && imag == rhs.imag);
    // }

    // bool operator!=(const Complex& rhs) const { // not accessing private so just make it a function
    //     return (*this == rhs);
    // }

    Complex& operator+=(const Complex& rhs){
        real += rhs.real;
        imag += rhs.imag;
        return *this; 
    }

    Complex& operator++(){
        ++real;
        return *this;
    }

    Complex operator++(int){
        Complex original(*this);
        ++real;
        return original; // do not return reference (local obj)
    }

    explicit operator bool() const {
        // return real != 0 || imag != 0;
        return real || imag;
    }

private:
    double real;
    double imag;
};

int main() {
    Complex c1;
    Complex c2(17);
    Complex c3(3, -5);

    //Testing equality and inequality operators
    cout << "c1 ";
    if (c1 == c2) cout << "==";
    //c1.operator==(c2);
    //operator==(c1, c2);
    else cout << "!=";
    cout << " c2\n";

    //The above 4 line in one line
    cout << "c1 " << (c1 == c2 ? "==" : "!=") << " c2\n"; 
    // must be same type for both options
    // if results are two function calls, only one function gets called
    // review some keyword "explicit"

    Complex one(1);
    cout << "one " << (one == 1 ? "==" : "!=") << " 1" << endl;
    // one == 1
    // one.operator==(1)
    // one.operator==(Complex(1))

    cout << "one " << (1 == one ? "==" : "!=") << " 1" << endl;
    // 1 == one
    // 1.operator==(one) //

    cout << ++c1 << " " << endl; // add first then return
    // c1.operator++();
    
    cout << c1++ << " " << endl; // return first then add
    // c1.operator++(0); // differentiates with a 0


}

bool operator!=(const Complex& lhs, const Complex& rhs){
    return !(lhs == rhs);
}

bool operator==(const Complex& lhs, const Complex& rhs) { // lhs is int but compiler uses that as arg to make temp Complex
    return (lhs.real == rhs.real && lhs.imag == rhs.imag);
}

Complex operator+(const Complex& lhs, const Complex& rhs) { // can't return & since result is a local copy
    // Complex result;
    // result += lhs;
    // result += rhs;
    // return result;

    Complex result(lhs);
    result += rhs;
    return result;
}


