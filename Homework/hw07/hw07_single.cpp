/*
 hw07.cpp
 Adonis Garcia
 23 Fall
*/

// Comment out these two includes for the single file solution
// #include "Noble.h"
// #include "Protector.h"

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
using namespace std;

// Comment out this using namespace for the single file solution
// using namespace ProtectorCraft;

class Lord;

class Protector{
    friend ostream& operator<<(ostream& os, const Protector& aProtector);
public:
    // Constructor: initializes a Protector with a name and strength
    Protector(const string& aName, double aStrength);

    // Returns the Protector's name
    const string& getName() const;

    // Returns the Protector's strength
    double getStrength() const;

    // Checks if the Protector is dead
    bool isDead() const;

    // Checks if the Protector is hired
    bool isHired() const;

    // Marks the Protector as hired
    void gotHired(Lord* aLord);

    // Marks the Protector as not hired
    void gotFired();

    // Reduces the Protector's strength based on the given ratio
    void takesDamage (double ratio);

	// Protector leaves the army and is marked as not hired
	void runaway();

    // Kills the Protector by setting his strength to zero
    void kill();

	virtual void starter() const = 0;

	void generic() const;

private:
    const string name;
    double strength;
    bool is_hired;
    bool is_dead;
	Lord* hiringNoble;
};

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& aNoble); 
public:
    // Constructor: initializes a Noble with a name
    Noble(const string& aName, double strength = 0);

	// Returns the name of the Noble
    const string& getName() const;

	double getStrength() const;

	// Check if both Nobles are alive and returns false if either are dead
	bool areBothAlive(const Noble& otherNoble);

    // Initiates a battle between two Nobles
    void battle(Noble& otherNoble);

    // Reduces the strength of the Noble's army based on the given ratio
    virtual void getsHit (double ratio) = 0;

	bool isDead() const;

	virtual void display(ostream& os) const = 0;

	void setDead(); 

	virtual void kill() = 0;

	virtual void battlecry() const = 0;

protected:              
	void updateStrength(double amount);

private:
    const string name;
    bool is_dead;
    double strength;
};

class Lord : public Noble {
public:
	Lord(const string& name);

	// Kills the Noble and all his Protectors
    void kill();

    // Locates a Protector in the Noble's army and returns its position, 
    // or -1 if not found
    size_t locateProtector(Protector& aProtector) const;

    // Attempts to hire a Protector. If hiring fails, prints error message
    void hires(Protector& aProtector);

    // Fires a Protector from the Noble's army. If firing fails, print error message
    void fires(Protector& aProtector);

	// Removes a Protector from the army
	void removeProtector(Protector& aProtector);

	size_t getArmySize() const;

	void display(ostream& os) const;

	void getsHit(double ratio);

	void battlecry() const;
private:
    vector<Protector*> army;
};

class PersonWithStrengthToFight : public Noble {
public:
	PersonWithStrengthToFight(const string& name, double strength);

	void display(ostream& os) const;

	void getsHit(double ratio);

	void kill();

	void battlecry() const;
};

class Wizard : public Protector {
public:
	Wizard(const string& name, double strength);

	void starter() const;
};

class Warrior : public Protector {
public:
	Warrior(const string& name, double strength);
};

class Archer : public Warrior {
public:
	Archer(const string& name, double strength);

	void starter() const;
};

class Swordsman : public Warrior {
public:
	Swordsman(const string& name, double strength);

	void starter() const;
};

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);	
    janet.hires(stout);	
    janet.hires(samantha);     // fails because samantha works for sam.
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "\n==========\n";
    joe.battle(randy);	            // joe has no army and dies.
    joe.battle(sam);	            // joe is dead
    janet.battle(barclay);          // barclay wins
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);          // janet is dead, so can't hire
    sam.hires(thora);              // sam brings in reinforcements
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);	   // Silly janet
    sam.battle(barclay);           // Go Sam!
    samantha.runaway();            // Samantha has had enough
    sam.fires(thora);              // These layoffs! Sam fires thora.
    joe.battle(barclay);           // They're both dead already

    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "==========\n";
} // main

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
// Overloads the stream insertion operator to print a Noble's details
ostream& operator<<(ostream& os, const Noble& aNoble) {
    os << aNoble.name;
	aNoble.display(os);
    return os;
}

// Noble constructor
Noble::Noble(const string& aName, double strength)
: name(aName), strength(strength) {
	is_dead = false;
}

// Getter that returns the name of the Noble
const string& Noble::getName() const {return name;}

double Noble::getStrength() const{
	return strength;
}

void Noble::setDead(){
	strength = 0;
	is_dead = true;
}

bool Noble::isDead() const {
	return is_dead;
}

