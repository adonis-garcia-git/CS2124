#include <iostream>
#include <string>

using namespace std;

class FrogPrince;

class Princess {
    friend ostream& operator<<(ostream& os, const Princess& princess); // prototype only
public:
    // Princess(const string& name) : name(name), spouse(nullptr) {}
    Princess(const string& name); //prototype of constructor (without init list) to be defined later
    void marries(FrogPrince& betrothed); //prototype of method so can define later

    // void marries(FrogPrince& betrothed) {
    //     spouse = &betrothed;
    //     betrothed.setSpouse(this);
    // }

    const string& getName() const;
private:
    string name;
    FrogPrince* spouse;
    // FrogPrince spouse; // this class doesn't know how to construct a Frogprince instance or size
};

class FrogPrince {
    friend ostream& operator<<(ostream& os, const FrogPrince& frog) {
        os << "Frog Prince: " << frog.name;
        return os;
    }
public:
    FrogPrince(const string& name) : name(name), spouse(nullptr) {}
    void setSpouse(Princess* pp){
        spouse = pp;
    }
    const string& getName() const;
private:
    string name;
    Princess* spouse;
};

void Princess::marries(FrogPrince& betrothed) { // defined later so it knows setSpouse exists
    spouse = &betrothed;
    betrothed.setSpouse(this);
}

Princess::Princess(const string& name) : name(name), spouse(nullptr) {}

const string& FrogPrince::getName() const {
    return name;
}

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

int main() {
    Princess snowy("Snow White");
    FrogPrince froggy("Froggy");
    snowy.marries(froggy);
}

// begin() and end() are overloaded with different versions of const
// operator[] is overloaded with different versions of const

//not providing a necessary function results in linking error
