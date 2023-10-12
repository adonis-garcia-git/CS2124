/*
Author: Adonis Garcia
File: hw05.cpp
Class: CS-2124
Purpose: simulating nobles and warriors using classes and pointers
*/

//change error print statemetns
//add unemployed warriors
//add status command heading prints
//split parser into multiple functions

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
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

     const string& getName() const {return name;}

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

void open_file(ifstream& file);
void parser(ifstream& file, vector<Noble*>& nobles, vector<Warrior*>& warriors);
size_t locate_noble(string& name, vector<Noble*>& nobles);
size_t locate_warrior(string& name, vector<Warrior*>& warriors);

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
	vector<Noble*> nobles;
    vector<Warrior*> warriors;

    ifstream file;
    open_file(file);

    parser(file, nobles, warriors);

    file.close();
    nobles.clear();
    warriors.clear();
}

void open_file(ifstream& file){
    file.open("nobleWarriors.txt");
    if (!file){
        cerr << "File couldn't be opened" << endl;
        exit(1);
    }
}

void parser(ifstream& file, vector<Noble*>& nobles, vector<Warrior*>& warriors){
    string command;
    string name;
    string name2;
    string weapon_name;
    double strength;

    while (file >> command){
        if (command == "Noble"){
            file >> name;
            if (locate_noble(name, nobles) == nobles.size()){
                nobles.push_back(new Noble(name));
            }
            else {
                cout << name << " already exists" << endl;
            }
        } else if (command == "Warrior"){
            file >> name >> strength;
            if (locate_warrior(name, warriors) == warriors.size()){
                warriors.push_back(new Warrior(name, strength));
            }
            else {
                cout << name << " already exists" << endl;
            }
        } else if (command == "Hire"){
            file >> name >> name2;
            if (locate_noble(name, nobles) == nobles.size()){
                cout << name << " doesn't exist" << endl;
            } else if (locate_warrior(name2, warriors) == warriors.size()){
                cout << name2 << " doesn't exist" << endl;
            } else {
                size_t noble_index{locate_noble(name, nobles)};
                size_t warrior_index{locate_warrior(name2, warriors)};
                nobles[noble_index]->hire(*warriors[warrior_index]);
            } 
        } else if (command == "Fire"){
            file >> name >> name2;
            if (locate_noble(name, nobles) == nobles.size()){
                cout << name << " doesn't exist" << endl;
            } else if (locate_warrior(name2, warriors) == warriors.size()){
                cout << name2 << " doesn't exist" << endl;
            } else {
                size_t noble_index{locate_noble(name, nobles)};
                size_t warrior_index{locate_warrior(name2, warriors)};
                nobles[noble_index]->fire(*warriors[warrior_index]);
            } 
        } else if (command == "Battle"){
            file >> name >> name2;
            if (locate_noble(name, nobles) == nobles.size()){
                cout << name << " doesn't exist" << endl;
            } else if (locate_noble(name2, nobles) == nobles.size()){
                cout << name2 << " doesn't exist" << endl;
            } else {
                size_t noble_index{locate_noble(name, nobles)};
                size_t noble2_index{locate_noble(name2, nobles)};
                nobles[noble_index]->battle(*nobles[noble2_index]);
            } 
        } else if (command == "Status"){
            for (size_t i{}; i < nobles.size(); i++){
                cout << *nobles[i] << endl;
            }
        } else if (command == "Clear"){
            for (size_t i{nobles.size()}; i > 0; i--){
                delete nobles[i-1];
                nobles[i-1] = nullptr;
                nobles.pop_back();
            }
            nobles.clear();
            for (size_t i{warriors.size()}; i > 0; i--){
                delete warriors[i-1];
                warriors[i-1] = nullptr;
                warriors.pop_back();
            }
            warriors.clear();
        }
    }
}

size_t locate_noble(string& name, vector<Noble*>& nobles){
    for (size_t i{}; i < nobles.size(); i++){
        if (nobles[i]->getName() == name) {
            return i;
        }
    }

    return nobles.size();
}

size_t locate_warrior(string& name, vector<Warrior*>& warriors){
    for (size_t i{}; i < warriors.size(); i++){
        if (warriors[i]->getName() == name) {
            return i;
        }
    }

    return warriors.size();
}

