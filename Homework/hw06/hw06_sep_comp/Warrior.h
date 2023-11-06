#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {

class Noble;

class Warrior{
    friend std::ostream& operator<<(std::ostream& os, const Warrior& aWarrior);
public:
    // Constructor: initializes a Warrior with a name and strength
    Warrior(const std::string& aName, double aStrength);

    // Returns the Warrior's name
    const std::string& getName() const;

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
    const std::string name;
    double strength;
    bool is_hired;
    bool is_dead;
	Noble* hiringNoble;
};

}

#endif
