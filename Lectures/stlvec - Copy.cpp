/*
  stlvec.cpp
  John Sterling
  Demonstrate certain implementation dependent features of the vector
 */

#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> v;
    cout << "What does a default initialized vector look like?\n";
    cout << "v.size(): " << v.size() << ", v.capacity(): " << v.capacity()
	 << ", v.data(): " << v.data() << endl;

    cout << "What happens if we pop_back an empty vector?\n";
    cout << "Empty vector: v.size(): " << v.size() << " ";
    v.pop_back();
    cout << "; and after pop_back: v.size(): " << v.size() << endl;
    
    cout << "starting with a fresh vector, v2, since v is broken\n";
    vector<int> v2;
    cout << "Initially, v2.capacity() = " << v2.capacity() << endl;
    for (int i = 1; i <= 20; ++i) {
	v2.push_back(i);
	cout << "After adding: " << i << ", v2.size() = " << v2.size() 
	     << ", v2.capacity() = " << v2.capacity() << endl;
    }

    while (!v2.empty()) {
	int val = v2.back();
	v2.pop_back();
	cout << "After removing: " << val << ", v2.size() = " << v2.size()
	     << ", v2.capacity() = " << v2.capacity() << endl;
    }

    v2.clear();
    cout << "\nAfter clearing: v2.size() = " << v2.size()
	 << ", v2.capacity() = " << v2.capacity() << endl;
}

// vector size is completely dependent on number of elements in the vector
// when size exceeds capacity, capacity increase by half of current capacity
// when removing elements, size decreases but capacity stays the same
// when clearing vector, capacity still doesn't change
