/*
  marries.cpp
  CS2124 - Sec A
  2023F
 */

#include <iostream>
#include <string>
using namespace std;

class Person {
    friend ostream& operator<<(ostream& os, const Person& rhs);

public:
    Person(const string& name) : name(name), spouse(nullptr) {}

    // john.marries(mary)
    //    void marries(Person betrothed) {
    //void marries(const Person& betrothed) {
    void marries(Person& betrothed) {
	spouse = &betrothed;
	betrothed.spouse = this; // this is a keyword. 
    }

private:
    string name;
    //    bool ring;
    //    string spouse;
    //Person spouse;
    Person* spouse;
};

int main() {
    Person john("John");
    Person mary("Mary");
    cout << john << endl
         << mary << endl;
    john.marries(mary);
    cout << john << endl
	 << mary << endl;

    int x = 17;
    cout << "address of x: " << &x << endl; // address of operator

    int* p = &x; // pointer variable
    // int *p = &x;
    // int * p = &x;
    cout << "address of x: " << &x << ", p: " << p << endl;

    cout << "x: " << x << ", *p: " << *p << endl; // dereference operator

    *p = 42;
    cout << "x: " << x << ", *p: " << *p << endl; // dereference operator

    int* q;
    cout << "q: " << q << endl; // q is undefined;
    int* r = nullptr;
    cout << "r: " << r << endl; // r is nullptr


    cout << "&john: " << &john << ", &mary: " << &mary << endl;

    cout << sizeof(p) << ", " << sizeof(Person) << endl;

}

ostream& operator<<(ostream& os, const Person& rhs) {
    os << "Name: " << rhs.name << ", spouse address: " << rhs.spouse;
    if (rhs.spouse == nullptr) {
	os << ", Single";
    } else {
	os << ", Married to: " << *rhs.spouse; // Infinite recursion
    }

    return os;
}
