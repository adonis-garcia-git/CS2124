/*
  loadStooges.cpp
  Inclass Sec A

  Here we are loading a vector of instances of Person
  Modify it to load a vector of pointers to Person instancess
  
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Person {
    friend ostream& operator<<(ostream& os, const Person& someone) {
        os << "Person: " << someone.name << ", " << someone.age;
        return os;
    }
public:
    Person(const string& name, int age) : name(name), age(age) {}
    const string& getName() const { return name; }
private:
    string name;
    int age;
};

int main() {
    ifstream ifs("stooges.txt");
    if (!ifs) {
	cerr << "Failed to open stooges.txt\n";
	exit(1);
    }

    /*
    vector<Person> stooges;
    
    string name;
    int age;
    while (ifs >> name >> age) {
	Person aPerson(name, age);
	stooges.push_back(aPerson);
    }

    for (const Person& per : stooges) {
	cout << per << endl;
    }
    */

    vector<Person*> stooges;
    
    string name;
    int age;
    while (ifs >> name >> age) {
	// Person aPerson(name, age);
	// stooges.push_back(&aPerson);
	Person* personPtr = new Person(name, age);
	stooges.push_back(personPtr);
    }

    ifs.close();

    for (Person* per : stooges) {
    //for (const Person* per : stooges) {
	cout << per << ": " << *per << endl;
    }
    
    Person* p = new Person("Fred", 22);

    delete p;

    //    stooges.clear(); // Memory leak, aka garbage on the heap
    
    for (Person* per : stooges) {
    	delete per;
	per = nullptr; // Not useful as per here is a local copy
    }
    stooges.clear();

    for (Person*& per : stooges) {
    	delete per;
	per = nullptr; // actually makes the real pointer point to null
    }
    stooges.clear();

    

    

}
