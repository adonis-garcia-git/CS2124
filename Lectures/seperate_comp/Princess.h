#ifndef PRINCESS_H
#define PRINCESS_H

#include <iostream>
#include <string>
// #include "FrogPrince.h" // Likely to be a problem!
// using namespace std;  // NOT IN HEADER FILES!!!

namespace Fantasy { // creating Fantasy namespace

class FrogPrince;

class Princess {
    friend std::ostream& operator<<(std::ostream& os, const Princess& princess); // prototype only
public:
    // Princess(const string& name) : name(name), spouse(nullptr) {}
    Princess(const std::string& name); //prototype of constructor (without init list) to be defined later
    void marries(FrogPrince& betrothed); //prototype of method so can define later

    // void marries(FrogPrince& betrothed) {
    //     spouse = &betrothed;
    //     betrothed.setSpouse(this);
    // }

    const std::string& getName() const;
private:
    std::string name;
    FrogPrince* spouse;
    // FrogPrince spouse; // this class doesn't know how to construct a Frogprince instance or size
};

}

#endif
