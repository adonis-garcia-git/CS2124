
/*
  1.inheritance.cpp
  Section Base

  Code reuse, principle of substitutability, polymorphism
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Pet {
public:
    virtual void eat() { cout << "eating" << endl; }
    // void eat() { cout << "eating" << endl; }

    virtual ~Pet() {}
};

class Cat : public Pet {
public:
    //void eat() { cout << "Cat eating" << endl; }
    void eat() {
	cout << "Cat ";
	Pet::eat(); // qualified because otherwise would be recursive;
    }
    void purr() { cout << "purrr\n"; }
};

class Slug : public Pet { };

class Roach : public Pet { };

// =============

//void someFunc(Pet aPet) {
void someFunc(Pet& aPet) {
    cout << "someFunc: ";
    aPet.eat();
}

int main() {
    cout << "Peeve\n";
    Pet peeve;
    peeve.eat();
    someFunc(peeve);

    cout << "Felix\n";
    Cat felix;
    felix.eat();             // code reuse
    someFunc(felix);         // Barbara Liskov: principle of substitutablity

    cout << "Archie\n";
    Roach archie;
    archie.eat();             // code reuse
    someFunc(archie);         // Barbara Liskov: principle of substitutablity

    cout << "Using menagerie\n";
    vector<Pet> menagerie;
    menagerie.push_back(peeve);
    menagerie.push_back(felix);
    menagerie.push_back(archie);
    for (size_t index = 0; index < menagerie.size(); ++index) {
	menagerie[index].eat();
    }

    cout << "Using menagerieV2\n";
    vector<Pet*> menagerieV2;
    menagerieV2.push_back(&peeve);
    menagerieV2.push_back(&felix);
    menagerieV2.push_back(&archie);
    for (size_t index = 0; index < menagerieV2.size(); ++index) {
	menagerieV2[index]->eat();
    }

    peeve = archie; // compiles - but...
    // felix = peeve; // NO!
}
