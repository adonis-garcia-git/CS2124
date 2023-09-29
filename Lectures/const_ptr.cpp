/*
  const_ptr.cpp
  
  explore how does the keyword const works together with pointers
*/

#include <iostream>
using namespace std;

struct Thing { int val; };


void foo(const Thing& aThing) {
    // 4. What kind of pointer can point to aThing?
    //p = &aThing; // What does p's type have to be?
    const Thing* p = &aThing; // What does p's type have to be?
}


int main() {
    int x = 17, y = 42;

    // 1. How can we define a pointer that CANNOT modify what it
    //    points at?
    //int* p = &x;
    const int* p = &x;
    //*p = 28;  // how can we prevent that?
    p = &y; // Ok

    // 2. how can we define a pointer that CAN ONLY ever point at
    //    one item which it was set to point to initially
    //int* q = &x;
    int* const q = &x;
    //q = &y; // how can we prevent that?

    // 3. What kind of pointer can point at a constant item?
    const int Z = 100;
    //Z = 200; // not allowed, of course;
    
    //int* r = &Z;
    const int* r = &Z;
    //*r = 100;  // how can we prevent that?
    
}
