/*
  final.cpp
  -jbs
 */


//
// Simple inheritance
//
class Base1 {};

class Derived1 : public Base1 {};


//
// Final class
//
// Defining a final class
class Base2 final {};

// Attempting inheritance with a final class
class Derived2 : public Base2 {};


//
// Final method
//
class Base3 {
public:
    // Defining a final method
    virtual void foo() {}
};

class Middle3 : public Base3 {
public:
    // Mark this override as final
    void foo() final {}
};

class Derived3 : public Middle3 {
public:
    // Attempting to override a final method
    void foo() {}
};

int main() {
    // The simple case
    Base1 b1;
    Derived1 d1;

    // Creating an instance of a final class
    Base2 b2;
    // But this class won't have compiled
    Derived2 d2;
    
    // Creating an instance of a base class 
    Base3 b3;
    // Creating an instance of a base class declares a method final
    Middle3 m3;
    // But this class won't have compiled
    Derived3 d3;
}
