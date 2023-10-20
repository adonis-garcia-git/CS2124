#ifndef FROGPRINCE_CPP
#define FROGPRINCE_CPP

#include "Princess.h"
#include "FrogPrince.h" // necessary to define FrogPrince methods
// #include <string> // (optional) since princess.h already has it
using namespace std;
using namespace Fantasy;

namespace Fantasy { // creating Fantasy namespace

FrogPrince::FrogPrince(const string& name) : name(name), spouse(nullptr) {};

const string& FrogPrince::getName() const {
    return name;
}

void FrogPrince::setSpouse(Princess* pp){
        spouse = pp;
}

}

#endif
