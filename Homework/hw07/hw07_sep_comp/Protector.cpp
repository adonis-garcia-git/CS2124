#include "Protector.h"
#include "Noble.h"
using namespace std;

namespace WarriorCraft {

// Overloads the stream insertion operator to print a Protector's details
ostream& operator<<(ostream& os, const Protector& aProtector) {
    os << aProtector.name << " has strength " << aProtector.strength;
    return os;
}

// Constructor: initializes a Protector with a name and strength
Protector::Protector(const string& aName, double aStrength) 
: name(aName), strength(aStrength) {
	hiringNoble = nullptr;
	is_hired = false;
	is_dead = false;
}

// Returns the Protector's name
const string& Protector::getName() const {return name;}

// Returns the Protector's strength
double Protector::getStrength() const {return strength;}

// Checks if the Protector is dead
bool Protector::isDead() const {return is_dead;}

// Checks if the Protector is hired
bool Protector::isHired() const {return is_hired;}

// Marks the Protector as hired
void Protector::gotHired(Lord* aLord) { 											
	is_hired = true;
	hiringNoble = aLord;
}

// Marks the Protector as not hired
void Protector::gotFired() {
	is_hired = false;
	hiringNoble = nullptr;
}

// Reduces the Protector's strength based on the given ratio
void Protector::takesDamage (double ratio) {
	strength *= (1 - ratio);
	if (strength < 0) {
		strength = 0;
		is_dead = true;
	}
}


void Protector::runaway() {
	cout << name << " flees in terror, abandoning his lord, "
	<< hiringNoble->getName() << endl;
	hiringNoble->removeProtector(*this);
	hiringNoble = nullptr;
	is_hired = false;
}

// Kills the Protector by setting his strength to zero
void Protector::kill() {
	strength = 0;
	is_dead = true;
}

void Protector::generic() const{
	cout << name << " says: Take that in the name of my lord, " 
	<< hiringNoble->getName();
}

Wizard::Wizard(const string& name, double strength) : Protector(name, strength) {}

void Wizard::starter() const {
	cout << "POOF! ";
}

Warrior::Warrior(const string& name, double strength) : Protector(name, strength) {}

Archer::Archer(const string& name, double strength) : Warrior(name, strength) {}

void Archer::starter() const {
	cout << "TWANG!  ";
	generic();
}

Swordsman::Swordsman(const string& name, double strength) : Warrior(name, strength) {}

void Swordsman::starter() const {
	cout << "CLANG!  ";
	generic();
}

}