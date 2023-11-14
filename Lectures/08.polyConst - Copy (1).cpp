/*
  08.polyConst
  Sec C - 23S
*/

#include <iostream>
using namespace std;

class Base {
public:
    Base() {
	this->foo();    // should do polymorphism but compiler chooses not to since this has potential to cause issues
                    // as a result, polymorphism is disabled inside the constructor of the base class
    }
    virtual void foo() const { cout << "Base\n"; }
    void display() {
	this->foo();
    }
};

class Derived : public Base {
public:
    Derived(int n) : Base(), x(n) {}
    void foo() const { cout << "Derived: x == " << x << endl; } // x not defined yet when base const is called
private:
    int x;
};

int main() {
    Derived der(17);
    der.display();
}
