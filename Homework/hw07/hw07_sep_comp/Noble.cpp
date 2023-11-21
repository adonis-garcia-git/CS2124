#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft {

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

// Kills the Noble and all his Protectors
void Lord::kill() {
	for (int i{}; i < army.size(); i++) {
		if (army[i]->isDead() == false) {
			army[i]->kill();
		}
	}

	setDead();
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

void PersonWithStrengthToFight::kill() {
	setDead();
}

}