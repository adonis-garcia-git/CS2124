/*
 hw06-testcode.cpp
 21 Fall
 */

// Comment out these two includes for the single file solution
// #include "Noble.h"
// #include "Warrior.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Comment out this using namespace for the single file solution
// using namespace WarriorCraft;

class Noble;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& aWarrior);
public:
    // Constructor: initializes a Warrior with a name and strength
    Warrior(const string& aName, double aStrength);

    // Returns the Warrior's name
    const string& getName() const;

    // Returns the Warrior's strength
    double getStrength() const;

    // Checks if the Warrior is dead
    bool isDead() const;

    // Checks if the Warrior is hired
    bool isHired() const;

    // Marks the Warrior as hired
    void gotHired(Noble* aNoble);

    // Marks the Warrior as not hired
    void gotFired();

    // Reduces the Warrior's strength based on the given ratio
    void takesDamage (double ratio);

	// Warrior leaves the army and is marked as not hired
	void runaway();

    // Kills the Warrior by setting his strength to zero
    void kill();

private:
    const string name;
    double strength;
    bool is_hired;
    bool is_dead;
	Noble* hiringNoble;
};

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& aNoble); 
public:
    // Constructor: initializes a Noble with a name
    Noble(const string& aName);

	// Returns the name of the Noble
    const string& getName() const;

	// Check if both Nobles are alive and returns false if either are dead
	bool areBothAlive(const Noble& otherNoble);

    // Initiates a battle between two Nobles
    void battle(Noble& otherNoble);

    // Reduces the strength of the Noble's army based on the given ratio
    void getsHit (double ratio);

    // Kills the Noble and all his Warriors
    void massacre();

    // Locates a Warrior in the Noble's army and returns its position, 
    // or -1 if not found
    int locateWarrior(Warrior& aWarrior) const;

    // Attempts to hire a Warrior. If hiring fails, prints error message
    void hire(Warrior& aWarrior);

    // Fires a Warrior from the Noble's army. If firing fails, print error message
    void fire(Warrior& aWarrior);

	// Removes a Warrior from the army
	void removeWarrior(Warrior& aWarrior);

private:
    const string name;
    vector<Warrior*> army;
    bool is_dead;
    double strength;
    int army_size;
};

int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 4);
	Warrior sky("Leia", 6);
	Warrior wizard("Merlin", 9);
	Warrior jaffa("Teal'c", 9);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(jaffa);
	art.hire(cheetah);
	art.hire(wizard);
	art.hire(sky);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(nimoy);

	cout << "================ Initial Status ===============" << endl;
	cout << art << endl
	     << lance << endl
	     << jim << endl
	     << linus << endl
	     << billie << endl;
	cout << "===============================================\n\n";

	art.fire(cheetah);
	wizard.runaway();
	cout << endl << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	cout << "\n================ Final Status ===============" << endl;
	cout << art << endl
	     << lance << endl
	     << jim << endl
	     << linus << endl
	     << billie << endl;

	// Tarzan and Merlin should be unemployed
	cout << "Tarzan's Hire Status: " << boolalpha 
	     << cheetah.isHired() << endl;
	cout << "Merlin's Hire Status: " << boolalpha 
	     << wizard.isHired() << endl;
	cout << "===============================================\n\n";
}

// Overloads the stream insertion operator to print a Warrior's details
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

// Overloads the stream insertion operator to print a Noble's details
ostream& operator<<(ostream& os, const Noble& aNoble) {
    os << aNoble.name << " had an army of " << aNoble.army_size;
    for (int i{}; i < aNoble.army_size; i++){
        os << "\n\t" << *aNoble.army[i];
    }
    return os;
}

// Noble constructor
Noble::Noble(const string& aName) : name(aName) {
	is_dead = false;
	strength = 0;
	army_size = 0;
}

// Getter that returns the name of the Noble
const string& Noble::getName() const {return name;}

// Check if both Nobles are alive and returns false if either are dead
bool Noble::areBothAlive(const Noble& otherNoble){
	// Both Nobles are dead
	if (is_dead && otherNoble.is_dead) {
		cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
		return false;
	}

	// Current Noble is dead but the opponent is alive
	if (is_dead) {
		cout << "He's dead, " << otherNoble.name << endl;
		return false;
	}

	// Opponent Noble is dead but the current one is alive
	if (otherNoble.is_dead) {
		cout << "He's dead, " << name << endl;
		return false;
	}

	return true;
}

// Initiates a battle between two Nobles
void Noble::battle(Noble& otherNoble) {
	cout << name << " battles " << otherNoble.name << endl;

	if (!areBothAlive(otherNoble)){
		return;
	}

	// Current Noble has greater strength than opponent
	if (strength > otherNoble.strength) {
		cout << name << " defeats " << otherNoble.name << endl;
		double ratio = otherNoble.strength / strength;
		getsHit(ratio);
		otherNoble.massacre();
	} 
	// Opponent Noble has greater strength than the current one
	else if (strength < otherNoble.strength) {
		cout << otherNoble.name << " defeats " << name << endl;
		double ratio = strength / otherNoble.strength;
		otherNoble.getsHit(ratio);
		massacre();
	} 
	// Both Nobles have equal strength
	else {
		cout << "Mutual Annihilation: " << name << " and "
			<< otherNoble.name << " die at each other's hands" << endl;

		otherNoble.massacre();
		massacre();
	}
}

// Reduces the strength of the Noble's army based on the given ratio
void Noble::getsHit (double ratio) {
	for (int i{}; i < army_size; i++) {
		if (army[i]->isDead() == false) {
			double amount = army[i]->getStrength() * (1 - ratio);
			army[i]->takesDamage(ratio);
			strength -= amount;
		}
	}
}

// Kills the Noble and all his Warriors
void Noble::massacre() {
	for (int i{}; i < army_size; i++) {
		if (army[i]->isDead() == false) {
			army[i]->kill();
		}
	}

	strength = 0;
	is_dead = true;
}

// Locates a Warrior in the Noble's army and returns its position, 
// or -1 if not found
int Noble::locateWarrior(Warrior& aWarrior) const {
	for (int i{}; i < army_size; i++){
		if (army[i] == &aWarrior){
			return i;
		}
	}

	return -1;
} 

// Attempts to hire a Warrior. If hiring fails, prints error message
void Noble::hire(Warrior& aWarrior){
	if ((aWarrior.isHired()) || (aWarrior.isDead()) || (is_dead)) {
		cout << name << " failed to hire " << aWarrior.getName() << endl;
		return;
	}

	if (locateWarrior(aWarrior) != -1) {
		cout << name << " failed to hire " << aWarrior.getName() << endl;
		return;
	}

	army_size += 1;
	strength += aWarrior.getStrength();
	army.push_back(&aWarrior);

	aWarrior.gotHired(this);
}

// Fires a Warrior from the Noble's army. If firing fails, print error message
void Noble::fire(Warrior& aWarrior) {
	removeWarrior(aWarrior);

	cout << aWarrior.getName() << ", you don't work for me any more! -- "
	<< name << endl;
}

void Noble::removeWarrior(Warrior& aWarrior) {
	int index = locateWarrior(aWarrior);

	if ((index == -1) || (is_dead)) {
		cout << name << " failed to hire " << aWarrior.getName() << endl;
		return;
	}

	for (int i{index}; i < army_size - 1; i++){
		army[i] = army[i + 1];
	}
	
	army.pop_back();
	army_size -= 1;
	aWarrior.gotFired();
	strength -= aWarrior.getStrength();
}
