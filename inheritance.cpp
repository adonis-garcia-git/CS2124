#include <iostream>
#include <vector>

using namespace std;

class Pet {
public:
    Pet(const string& name) : name(name) {}

    // void eat() {cout << "eating" << endl;}
    virtual void eat() {cout << "eating" << endl;}

private:
    string name;
};

class Cat : public Pet {
public:
    // Cat(const string& name) : name(name) {}  // Cat does not itself have a name field
    Cat(const string& name) : Pet(name) {}      // Calling the base constructor

    // void eat() {cout << "cat eating" << endl;} // redifined
    void eat() {
        cout << "cat";
        // eat();                               // results in infinite recursion
        Pet::eat();                             // qualified
    }

    void purr() {cout << "purrr" << endl;}
};

class Slug : public Pet {};

class Roach : public Pet {
    using Pet::Pet;                             // pulling down base constructor
};

// ======================

// void someFunc(Pet aPet){
void someFunc(Pet& aPet){
    cout << "someFunc: ";
    aPet.eat();
}

int main(){
    Pet peeve("Peeve");
    peeve.eat();
    someFunc(peeve);                            // no polymorphism

    Cat felix("Felix");
    felix.eat();                                // code reuse
    someFunc(felix);                            // Barbara Liskov: principal of substitutability

    Roach archie("Archie");
    archie.eat();
    someFunc(archie);

    vector<Pet> menagerie;
    menagerie.push_back(peeve);
    menagerie.push_back(felix);
    menagerie.push_back(archie);
    for (size_t index = 0; index < menagerie.size(); index++){
        menagerie[index].eat();
    }

    vector<Pet*> menagerie2;
    menagerie2.push_back(&peeve);
    menagerie2.push_back(&felix);
    menagerie2.push_back(&archie);
    for (size_t index = 0; index < menagerie2.size(); index++){
        menagerie2[index]->eat();
    }

    peeve = archie;                             // compiles - but...
    archie = peeve;                             // doesn't compile
}
