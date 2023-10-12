/*
  Copy Control (start)
  CS2124 - 2023 Fall
  Inclass Sec B
 */

#include <iostream>
using namespace std;

// Thing class has just one field, a pointer to an int on the heap
class Thing {
    friend ostream& operator<<(ostream& os, const Thing& rhs);
public:
    Thing(int x) { p = new int(x); }
    void setValue(int val) { *p = val; }
    int getValue() const { return *p; }

    //
    // Copy control / BIG 3
    //
    //void cleanUp() { delete p; }
    ~Thing() { delete p; } // destructor

    //Thing(Thing rhs) {
    Thing(const Thing& rhs) { // copy constructor
	//int val = *rhs.p;
	// int* intPtr = new int(val);
	// this->p = intPtr;

	//p = new int(val);
	p = new int(*rhs.p);
    }

    // Assignment operator
    //   thingA = thingB;
    //   thingA.operator=(thingB);  // Assignment operator
    Thing& operator=(const Thing& rhs) {
	// 0. self assignment
	if (this != &rhs) {
	    //void operator=(const Thing& rhs) {
	    // 1. prevent the memory leak
	    //    Free up the lhs's space
	    delete p;

	    // 2. Allocate and copy
	    p = new int(*rhs.p);
	}

	// 3. What to return?
	return *this;
    }

private:
    int* p;
};

Thing anotherFunc(Thing something) { // pass-by-value uses C.C.
    Thing thingOne(42);
    Thing thingTwo(thingOne);  // C.C.
    vector<Thing> things;
    things.push_back(thingOne); // C.C.
    for (Thing val : things) {  // C.C.
    }
    Thing thingThree = thingOne; // C.C

    something = thingThree; // not a C.C.

    return something; // C.C
}

void vaf() {
    Thing thingA(17);
    Thing thingB(42);
    thingA = thingB;
    //operator=(thingA, thingB);
    //thingA.operator=(thingB);  // Assignment operator
}

// ========== Client Code =========
void doNothing(Thing something) {}

void simpleFunc() {
    Thing aThing(17);
    cout << aThing << endl;

    doNothing(aThing);

    //aThing.cleanUp();
}

int main() {
    simpleFunc();
}

ostream& operator<<(ostream& os, const Thing& rhs) { 
    os << *rhs.p;
    return os;
}
