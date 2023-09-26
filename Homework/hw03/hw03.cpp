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

void open_file(ifstream& file);
void run_game(ifstream& file, vector<Warrior>& warrior_list);
void prepare_battle(ifstream& file);
void battle(Warrior& first_warrior, Warrior& second_warrior);
void add_warrior(ifstream& file);
void locate_warrior(const string& name, vector<Warrior>& warrior_list);
void display_status(vector<Warrior>& warrior_list);

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

    void gets_hit(int opponent_strength){
        weapon.take_damage(opponent_strength);
    };

    int get_strength() const {
        return weapon.get_weapon_strength();
    };

public:
    Warrior(const string& aName, const string& weapon_name, int strength)
    : name(aName), weapon(weapon_name, strength) {};

private:
    Weapon weapon;
    const string& name;
};

// overloading the output operator for the Warrior class
ostream& operator<<(ostream& os, const Warrior& aWarrior){
    cout << "Warrior: " << aWarrior.name << ", weapon: "
    << aWarrior.weapon << endl;
    return os;
};

// overloading the output operator for the nested Weapon class
ostream& operator<<(ostream& os, const Warrior::Weapon& aWeapon){
    cout << aWeapon.weapon_name << ", " << aWeapon.strength;
    return os;
};

// main function that prepares for and begins the simulation
int main(){
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
            add_warrior();
        } else if (command == "Status"){
            display_status(warrior_list);
        } else {
            prepare_battle(file);
        };
    };
};

void prepare_battle(ifstream& file){
    string first_name;
    string second_name;
    file >> first_name >> second_name;

    //left off here
};

void battle(Warrior& first_warrior, Warrior& second_warrior){

};

void add_warrior();
void locate_warrior(const string& name, vector<Warrior>& warrior_list);
void display_status(vector<Warrior>& warrior_list);
