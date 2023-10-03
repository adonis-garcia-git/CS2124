/*
Author: Adonis Garcia
File: hw03.cpp
Class: CS-2124
Purpose: simulating medieval times warrier game using classes
*/

#include <iostream>     //include I/O library
#include <fstream>      //include file I/O library
#include <string>       //include string library
#include <vector>       //include vector library
using namespace std;

// Represents a Warrior with a nested Weapon class.
class Warrior{
    // Represents a Weapon with a name and strength.
    class Weapon{
        friend ostream& operator<<(ostream& os, const Weapon& aWeapon);
    public:
        // Constructs a Weapon with a given name and strength.
        Weapon(const string& name, int strength)
        : weapon_name(name), strength(strength){};

        // Reduces the weapon's strength by a specified number of units, 
        // ensuring it never goes negative by setting to 0.
        void take_damage(int strength_units){
            strength -= strength_units;
            if (strength < 0){
                strength = 0;
            };
        };

        // Returns the current strength of the weapon.
        int get_weapon_strength() const {
            return strength;
        }

    private:
        const string weapon_name;   // Weapon name
        int strength;               // Weapon strength
    };

    friend ostream& operator<<(ostream& os, const Warrior& aWarrior);
    friend ostream& operator<<(ostream& os, const Weapon& aWeapon);

public:
    // Constructs a Warrior with a name and a weapon.
    Warrior(const string& aName, const string& weapon_name, int strength)
    : name(aName), weapon(weapon_name, strength) {};

    // Returns the name of the Warrior.
    const string& get_name() const {
        return name;
    };

    // Reduces the weapon's strength based on an opponent's attack.
    void gets_hit(int opponent_strength){
        weapon.take_damage(opponent_strength);
    };

    // Returns the current strength of the Warrior's weapon.
    int get_strength() const {
        return weapon.get_weapon_strength();
    };

private:
    Weapon weapon;      // Warrior's weapon of Weapon class
    const string name;  // Warrior's name
};

// Opens a file stream for reading the warrior data.
void open_file(ifstream& file);

// Manages the game, processing each command in the file: Warrior, Status, or Battle.
void run_game(ifstream& file, vector<Warrior>& warrior_list);

// Prepares two warriors for a battle by locating them and invoking the battle function.
void prepare_battle(ifstream& file, vector<Warrior>& warrior_list);

// Conducts a battle between two warriors, updating their strength accordingly.
void battle(Warrior& first_warrior, Warrior& second_warrior);

// Adds a new warrior to the list of warriors from the file's data.
void add_warrior(ifstream& file, vector<Warrior>& warrior_list);

// Searches for and returns the index of a warrior by name. If not found, returns -1.
size_t locate_warrior(const string& name, const vector<Warrior>& warrior_list);

// Displays the current status of all warriors in the game.
void display_status(const vector<Warrior>& warrior_list);

// Overloading the output operator for the Warrior class.
ostream& operator<<(ostream& os, const Warrior& aWarrior){
    os << "Warrior: " << aWarrior.name << ", weapon: "
    << aWarrior.weapon << endl;
    return os;
};

// Overloading the output operator for the nested Weapon class.
ostream& operator<<(ostream& os, const Warrior::Weapon& aWeapon){
    os << aWeapon.weapon_name << ", " << aWeapon.strength;
    return os;
};

// Main function that prepares for and begins the simulation.
int main(){

    ifstream file;
    open_file(file);
    vector<Warrior> warrior_list;
    
    run_game(file, warrior_list);

    file.close();
    return 0;
};

void open_file(ifstream& file){
    file.open("warriors.txt");
    if (!file){
        cout << "File didn't open" << endl;
        exit(1);
    };
};

void run_game(ifstream& file, vector<Warrior>& warrior_list){
    string command;
    while(file >> command){
        if (command == "Warrior"){
            add_warrior(file, warrior_list);
        } else if (command == "Status"){
            display_status(warrior_list);
        } else if (command == "Battle"){
            prepare_battle(file, warrior_list);
        };
    };
};

void prepare_battle(ifstream& file, vector<Warrior>& warrior_list){
    string first_name;
    string second_name;
    file >> first_name >> second_name;

    size_t first_index{locate_warrior(first_name, warrior_list)};
    size_t second_index{locate_warrior(second_name, warrior_list)};

    if (first_index != -1 && second_index != -1){
        cout << first_name << " battles " << second_name << endl;
        battle(warrior_list[first_index], warrior_list[second_index]);
        return;
    };

    if (first_index == -1){
        cout << first_name << " doesn't exist" << endl;
    };

    if (second_index == -1){
        cout << second_name << " doesn't exist" << endl;
    };
};

void battle(Warrior& first_warrior, Warrior& second_warrior){
    // If both warriors are already dead
    if (first_warrior.get_strength() == 0 && second_warrior.get_strength() == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        return;
    }

    // If one of them is dead
    if (first_warrior.get_strength() == 0) {
        cout << "He's dead, " << second_warrior.get_name() << endl;
        return;
    }
    if (second_warrior.get_strength() == 0) {
        cout << "He's dead, " << first_warrior.get_name() << endl;
        return;
    }

    // If neither of them is dead, compute the battle result
    if (first_warrior.get_strength() > second_warrior.get_strength()) {
        cout << first_warrior.get_name() << " defeats " << second_warrior.get_name() << endl;
    } 
    else if (first_warrior.get_strength() < second_warrior.get_strength()) {
        cout << second_warrior.get_name() << " defeats " << first_warrior.get_name() << endl;
    } 
    else { // Equal strength leads to mutual destruction
        cout << "Mutual Annihilation: " << first_warrior.get_name()
             << " and " << second_warrior.get_name() << " die at each other's hands" << endl;
    };

    int first_warrior_strength{first_warrior.get_strength()};
    int second_warrior_strength{second_warrior.get_strength()};

    first_warrior.gets_hit(second_warrior_strength);
    second_warrior.gets_hit(first_warrior_strength);
};

void add_warrior(ifstream& file, vector<Warrior>& warrior_list){
    string warrior_name;
    string weapon_name;
    int weapon_strength;
    file >> warrior_name >> weapon_name >> weapon_strength;

    if (locate_warrior(warrior_name, warrior_list) != -1){
        cout << warrior_name << " already exists" << endl;
        return;
    };

    warrior_list.emplace_back(warrior_name, weapon_name, weapon_strength);
};

size_t locate_warrior(const string& name, const vector<Warrior>& warrior_list){
    for (size_t index{}; index < warrior_list.size(); index++){
        if (warrior_list[index].get_name() == name){
            return index;
        };
    };

    return -1;
};

void display_status(const vector<Warrior>& warrior_list){
    cout << "There are: " << warrior_list.size() << " warriors" << endl;
    for (const Warrior& aWarrior: warrior_list){
        cout << aWarrior;
    };
};
