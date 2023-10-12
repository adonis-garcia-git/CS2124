/*
  Copy Control (start)
  CS2124 - 2023 Fall
  Inclass Sec A
 */

#include <iostream>
using namespace std;

// Thing class has just one field, a pointer an an int on the heap
class Thing {
    friend ostream& operator<<(ostream& os, const Thing& rhs);
public:
    Thing(int x) { p = new int(x); }
    void setValue(int val) { *p = val; }
    int getValue() const { return *p; }
    void cleanUp() {
	//p = nullp[tr;  // NOOOOO!
	delete p; // always delete before setting to nullptr
	p = nullptr; // Ok
    }
    ~Thing() { // Destructor
	delete p;
    }

    // copy constructor
    //Thing(Thing anotherThing) {
    Thing(const Thing& anotherThing) {
	//int theValue = anotherThing.getValue();
	int theValue = *anotherThing.p;
	p = new int(theValue);
    }

private:
    int* p;
};

// ===========  Client Code ==============

void doNothing(Thing something) {}
//void doNothing(const Thing& something) {}

Thing anotherFunc(Thing something) { // Copy constructor

    Thing yat(something); // Copy constructor

    Thing yat2 = something; // Copy constructor

    Thing yat3(42);

    yat = yat3;
    //    operator=(yat, yat3);  // But NOOOOO
    yat.operator=(yat3); // Right!

    return something; // Copy constructor
}

void simpleFunc() {
    Thing aThing(17);
    cout << aThing << endl;
    //delete aThing.p;
    //    aThing.cleanUp();

    doNothing(aThing);

    

}

int main() {
    simpleFunc();
}

ostream& operator<<(ostream& os, const Thing& rhs) { 
    os << *rhs.p;  // No arrow operator?
    return os;
}
