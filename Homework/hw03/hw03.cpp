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
class Warrior{
    class Weapon{
        friend ostream& operator<<(ostream& os, const Weapon& aWeapon);
    public:
        Weapon(const string& name, int strength)
        : weapon_name(name), strength(strength){};

        void take_damage(int strength_units){
            strength -= strength_units;
            if (strength < 0){
                strength = 0;
            };
        };

        int get_weapon_strength() const {
            return strength;
        }

    private:
        const string weapon_name;
        int strength;
    };

    friend ostream& operator<<(ostream& os, const Warrior& aWarrior);
    friend ostream& operator<<(ostream& os, const Weapon& aWeapon);

public:
    Warrior(const string& aName, const string& weapon_name, int strength)
    : name(aName), weapon(weapon_name, strength) {};

    const string& get_name() const {
        return name;
    };

    void gets_hit(int opponent_strength){
        weapon.take_damage(opponent_strength);
    };

    int get_strength() const {
        return weapon.get_weapon_strength();
    };

private:
    Weapon weapon;
    const string name;
};

void open_file(ifstream& file);
void run_game(ifstream& file, vector<Warrior>& warrior_list);
void prepare_battle(ifstream& file, vector<Warrior>& warrior_list);
void battle(Warrior& first_warrior, Warrior& second_warrior);
void add_warrior(ifstream& file, vector<Warrior>& warrior_list);
int locate_warrior(const string& name, const vector<Warrior>& warrior_list);
void display_status(const vector<Warrior>& warrior_list);

// overloading the output operator for the Warrior class
ostream& operator<<(ostream& os, const Warrior& aWarrior){
    os << "Warrior: " << aWarrior.name << ", weapon: "
    << aWarrior.weapon << endl;
    return os;
};

// overloading the output operator for the nested Weapon class
ostream& operator<<(ostream& os, const Warrior::Weapon& aWeapon){
    os << aWeapon.weapon_name << ", " << aWeapon.strength;
    return os;
};

// main function that prepares for and begins the simulation
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

    int first_index{locate_warrior(first_name, warrior_list)};
    int second_index{locate_warrior(second_name, warrior_list)};

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

int locate_warrior(const string& name, const vector<Warrior>& warrior_list){
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
