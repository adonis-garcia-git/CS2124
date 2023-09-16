/*
  structs.cpp
  
  Demonstrate defining and using a struct

  CS2124 22F
  jbs
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Motorcycle {
    string model;
    int cc;
}; // don't forget the semi-colon

void printBike(const Motorcycle& aBike) {
    cout << aBike.model << " " << aBike.cc << endl;
}

int main() {
    Motorcycle myBike;

    //cout << myBike << endl;
    cout << myBike.model << " " << myBike.cc << endl;

    myBike.model ="Bonneville";
    myBike.cc = 1200;

    Motorcycle anotherBike { "VStrom", 650 };
    printBike(myBike);

    vector<Motorcycle> bikes;
    ifstream ifs("bikes.txt");

    if (!ifs) {
	cerr << "Couldn't open bikes.txt\n";
	exit(1);
    }

    string model;
    int cc;
    while (ifs >> model >> cc) {
	Motorcycle mc { model, cc };

	bikes.push_back(mc);
    }

    for (const Motorcycle& mc : bikes) {
	printBike(mc);
    }

}
