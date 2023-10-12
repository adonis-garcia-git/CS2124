/*
Author: Adonis Garcia
File: hw04.cpp
Class: CS-2124
Purpose: simulating nobles and warriors using classes and pointers
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Warrior{
     friend ostream& operator<<(ostream& os, const Warrior& aWarrior);
public:
     // Constructor: initializes a Warrior with a name and strength
     Warrior(const string& aName, double aStrength) : name(aName), strength(aStrength) {}

     // Returns the Warrior's name
     const string& getName() const {return name;}

     // Returns the Warrior's strength
     double getStrength() const {return strength;}

     // Checks if the Warrior is dead
     bool isDead() const {return is_dead;}

     // Checks if the Warrior is hired
     bool isHired() const {return is_hired;}

     // Marks the Warrior as hired
     void gotHired() {is_hired = true;}

     // Marks the Warrior as not hired
     void gotFired() {is_hired = false;}

     // Reduces the Warrior's strength based on the given ratio
     void takesDamage (double ratio) {
          strength *= (1 - ratio);
          if (strength < 0) {
               strength = 0;
               is_dead = true;
          }
     }

     // Kills the Warrior by setting his strength to zero
     void kill() {
          strength = 0;
          is_dead = true;
     }

private:
     const string name;
     double strength;
     bool is_hired{false};
     bool is_dead{false};
};

class Noble{
     friend ostream& operator<<(ostream& os, const Noble& aNoble); 
public:
     // Constructor: initializes a Noble with a name
     Noble(const string& aName) : name(aName) {}

     // Initiates a battle between two Nobles
     void battle(Noble& otherNoble) {
          cout << name << " battles " << otherNoble.name << endl;

          // Both Nobles are dead
          if (is_dead && otherNoble.is_dead) {
               cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
               return;
          }

          // Current Noble is dead but the opponent is alive
          if (is_dead) {
               cout << "He's dead, " << otherNoble.name << endl;
               return;
          }

          // Opponent Noble is dead but the current one is alive
          if (otherNoble.is_dead) {
               cout << "He's dead, " << name << endl;
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
     void getsHit (double ratio) {
          for (int i{}; i < army_size; i++) {
               if (army[i]->isDead() == false) {
                    double amount = army[i]->getStrength() * (1 - ratio);
                    army[i]->takesDamage(ratio);
                    strength -= amount;
               }
          }
     }

     // Kills the Noble and all his Warriors
     void massacre() {
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
     int locateWarrior(Warrior& aWarrior) const {
          for (int i{}; i < army_size; i++){
               if (army[i] == &aWarrior){
                    return i;
               }
          }

          return -1;
     } 

     // Attempts to hire a Warrior. If hiring fails, prints error message
     void hire(Warrior& aWarrior){
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

          aWarrior.gotHired();
     }

     // Fires a Warrior from the Noble's army. If firing fails, print error message
     void fire(Warrior& aWarrior) {
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

          cout << aWarrior.getName() << ", you don't work for me any more! -- "
          << name << endl;
     }
private:
     const string name;
     vector<Warrior*> army; // maintain order
     bool is_dead{false};
     double strength{};
     int army_size{};
};

// Overloads the stream insertion operator to print a Noble's details
ostream& operator<<(ostream& os, const Noble& aNoble) {
     os << aNoble.name << " had an army of " << aNoble.army_size;
     for (int i{}; i < aNoble.army_size; i++){
          os << "\n\t" << *aNoble.army[i];
     }
     return os;
}

// Overloads the stream insertion operator to print a Warrior's details
ostream& operator<<(ostream& os, const Warrior& aWarrior) {
     os << aWarrior.name << ": " << aWarrior.strength;
     return os;
}

int main() {
	
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);
	
    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";
	
    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
	
}
