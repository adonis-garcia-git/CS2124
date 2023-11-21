#include <iostream>
#include <string>
using namespace std;

// class Movie {
// public:
//     Movie() {
//         title = "Casablanca";
//         length = 17;
//     }

//     Movie(int length, string title = "Forrest Gump")
//         : title(title), length(length) {}

//     void display() {
//         cout << title << ": " << length << " minutes" << endl;
//     }

// private:
//     string title;
//     int length;
// };

// int main() {
//     Movie mov;
//     mov = 42;
//     mov.display();
// }

// class Base {
// public:
//     void show(int i) {
//         std::cout << "Base::show(int) called with " << i << std::endl;
//     }
// };

// class Derived : public Base {
// public:
//     // This overloads Base::show(int), but does not override it.
//     void show(double d) {
//         std::cout << "Derived::show(double) called with " << d << std::endl;
//     }


// };

// int main() {
//     Derived obj;
//     obj.show(10);    // Calls Base::show(int)
//     obj.show(3.14);  // Calls Derived::show(double)

//     // To explicitly call Base::show from a Derived object
//     obj.Base::show(10);
// }

// const int INIT_BALANCE = 200;

// class Account {
// public:
//     Account() : balance(INIT_BALANCE) {}

//     virtual void display_balance() {
//         cout << "Balance is " << balance; // Line 1
//     }

// protected:
//     int get_balance() const { return balance; } // Line 2

// private:
//     int balance;
// };

// class CheckingAccount: public Account {
// public:
//     void display_balance() const override { // Line 3
//         cout << "Checking balance is " << get_balance(); // Line 4
//     }
// };

// int main() {
//     Account acct; // Line 4
//     CheckingAccount ca; // Line 5
//     acct = ca; // Line 6
//     acct.display_balance(); // Line 7
// }

// const int NUM = 5;

// int main() {
//     int val = 7;
//     int* arr = new int[NUM];
//     for (int i = 0; i < NUM; ++i) {
//         arr[i] = val + i;
//     }

//     int* ptr_p = arr + NUM - 2;
//     int* ptr_q = ptr_p + 1;
//     cout << "X: " << *ptr_q << endl;

//     *ptr_p = val;
//     ++ptr_p;
//     cout << "Y: " << *ptr_p << endl;
// }

// class Bird {
// public:
//     virtual void chirp() { cout << "chirp"; } // Line 1
// };

// class Parrot : public Bird {
// public:
//     void chirp(string phrase) { cout << phrase; } // Line 2
// };

// int main() {
//     Parrot* ptr = new Bird(); // Line 3
//     ptr->chirp("Hello"); // Line 4
// }

// class Dinosaur {
// public:
//     void attack(Dinosaur& dino) {} // Line A
// };

// class TRex : public Dinosaur {
//     void attacker(Dinosaur& dino){
//         attack(dino);
//     }
// };

// class Raptor : public Dinosaur {};

// int main() {
//     TRex t; // Line B
//     Raptor rappy; // Line C
//     rappy.attack(t); // Line D
// }

// class EyeWear {
// public:
//     void set_strength(int s) { strength = s; } // Line 1
//     int get_strength() const { return strength; } // Line 2
// private:
//     int strength;
// };

// class ContactLens : public EyeWear {
// public:
//     void set_diameter(double d) { dia = d; } // Line 3
//     double get_diameter() const { return dia; } // Line 4
// private:
//     double dia;
// };

// void output(EyeWear& ew) {
//     cout << "Diameter is " << ew.get_diameter(); // Line 5
// }

// int main() {
//     ContactLens obj; // Line 6
//     obj.set_strength(5); // Line 7
//     obj.set_diameter(8.2); // Line 8
//     output(obj); // Line 9
// }


class Pet {
public:
    Pet() { cout << "A "; }
    ~Pet() { cout << "B "; }
};

class Bird : public Pet {
public:
    Bird() { cout << "C "; }
    ~Bird() { cout << "D "; }
};

class Parrot : public Bird {
public:
    Parrot() { cout << "E "; }
    virtual ~Parrot() { cout << "F "; }
};

int main() {
    Bird* ptr = new Parrot();
    delete ptr;
}

