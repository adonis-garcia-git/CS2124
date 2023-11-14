/*
  09.polyNonMember.cpp
  Inclass Base
*/

#include <iostream>
using namespace std;

class Base {
public:
    virtual void display(ostream& os) const {
	os << "Base";
    }
};

ostream& operator<<(ostream& os, const Base& rhs) {
    //os << "Base";
    rhs.display(os);
    return os;
}

class Derived : public Base {
public:
    void display(ostream& os) const {
	os << "Derived";
    }
 };

// ostream& operator<<(ostream& os, const Derived& rhs) {
//     //os << "Derived"; 
//     rhs.derived(os);
//     return os;
// }

void func(const Base& base) {
    cout << base << endl;
    //operator<<(cout, base)
    //cout.operator<<(base);
}

int main() {
    Derived der;
    cout << der << endl;
    operator<<(cout, der);
    
    func(der);
}
