#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {

class Lord;

class Protector{
    friend std::ostream& operator<<(std::ostream& os, const Protector& aProtector);
public:
    // Constructor: initializes a Protector with a name and strength
    Protector(const std::string& aName, double aStrength);

    // Returns the Protector's name
    const std::string& getName() const;

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
    const std::string name;
    double strength;
    bool is_hired;
    bool is_dead;
	Lord* hiringNoble;
};

class Wizard : public Protector {
public:
	Wizard(const std::string& name, double strength);

	void starter() const;
};

class Warrior : public Protector {
public:
	Warrior(const std::string& name, double strength);
};

class Archer : public Warrior {
public:
	Archer(const std::string& name, double strength);

	void starter() const;
};

class Swordsman : public Warrior {
public:
	Swordsman(const std::string& name, double strength);

	void starter() const;
};

}

#endif