void Noble::updateStrength(double amount){
	strength += amount;
}

// Check if both Nobles are alive and returns false if either are dead
bool Noble::areBothAlive(const Noble& otherNoble){
	// Both Nobles are dead
	if (is_dead && otherNoble.is_dead) {
		cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
		return false;
	}

	// Current Noble is dead but the opponent is alive
	if (is_dead) {
		otherNoble.battlecry();
		cout << "He's dead " << otherNoble.name << endl;
		return false;
	}

	// Opponent Noble is dead but the current one is alive
	if (otherNoble.is_dead) {
		battlecry();
		cout << "He's dead " << name << endl;
		return false;
	}

	battlecry();
	otherNoble.battlecry();
	return true;
}

// Initiates a battle between two Nobles
void Noble::battle(Noble& otherNoble) {
	cout << name << " battles " << otherNoble.name << endl;
	
	if (!areBothAlive(otherNoble)){
		return;
	}

	// battlecry();
	// otherNoble.battlecry();

	// Current Noble has greater strength than opponent
	if (strength > otherNoble.strength) {
		cout << name << " defeats " << otherNoble.name << endl;
		double ratio = otherNoble.strength / strength;
		getsHit(ratio);
		otherNoble.kill();
	} 
	// Opponent Noble has greater strength than the current one
	else if (strength < otherNoble.strength) {
		cout << otherNoble.name << " defeats " << name << endl;
		double ratio = strength / otherNoble.strength;
		otherNoble.getsHit(ratio);
		kill();
	} 
	// Both Nobles have equal strength
	else {
		cout << "Mutual Annihilation: " << name << " and "
			<< otherNoble.name << " die at each other's hands" << endl;

		otherNoble.kill();
		kill();
	}
}

Lord::Lord(const string& name) : Noble(name) {}

void Lord::display(ostream& os) const {
    os << " has an army of size: " << army.size();
    for (int i{}; i < army.size(); i++){
        os << "\n\t" << *army[i];
    }
}

void Lord::battlecry() const{
	if (!army.size() || isDead()) return;
	for (int i{}; i < army.size(); i++){
		army[i]->starter();
		cout << endl;
    }
}

// Reduces the strength of the Noble's army based on the given ratio
void Lord::getsHit (double ratio) {
	if (ratio == 0) return;
	for (int i{}; i < army.size(); i++) {
		if (army[i]->isDead() == false) {
			double amount = army[i]->getStrength() * (1 - ratio);
			army[i]->takesDamage(ratio);
			updateStrength(-1 * amount);
		}
	}
}

size_t Lord::getArmySize() const{
	return army.size();
}

// Locates a Protector in the Noble's army and returns its position, 
// or -1 if not found
size_t Lord::locateProtector(Protector& aProtector) const {
	for (int i{}; i < army.size(); i++){
		if (army[i] == &aProtector){
			return i;
		}
	}

	return army.size();
} 

// Attempts to hire a Protector. If hiring fails, prints error message
void Lord::hires(Protector& aProtector){
	if ((aProtector.isHired()) || (aProtector.isDead()) || (isDead())) {
		return;
	}

	if (locateProtector(aProtector) != army.size()) {
		return;
	}

	updateStrength(aProtector.getStrength());
	army.push_back(&aProtector);

	aProtector.gotHired(this);
}

// Fires a Protector from the Noble's army. If firing fails, print error message
void Lord::fires(Protector& aProtector) {
	removeProtector(aProtector);

	cout << aProtector.getName() << ", you don't work for me any more! -- "
	<< getName() << endl;
}

void Lord::removeProtector(Protector& aProtector) {
	int index = locateProtector(aProtector);

	if ((index == army.size()) || (isDead())) {
		cout << getName() << " failed to hire " << aProtector.getName() << endl;
		return;
	}

	for (int i{index}; i < army.size() - 1; i++){
		army[i] = army[i + 1];
	}
	
	army.pop_back();
	aProtector.gotFired();
	updateStrength(-1 * aProtector.getStrength());
}

PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double strength) 
: Noble(name, strength) {}

void PersonWithStrengthToFight::display(ostream& os) const {
    os << " has strength: " << getStrength();
}

void PersonWithStrengthToFight::getsHit (double ratio) {
	if (ratio == 0) return;
	updateStrength(-1 * getStrength() * (ratio));
}

void PersonWithStrengthToFight::battlecry() const{
	cout << "Ugh!" << endl;
}

// Kills the Noble and all his Protectors
void Lord::kill() {
	for (int i{}; i < army.size(); i++) {
		if (army[i]->isDead() == false) {
			army[i]->kill();
		}
	}

	setDead();
}

void PersonWithStrengthToFight::kill() {
	setDead();
}
