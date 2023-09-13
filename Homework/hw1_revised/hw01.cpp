/*
Author: Adonis Garcia
File: hw01.cpp
Class: CS-2124
Purpose: decrypt encrypted file using caesar cypher
*/

#include <iostream>     //include I/O library
#include <fstream>      //include file I/O library
#include <string>       //include string library
#include <vector>       //include vector library
using namespace std; 

/*forward declare the relevant functions*/
char decrypt_letter(int rotation, char letter);
void decrypt_line(int rotation, string& line);
void decrypt_file(int rotation, vector<string>& vectorOfLines);
void display_decrypted_file(vector<string>& vectorOfLines);

/*initialize global variables*/
const int NUM_OF_LETTERS_IN_ALPHABET{26};

/*open encryted file, decrypt it, and then display values*/
int main()
{   
    //open file and check if opened successfully
    ifstream encrypted_file;
    encrypted_file.open("encrypted.txt");
    if (!encrypted_file){
        cerr << "Couldn't open file" << endl;
        exit(1);
    }

    //extract and save rotation steps
    int rotation;
    encrypted_file >> rotation;

    //save lines to a vector
    string line;
    vector<string> vectorOfLines;
    getline(encrypted_file, line); //necessary to skip first line
    while (getline(encrypted_file, line)){
        vectorOfLines.push_back(line);
    };

    decrypt_file(rotation, vectorOfLines);

    display_decrypted_file(vectorOfLines);

    return 0;
}

/*uses rotation to decrypt letter and returns decrypted letter*/
char decrypt_letter(int rotation, char letter)
{
    if (letter >= 'A' && letter <= 'Z'){
        letter -= rotation;
        if (letter < 'A'){
            letter += NUM_OF_LETTERS_IN_ALPHABET;
        }
    }
    return letter;
}

/*decrypts line by iterating through characters, decrypting each
individually, and mutating the given line reference*/
void decrypt_line(int rotation, string& line)
{   
    for (char& letter: line){
        letter = decrypt_letter(rotation, letter);
    }
}

/*decrypts file by decrypting each line individually and mutating
the lines in the original vector holding the file*/
void decrypt_file(int rotation, vector<string>& vectorOfLines){
    for (string& line: vectorOfLines){
        decrypt_line(rotation, line);
    }
}

/*iterates through the vector file backwards to successfully
display the decrypted code correctly*/
void display_decrypted_file(vector<string>& vectorOfLines){
    for (size_t index{vectorOfLines.size()}; index > 0; index--){
        cout << vectorOfLines[index - 1] << '\n';
    }
}
