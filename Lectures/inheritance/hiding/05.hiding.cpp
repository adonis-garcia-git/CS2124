/*
  5.hiding.cpp
  der.foo(17) calls Base::foo(int) through code reuse, i.e. method inheritance
  Inclass Base 
*/

#include <iostream>
using namespace std;

class Base {
public:
    virtual void foo(int n) const { cout << "Base::foo(n)\n"; }
};

class Derived : public Base {
public:
    // Hides the Base::foo
    void foo() const { cout << "Derived::foo()\n"; }
    //void foo(int n) { Base::foo(n); } // wrapper
    using Base::foo;
};
class DerivedV2 : public Base {
public:
    
};

int main() {
    Derived der;
    der.foo(17); // code reuse
    //der.Base::foo(17);
    der.foo();
    DerivedV2 derV2;
    derV2.foo(17); // code reuse
}
