/*
Author: Adonis Garcia
File: hw02.cpp
Class: CS-2124
Purpose: simulating medieval times warrier game
*/

#include <iostream>     //include I/O library
#include <fstream>      //include file I/O library
#include <string>       //include string library
#include <vector>       //include vector library
using namespace std;

struct Warrior{
    string name;
    int strength;
};

void open_file(ifstream& command_file);
void run_game(ifstream& command_file, vector<Warrior>& warriors);
void command_parser(const string& command, ifstream& command_file, vector<Warrior>& warriors);
void add_warrior(vector<Warrior>& warriors, ifstream& command_file);
void display_status(const vector<Warrior>& warriors);
void prepare_battle(vector<Warrior>& warriors, ifstream& command_file);
int locate_warrior(const string& warrior, vector<Warrior> warriors);
void battle(Warrior& first_warrior, Warrior& second_warrior);


int main(){

    vector<Warrior> warriors;

    ifstream command_file;
    open_file(command_file);
    run_game(command_file, warriors);    


    return 0;
}

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

    Warrior warrior;
    warrior.name = name;
    warrior.strength = strength;

    warriors.push_back(warrior);
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

    battle(warriors[first_index], warriors[second_index]);
};

int locate_warrior(const string& warrior, vector<Warrior> warriors){
    for (size_t index{}; index < warriors.size(); index++){
        if (warriors[index].name == warrior){
            return index;
        };
    };
    cerr << warrior << " not found";
    exit(1); 
};

void battle(Warrior& first_warrior, Warrior& second_warrior){
    if ((first_warrior.strength == 0) && (second_warrior.strength == 0)){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    } else if (first_warrior.strength == 0){
        cout << "He's dead, " << second_warrior.name << endl;
    } else if (second_warrior.strength == 0){
        cout << "He's dead, " << first_warrior.name << endl;
    } else if (first_warrior.strength > second_warrior.strength){
        first_warrior.strength -= second_warrior.strength;
        second_warrior.strength = 0;
        cout << first_warrior.name << " defeats " << second_warrior.name << endl;
    } else if (first_warrior.strength < second_warrior.strength){
        second_warrior.strength -= first_warrior.strength;
        first_warrior.strength = 0;
        cout << second_warrior.name << " defeats " << first_warrior.name << endl;
    } else {
        first_warrior.strength = 0;
        second_warrior.strength = 0;
        cout << "Mutual Annihilation: " << first_warrior.name;
        cout << " and " << second_warrior.name << " die at each other's hands" << endl;
    };
};