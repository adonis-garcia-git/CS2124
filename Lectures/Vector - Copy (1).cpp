/*
  Vector Class
  Basic vector of ints
  Sec A - 23F
 */
#include <iostream>
using namespace std;

class Iterator {
    // != operator
    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
	return rhs.where != lhs.where;
    }
public:
    // constructor to store where
    Iterator(int* where) : where(where) {}

    // * operator
    //  *iter
    //  operator*(iter)
    //  iter.operator*();
    int& operator*() const {
	return *where;
    }

    // ++ operator
    Iterator& operator++() {
	++where;
	return *this;
    }

    // post-increment
    Iterator operator++(int dummy) {
	Iterator old(*this);
	++where;
	return old;
    }

private:
    int* where;
};

class Const_Iterator {
    // != operator
    friend bool operator!=(const Const_Iterator& lhs, const Const_Iterator& rhs) {
	return rhs.where != lhs.where;
    }
public:
    // constructor to store where
    Const_Iterator(int* where) : where(where) {}

    // * operator
    //  *iter
    //  operator*(iter)
    //  iter.operator*();
    int operator*() const {
	return *where;
    }

    // ++ operator
    Const_Iterator& operator++() {
	++where;
	return *this;
    }

    // post-increment
    Const_Iterator operator++(int dummy) {
	Const_Iterator old(*this);
	++where;
	return old;
    }

private:
    int* where;
};

class Vector {
public:
    
    explicit Vector(size_t howMany=0, int val=0)
    {
        theSize = howMany;
        theCapacity = howMany;
        data = new int[howMany];
        for (size_t i = 0; i < theSize; ++i) {
            data[i] = val;
        }
    }

    // Copy control
    //   Destructor
    ~Vector() {
        delete [] data;
    }

    //   Copy Constructor
    Vector(const Vector& rhs) {
        theSize = rhs.theSize;
        theCapacity = rhs.theCapacity;
        data = new int[theCapacity];
        for (size_t i = 0; i < theSize; ++i) {
            data[i] = rhs.data[i];
        }
    }

    //   Assignement Operator
    Vector& operator=(const Vector& rhs) {
        if (this != &rhs) {
            // Free up the old (destructor)
            delete [] data;
            // Allocate new
            data = new int[rhs.theCapacity];
            // Copy all the stuff
            theSize = rhs.theSize;
            theCapacity = rhs.theCapacity;
            for (size_t i = 0; i < theSize; ++i) {
                data[i] = rhs.data[i];
            }
        }
        // Return ourselves
        return *this;
    }


    void push_back(int val) {
        if (theSize == theCapacity) {
            if (theCapacity == 0) {
                delete [] data;
                data = new int[1];
                theCapacity = 1;
            } else {
                int* oldData = data;
                theCapacity *= 2;
                data = new int[theCapacity];
                for (size_t i = 0; i < theSize; ++i) {
                    data[i] = oldData[i];
                }
                delete [] oldData;
            }
        }
        data[theSize++] = val;
    }

    size_t size() const { return theSize; }
    void pop_back() { --theSize; }

    void clear() { theSize = 0; };


    // Square brackets?
    int operator[](size_t index) const {
        return data[index];
    }
    int& operator[](size_t index) {
        return data[index];
    }

    Const_Iterator begin() const {
	Const_Iterator result(data);
	return result;
    }
    Const_Iterator end() const {
	Const_Iterator result( data + theSize  );
	return result;
    }
   
    Iterator begin() {
	Iterator result(data);
	return result;
    }
    Iterator end() {
	Iterator result( data + theSize  );
	return result;
    }
   
    /*
    Iterator begin() const {
    }

    end() const {}
    */   
    
private:
    int* data;
    size_t theSize;
    size_t theCapacity;
};


void printVector(const Vector& v) {
    // for (size_t i = 0; i < v.size(); ++i) {
    //     cout << v[i] << ' ';
    // }
    // cout << endl;
    // for (int& val : v) {
    //     val *= 2;
    // }
    for (int val : v) {
        cout << val << ' ';
    }
    cout << endl;
}

int main() {

    // Not templated.  Our Vector class can only hold ints.
    Vector v;  

    v.push_back(17);
    v.push_back(42);
    v.push_back(6);
    v.push_back(28);
    printVector(v);
    
    v[0] = 100;

    Vector v2 = v;
    printVector(v2);

    Vector v3;
    v3 = v;
    printVector(v3);

    v3 = Vector(17);
    printVector(v2);


    cout << "Displaying using ranged for\n";
    for (int val : v2) {
        cout << val << ' ';
    }
    cout << endl;

    cout << "Displaying using iterators\n";
    for (Iterator iter = v2.begin(); iter != v2.end(); ++iter) {
	int val = *iter;
	cout << val << ' ';
    }
    cout << endl;
	
    for (int& val : v2) {
        ++val;
    }
    for (Iterator iter = v2.begin(); iter != v2.end(); ++iter) {
	int& val =  *iter;
	++val;
    }


    for (int val : v2) {
        cout << val << ' ';
    }
    cout << endl;
}

