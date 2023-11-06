// Overloads the stream insertion operator to print a Noble's details
#include "Noble.h"
#include "Warrior.h"

using namespace std;

namespace WarriorCraft {

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

}
