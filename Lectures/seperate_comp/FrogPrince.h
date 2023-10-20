#ifndef FROGPRINCE_H
#define FROGPRINCE_H

#include <iostream>
#include <string>

//std:: is called qualifying

namespace Fantasy { // creating Fantasy namespace

class Princess;

class FrogPrince {
    friend std::ostream& operator<<(std::ostream& os, const FrogPrince& frog) {
        os << "Frog Prince: " << frog.name;
        return os;
    }
public:
    FrogPrince(const std::string& name);
    void setSpouse(Princess* pp);
    const std::string& getName() const;
private:
    std::string name;
    Princess* spouse;
};

}
#endif
