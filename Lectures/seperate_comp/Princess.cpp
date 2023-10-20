#ifndef PRINCESS_CPP
#define PRINCESS_CPP

#include "Princess.h"
#include "FrogPrince.h" // necessary to define FrogPrince methods
// #include <string> // (optional) since princess.h already has it
using namespace std;
using namespace Fantasy;

namespace Fantasy { // creating Fantasy namespace

void Princess::marries(FrogPrince& betrothed) { // defined later so it knows setSpouse exists
    spouse = &betrothed;
    betrothed.setSpouse(this);
}

Princess::Princess(const string& name) : name(name), spouse(nullptr) {}

const string& Princess::getName() const {
    return name;
}

ostream& operator<<(ostream& os, const Princess& princess) { // not a member method, just a friended function
        os << "Princess: " << princess.name
        << ", marital status: ";
        if (princess.spouse == nullptr) {
            os << "Single";
        }
        else {
            os << "Married to: " << princess.spouse->getName();
        }
        return os;
    }

}

#endif
