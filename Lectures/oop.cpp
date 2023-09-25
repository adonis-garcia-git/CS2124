/*
  CS2124 - Sec A
  oop.cpp

  Starting with a struct and a function that is passed an instance of
  that struct. Evolve into a class using encapsulation and data hiding.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//struct Person {
class Person {
    //friend ostream& operator<<(ostream& os, const Person& aPerson);
    friend ostream& operator<<(ostream& os, const Person& aPerson) { //has access to private/protected functions/variables
	os << "Name: " << aPerson.name << ", age: " << aPerson.age;
	return os;
    }
public:
    // Person(const string& aName) {
    // 	name = aName; // Will improve on this;
    // Yes we can use default parameter values
    // and if we are using the initialization list the parameter can
    // be named the same as the field!
    Person(const string& aName, int age = 18) : name(aName),
						age(age) {
    }

    //void eats() {
    void eats() const {
	cout << name << " eating\n";
	//name = "Fred";
    }

    // Setters (aka Mutators)
    //void setName(string aName) {
    void setName(const string& aName) {
	name = aName;
    }

    //string getName() { return name; }
    //string getName() const { return name; }
    const string& getName() const { return name; }

    int getAge() const { return age; }
private:
    string name;
    int age;
};

void personEating(const Person& aPerson) {
    //cout << aPerson.name << " eating\n";
    aPerson.eats();
}

// ostream& operator<<(ostream& os, const Person& aPerson) {
//     //os << "Name: " << aPerson.name;
//     //os << "Name: " << aPerson.getName() << ", age: " << aPerson.getAge();
//     os << "Name: " << aPerson.name << ", age: " << aPerson.age;
//     return os;
// }

int main() {
    Person john("John");
    //john.name = "John";
    //john.setName("John");
    //    personEating(john);

    john.eats();

    //    Person mary;

    //(cout << john) << endl;
    //cout << john;
    //operator<<(cout, john);
    cout << john << endl;

    vector<Person> people;
    people.push_back(john); //needs the object type

    people.push_back(Person("Mary"));

    people.emplace_back("Fred"); //needs the parameters of the object type
    people.emplace_back(Person("George")); // DON'T
}
