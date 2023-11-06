#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {

class Warrior;

class Noble
{
    friend std::ostream &operator<<(std::ostream &os, const Noble &aNoble);

public:
    // Constructor: initializes a Noble with a name
    Noble(const std::string &aName);

    // Returns the name of the Noble
    const std::string &getName() const;

    // Check if both Nobles are alive and returns false if either are dead
    bool areBothAlive(const Noble &otherNoble);

    // Initiates a battle between two Nobles
    void battle(Noble &otherNoble);

    // Reduces the strength of the Noble's army based on the given ratio
    void getsHit(double ratio);

    // Kills the Noble and all his Warriors
    void massacre();

    // Locates a Warrior in the Noble's army and returns its position,
    // or -1 if not found
    int locateWarrior(Warrior &aWarrior) const;

    // Attempts to hire a Warrior. If hiring fails, prints error message
    void hire(Warrior &aWarrior);

    // Fires a Warrior from the Noble's army. If firing fails, print error message
    void fire(Warrior &aWarrior);

    // Removes a Warrior from the army
    void removeWarrior(Warrior &aWarrior);

private:
    const std::string name;
    std::vector<Warrior *> army;
    bool is_dead;
    double strength;
    int army_size;
};

}

#endif
