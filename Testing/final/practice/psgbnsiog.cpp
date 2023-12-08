#include <iostream>
using namespace std;

// class Base {
// public:
//     virtual void foo(Base b) { cout << "Base::foo(Base)\n"; }
// };

// class Derived : public Base {
// public:
//     void foo(Base b) { cout << "Derived::foo(Derived)\n"; }
// };

// int main() {
//     Derived der;
//     Base base = der;    // Line A
//     base.foo(der);      // Line B
//     der.foo(der);       // Line C
// }

// class B {
// public:
//     B(int val = 42) : n(val) {}
//     virtual void foo() const { cout << "B"; }
// private:
//     int n;
// };

// class A {
// public:
//     void foo() { cout << "A"; }
// private:
//     B someB;
// };

// int main() {
//     A a;
//     a.foo();
// }

// #include <iostream>
// #include <vector>
// #include <algorithm>

// int main() {
//     std::vector<int> v { 6, 42, 28, 17, 16, 49 };
//     std::cout << *std::find_if(v.begin() + 1, v.end(),
//                                 [](int val) { return val % 2 == 0; })
//               << std::endl;
// }

// #include <iostream>
// #include <string>

// class Pet {
// public:
//     Pet(std::string name) : name(name) {}
//     void display() { std::cout << name << ' '; }

// protected:
//     void setName(std::string name) { this->name = name; }

// private:
//     std::string name;
// };

// class Cat : public Pet {
// public:
//     Cat(std::string name) : Pet(name) {}
// };

// class Dog : public Pet {
// public:
//     Dog() : Pet("ruff") {}

//     void setCatName(Cat& rhs) {
//         rhs.setName("Mehitabel"); // A
//     }

//     void setDogName(Dog& rhs) {
//         rhs.setName("Fido"); // B
//     }
// };

// int main() {
//     Cat felix("Felix");
//     Dog rover;
//     Dog fido;

//     fido.setCatName(felix); // This line will not compile
//     felix.display();
//     fido.setDogName(fido);
//     fido.display();
// }

// #include <iostream>

// class Base {
// public:
//     virtual void foo() { std::cout << " - Base::foo()\n"; }
// };

// class Derived : public Base {
// public:
//     virtual void foo() { std::cout << " - Derived::foo()\n"; }
// };

// void func(Base& arg) {
//     std::cout << "func(Base)";
//     arg.foo();
// }

// void func(Derived& arg) {
//     std::cout << "func(Derived)";
//     arg.foo();
// }

// void otherFunc(Base& arg) {
//     func(arg);
// }

// int main() {
//     Derived d;
//     otherFunc(d);
// }

// #include <iostream>

// class P1 {
// public:
//     void whoAmI() { std::cout << "P1"; }
// };

// class P2 {
// public:
//     void whoAmI() { std::cout << "P2"; }
// };

// class Child : public P2, public P1 {
//     // Inherits from both P2 and P1
// };

// int main() {
//     Child c;
//     c.whoAmI();
// }

void func(const int& something) {
    const int* p = &something;
    *p = 17;
}

int main(){}




