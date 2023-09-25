/*
Author: Adonis Garcia
File: hw02.cpp
Class: CS-2124
Purpose: simulating medieval times warrier game using structs
*/

#include <iostream>     //include I/O library
#include <fstream>      //include file I/O library
#include <string>       //include string library
#include <vector>       //include vector library
using namespace std;

struct Warrior{
    string name;
    int strength{};
};

// Opens the file containing warrior commands and checks for successful opening
void open_file(ifstream& command_file);

// Executes the game by continuously reading and processing commands from the file
void run_game(ifstream& command_file, vector<Warrior>& warriors);

// Determines the command type and directs to the corresponding function for processing
void command_parser(const string& command, ifstream& command_file, vector<Warrior>& warriors);

// Adds a new warrior to the warriors vector after ensuring the warrior doesn't already exist
void add_warrior(vector<Warrior>& warriors, ifstream& command_file);

// Displays the total number of warriors and their individual names and strengths
void display_status(const vector<Warrior>& warriors);

// Prepares two warriors for a battle by fetching their names and triggering the battle
void prepare_battle(vector<Warrior>& warriors, ifstream& command_file);

// Searches for a warrior in the warriors vector by name and returns its index or -1 if not found
int locate_warrior(const string& warrior, const vector<Warrior> warriors);

// Simulates a battle between two warriors, adjusting their strengths accordingly
// and printing out the outcome of the battle
void battle(Warrior& first_warrior, Warrior& second_warrior);


int main(){
    vector<Warrior> warriors;

    ifstream command_file;
    open_file(command_file);
    run_game(command_file, warriors);    

    command_file.close();

    return 0;
};

void open_file(ifstream& command_file){
    command_file.open("warriors.txt");
    if (!command_file){
        cerr << "File didn't open";
        exit(1);
    };
};

void run_game(ifstream& command_file, vector<Warrior>& warriors){
    string command;
    while (command_file >> command){
        command_parser(command, command_file, warriors);
    };
};

void command_parser(const string& command, ifstream& command_file, vector<Warrior>& warriors){
    if (command == "Warrior"){
        add_warrior(warriors, command_file); 
    } else if (command == "Status"){
        display_status(warriors);
    } else {
        prepare_battle(warriors, command_file);
    };
};

void add_warrior(vector<Warrior>& warriors, ifstream& command_file){
    string name;
    int strength;
    command_file >> name >> strength;

    if (locate_warrior(name, warriors) != -1){
        cout << name << "already exists" << endl;
    } else {
        Warrior warrior{name, strength};
        warriors.push_back(warrior);
    };

};

void display_status(const vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (const Warrior& warrior: warriors){
        cout << "Warrior: " << warrior.name << ", ";
        cout << "strength: " << warrior.strength << endl;
    };
};

void prepare_battle(vector<Warrior>& warriors, ifstream& command_file){
    string first_warrior;
    string second_warrior;
    command_file >> first_warrior >> second_warrior;

    cout << first_warrior << " battles " << second_warrior << endl;

    int first_index{locate_warrior(first_warrior, warriors)};
    int second_index{locate_warrior(second_warrior, warriors)};

    // If both warriors exist
    if (first_index != -1 && second_index != -1){
        battle(warriors[first_index], warriors[second_index]);
        return;
    }
    
    // If one of them doesn't exist
    if (first_index == -1){
        cout << first_warrior << " doesn't exist" << endl;
    } else {
        cout << second_warrior << " doens't exist" << endl;
    };
};

int locate_warrior(const string& warrior, const vector<Warrior> warriors){
    for (size_t index{}; index < warriors.size(); index++){
        if (warriors[index].name == warrior){
            return index;
        };
    };
    
    return -1; 
};

void battle(Warrior& first_warrior, Warrior& second_warrior) {
    // If both warriors are already dead
    if (first_warrior.strength == 0 && second_warrior.strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        return;
    }

    // If one of them is dead
    if (first_warrior.strength == 0) {
        cout << "He's dead, " << second_warrior.name << endl;
        return;
    }
    if (second_warrior.strength == 0) {
        cout << "He's dead, " << first_warrior.name << endl;
        return;
    }

    // If neither of them is dead, compute the battle result
    if (first_warrior.strength > second_warrior.strength) {
        first_warrior.strength -= second_warrior.strength;
        second_warrior.strength = 0;
        cout << first_warrior.name << " defeats " << second_warrior.name << endl;
    } 
    else if (first_warrior.strength < second_warrior.strength) {
        second_warrior.strength -= first_warrior.strength;
        first_warrior.strength = 0;
        cout << second_warrior.name << " defeats " << first_warrior.name << endl;
    } 
    else { // Equal strength leads to mutual destruction
        first_warrior.strength = 0;
        second_warrior.strength = 0;
        cout << "Mutual Annihilation: " << first_warrior.name
             << " and " << second_warrior.name << " die at each other's hands" << endl;
    };
};
