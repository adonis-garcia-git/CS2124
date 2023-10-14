// testNoCopy.cpp
// 
// demonstrates how to prevent a class from being copyable
// both pre-c++11 and post.

#include <iostream>
#include <string>
using namespace std;

class CanCopy {
    friend ostream& operator<<(ostream& os, const CanCopy& rhs) { 
        os << "CanCopy: " << rhs.val;
        return os;
    }
public:
    CanCopy(const string& val) : val(val) {}
private:
    string val;
};

// Demonstrates pre-c++11 way of making a class uncopyable.
class CannotCopyA {
    friend ostream& operator<<(ostream& os, const CannotCopyA& rhs) { 
        os << "CannotCopyA: " << rhs.val;
        return os;
    }
public:
    CannotCopyA(const string& val) : val(val) {}
private:
    string val;

    // Copy constructor and assignment operator are 
    // private and not implemented
    CannotCopyA(const CannotCopyA& rhs);
    CannotCopyA& operator=(const CannotCopyA& rhs);
};

// Demonstrates c++11 way of making a class uncopyable.
class CannotCopyB {
    friend ostream& operator<<(ostream& os, const CannotCopyB& rhs) { 
        os << "CannotCopyB: " << rhs.val;
        return os;
    }
public:
    CannotCopyB(const string& val) : val(val) {}
    // Copy constructor and assignment operator are 
    // public but tagged with " = delete" in the prototype
    CannotCopyB(const CannotCopyB& rhs) = delete;
    CannotCopyB& operator=(const CannotCopyB& rhs) = delete;
private:
    string val;
};


int main() {
    CanCopy cc("fred");
    CanCopy cc2(cc);
    cout << cc << "; " << cc2 << endl;

    CannotCopyA cncA("fred");
    // CannotCopyA cncA2(cncA);
    // cout << cncA << "; " << cncA2 << endl;

    CannotCopyB cncB("fred");
    // CannotCopyB cncB2(cncB);
    // cout << cncB << "; " << cncB2 << endl;

}
