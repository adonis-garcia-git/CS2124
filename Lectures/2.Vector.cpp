/*
  Vector Class
  Demonstrates:
     Good example of copy control
     Dynamic arrays and pointer arithmetic
     Square bracket operator
     Implementation of an important data structure
  Sec Base
 */

#include <iostream>
using namespace std;

class Vector {
public:
    Vector() { // constructor
	theSize = 0;
	theCap = 0;
	data = nullptr;    // why here and not list initialization or variable initialization
    }
    // Vector(size_t size, int value = 0) {}

    // Copy control

    ~Vector() {
	//delete data; // BAD // why?
	delete [] data;
    }
    
    Vector(const Vector& rhs) {
	data = new int[rhs.theCap];  // dynamic array
	theSize = rhs.theSize;
	theCap = rhs.theCap;
	for (size_t index = 0; index < theSize; ++index) {
	    
	}
	
    }
    // Vector& operator=(const Vector& rhs);

    //    void push_back(int val);

    // size_t size() const;
    // void clear();
    // void pop_back();

    // Square brackets
    
private:
    size_t theSize;
    size_t theCap;
    int* data;
};


int main() {

    Vector v;  // Not templated.  Our Vector class can only hold ints.
    // v.push_back(17);
    // v.push_back(42);
    // v.push_back(6);
    // v.push_back(28);

    // Vector v2(v);
    // Vector v3;
    // v3 = v;

    // for (size_t i = 0; i < v.size(); ++i)
    //     cout << v[i] << endl;
    // v[0] = 100;

    // v = 17;
}

