/*
Author: Adonis Garcia
File: rec02.cpp
Purpose: sort chemicals from a file and display them
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

struct Chemical {
        int carbon;
        int hydrogen;
        vector<string> names;
    };

void open_stream(ifstream& file);
void fill_vector(ifstream& file, vector<Chemical>& chemicals);
void display_chemicals(const vector<Chemical>& chemicals);
void sort_chemicals(vector<Chemical>& chemicals);
size_t locate_chemical(int carbon, int hydrogen, const vector<Chemical>& chemicals);
void insert_info(int carbon, int hydrogren, const string& name, vector<Chemical>& chemicals);
void print_chemical(const Chemical& chemical);

int main(){

    ifstream file;
    vector<Chemical> chemicals;

    open_stream(file);
    fill_vector(file, chemicals);
    file.close();

    cout << endl << "Unsorted:" << endl;
    display_chemicals(chemicals);

    cout << endl << "Sorted: " << endl;
    sort_chemicals(chemicals);
    display_chemicals(chemicals);

    return 0;
}

void open_stream(ifstream& file){
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    file.open(filename);
    while (!file){
        file.clear();
        cout << "(INVALID) Enter filename: ";
        cin >> filename;
        file.open(filename);
    }
};

void fill_vector(ifstream& file, vector<Chemical>& chemicals){
    string name;
    int carbon;
    int hydrogen;
    char dummy;

    while (file >> name >> dummy >> carbon >> dummy >> hydrogen){
        insert_info(carbon, hydrogen, name, chemicals);
    };
};

void display_chemicals(const vector<Chemical>& chemicals){
    for (const Chemical& chemical: chemicals){
        print_chemical(chemical);
    };
};

void sort_chemicals(vector<Chemical>& chemicals){
    for (size_t i{}; i < chemicals.size(); i++){
        bool done{true};
        for (size_t j{}; j < chemicals.size()-1-i; j++){
            if (chemicals[j+1].carbon < chemicals[j].carbon){
                swap(chemicals[j+1], chemicals[j]);
                bool done{false};
            } else if (chemicals[j+1].carbon == chemicals[j].carbon){
                if (chemicals[j+1].hydrogen < chemicals[j].hydrogen){
                    swap(chemicals[j+1], chemicals[j]);
                    bool done{false};
                };
            };
        };
        if (done){
            break;
        };
    };
};

size_t locate_chemical(int carbon, int hydrogen, const vector<Chemical>& chemicals){
    for (size_t index{}; index < chemicals.size(); index++){
        if ((chemicals[index].carbon == carbon) && (chemicals[index].hydrogen == hydrogen)){
            return index;
        };
    };
    return chemicals.size();
};

void insert_info(int carbon, int hydrogen, const string& name, vector<Chemical>& chemicals){
    int index;
    index = locate_chemical(carbon, hydrogen, chemicals);

    if (index >= chemicals.size()){
        vector<string> names{name};
        Chemical formula;
        formula.carbon = carbon;
        formula.hydrogen = hydrogen;
        formula.names = names;
        chemicals.push_back(formula);
    } else {
        chemicals[index].names.push_back(name);
    }
};

void print_chemical(const Chemical& chemical){
    cout << "C" << chemical.carbon << "H" << chemical.hydrogen << " ";
    for (const string& name: chemical.names){
        cout << name << " ";
    };
    cout << endl;
};
