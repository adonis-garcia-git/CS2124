/*
  Defining functions and using parameter passing
  2023 Fall - Sec A
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//void addOne(int someInt); // function prototype
void addOne(int); // function prototype

int addOneV2(int someInt) { // pass by value
    ++someInt;  // Same effect as: someInt += 1;
    return someInt;
}

void addOneV3(int& someInt) { // pass by reference
    ++someInt;  // Same effect as: someInt += 1;
}

//void printVec(vector<int> aVec) {
//void printVec(vector<int>& aVec) {
void printVec(const vector<int>& aVec) { // pass by constant reference
    for (int val : aVec) {
	cout << val << ' ';
    }
    cout << endl;
    //aVec.clear();
}

void printInt(const int val) {
    cout << val << endl;
}

void printIntV2(const int& val) { // Don't
    cout << val << endl;
}

//void printVecString(vector<string> vs) {
//void printVecString(vector<string>& vs) {
void printVecString(const vector<string>& vs) {
    //for (string& val : vs) {
    for (const string& val : vs) {
	cout << val << ", ";
    }
    cout << endl;
}    

void addSomething(int& someInt, int addOn = 17);
    

int main() {

    int x = 17;

    addOne(x);
    cout << x << endl;

    x = addOneV2(x);
    cout << x << endl;

    addOneV3(x);
    cout << x << endl;

    vector<int> v{2, 3, 5, 7, 11, 13};

    for (int val : v) {
	cout << val << ' ';
    }
    cout << endl;

    printVec(v);

    //addOneV3(17); // compilation error

    for (int& val : v) {
	++val;
    }

    vector<string> vs{"the", "cat", "in", "the", "hat"};

    //for (string val : vs) {
    //for (string& val : vs) {
    for (const string& val : vs) {
	cout << val << ", ";
    }
    cout << endl;
    
    addSomething(x);
}

void addOne(int someInt) { // pass by value
    ++someInt;  // Same effect as: someInt += 1;
    //    return;
}

void addSomething(int& someInt, int addOn) {
    someInt += addOn;
}
