/*
  oop2.cpp
  CS2124
  Sec Base
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person {
    friend ostream& operator<<(ostream& os, const Person& rhs);

    class Date {
	friend ostream& operator<<(ostream& os, const Date& rhs);
    public:
	Date(int month, int day, int year)
	    : month(month), day(day), year(year){}
    private:
	int month, day, year;
    };

    friend ostream& operator<<(ostream& os, const Person::Date& rhs);
public:
    Person(const string& name, int m, int d, int y)
	: name(name), bday(m, d, y) { }
private:    
    string name;
    Date bday;
};

int main() {
    Person john("John", 6, 1, 2000);
    cout << john << endl;

    // Person::Date aDate(7, 4, 2023);
    // cout << aDate << endl;
}

ostream& operator<<(ostream& os, const Person& rhs) {
    os << "Person: " << rhs.name << ", dob: " << rhs.bday;
    return os;
}

//ostream& operator<<(ostream& os, const Date& rhs) { // can't access Date class directly
ostream& operator<<(ostream& os, const Person::Date& rhs) { //states that date class is defined within Person
    os << rhs.month << '/' << rhs.day << '/' << rhs.year;
    return os;
}

