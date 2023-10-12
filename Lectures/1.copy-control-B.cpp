/*
  Basics of Copy Control
  1.copy-control-B.cpp
 */

#include <iostream>
using namespace std;

class Thing {
    friend ostream& operator<<(ostream& os, const Thing& rhs);
public:
    Thing(int x, const string& s) : s(s) {
	p = new int(x);
    }

    void setValue(int val) { *p = val; }
    int getValue() const { return *p; }

    //
    // Copy Control / Big 3

    //void cleanup() { delete p; }
    ~Thing() { delete p; } // destructor

    // Copy Constructor
    Thing(const Thing& anotherThing) : s(anotherThing.s) { // prevents double delete when pass by value is used
        p = new int(*anotherThing.p); // deep copy // why can't we do this in list initialization
	//s = anotherThing.s; // MIght lose five points
    }
                        
    // lhs = rhs
    // lhs.operator=(rhs)
    Thing& operator=(const Thing& rhs) {
        if (this != &rhs) { // 0. self-assignment check
            // 1. Free up whatever heap space the lhs is holding (desturctor)
            delete p;
            // Copy constructor code
            // 2. allocate
            // 3. copying
            p = new int(*rhs.p);
	    s = rhs.s;
        }
        // 4. return yourself
        return *this;
    }

private:
    int* p;
    string s;
};

ostream& operator<<(ostream& os, const Thing& rhs) {
    //return os << "Thing: " << *rhs.p;
    os << "Thing: " << *rhs.p << ", s: " << rhs.s;
    return os;
}

// ===========  customer's code ==============

void doNothing(Thing x) {}

void simpleFunc() {
    Thing aThing(17, "John");
    doNothing(aThing); // copy constructor
    cout << aThing << endl;
    //aThing.cleanup(); // this is done by destructor

    Thing something(6, "Mary");

    aThing = something; // copy assignment constructor
    //operator=(aThing, something)
    //aThing.operator=(something);
}

int main() {
    simpleFunc();
    Thing* ptr = new Thing(100, "George");
    delete ptr;
}
