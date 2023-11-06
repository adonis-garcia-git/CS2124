// Overloads the stream insertion operator to print a Warrior's details
#include "Noble.h"
#include "Warrior.h"

using namespace std;

namespace WarriorCraft {

ostream& operator<<(ostream& os, const Warrior& aWarrior) {
    os << aWarrior.name << ": " << aWarrior.strength;
    return os;
}

// Constructor: initializes a Warrior with a name and strength
Warrior::Warrior(const string& aName, double aStrength) : name(aName), strength(aStrength) {
	hiringNoble = nullptr;
	is_hired = false;
	is_dead = false;
}

// Returns the Warrior's name
const string& Warrior::getName() const {return name;}

// Returns the Warrior's strength
double Warrior::getStrength() const {return strength;}

// Checks if the Warrior is dead
bool Warrior::isDead() const {return is_dead;}

// Checks if the Warrior is hired
bool Warrior::isHired() const {return is_hired;}

// Marks the Warrior as hired
void Warrior::gotHired(Noble* aNoble) { 											// confirm if const is needed
	is_hired = true;
	hiringNoble = aNoble;
}

// Marks the Warrior as not hired
void Warrior::gotFired() {
	is_hired = false;
	hiringNoble = nullptr;
}

// Reduces the Warrior's strength based on the given ratio
void Warrior::takesDamage (double ratio) {
	strength *= (1 - ratio);
	if (strength < 0) {
		strength = 0;
		is_dead = true;
	}
}

void Warrior::runaway() {
	cout << name << " flees in terror, abandoning his lord, " << hiringNoble->getName() << endl;
	hiringNoble->removeWarrior(*this);
	hiringNoble = nullptr;
	is_hired = false;
}

// Kills the Warrior by setting his strength to zero
void Warrior::kill() {
	strength = 0;
	is_dead = true;
}

}
