#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {

class Protector;

class Noble{
    friend std::ostream& operator<<(std::ostream& os, const Noble& aNoble); 
public:
    // Constructor: initializes a Noble with a name
    Noble(const std::string& aName, double strength = 0);

	// Returns the name of the Noble
    const std::string& getName() const;

	double getStrength() const;

	// Check if both Nobles are alive and returns false if either are dead
	bool areBothAlive(const Noble& otherNoble);

    // Initiates a battle between two Nobles
    void battle(Noble& otherNoble);

    // Reduces the strength of the Noble's army based on the given ratio
    virtual void getsHit (double ratio) = 0;

	bool isDead() const;

	virtual void display(std::ostream& os) const = 0;

	void setDead(); 

	virtual void kill() = 0;

	virtual void battlecry() const = 0;

protected:              
	void updateStrength(double amount);

private:
    const std::string name;
    bool is_dead;
    double strength;
};

class Lord : public Noble {
public:
	Lord(const std::string& name);

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

	void display(std::ostream& os) const;

	void getsHit(double ratio);

	void battlecry() const;
private:
    std::vector<Protector*> army;
};

class PersonWithStrengthToFight : public Noble {
public:
	PersonWithStrengthToFight(const std::string& name, double strength);

	void display(std::ostream& os) const;

	void getsHit(double ratio);

	void kill();

	void battlecry() const;
};

}

#endif

