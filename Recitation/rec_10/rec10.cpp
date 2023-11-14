/*
  rec10_start.cpp
  Starting code 23S
 */

#include <iostream>
#include <vector>
using namespace std;

class Instrument {
    friend ostream& operator<<(ostream& os, const Instrument& rhs){
        rhs.identity(os);
        return os;
    }
    
public:
    void intro() const{
        cout << "To make a sound... ";
    }

    virtual void play() = 0;

    virtual void identity(ostream& os) const = 0;

    virtual void makeSound() const = 0;
};



// 
// Musician class as provided to the students. Requires an Instrument class.
// 
class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound(); 
        else cerr << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};

class MILL {
    friend ostream& operator<<(ostream& os, const MILL& rhs){
        os << "The MILL has the following instruments: ";
        bool empty = true;
        for (const Instrument* item : rhs.collection){
            if (item){
                os << "\n\t" << *item;
                empty = false;
            }
        }
        if (empty) os << "None";
        return os;
    }

public:
    void receiveInstr(Instrument& rhs){
        rhs.makeSound();
        for (size_t i = 0; i < collection.size(); i++){
            if (!collection[i]){
                collection[i] = &rhs;
                return;
            }
        }

        collection.push_back(&rhs);
    }

    void dailyTestPlay() const {
        for (const Instrument* item : collection){
            if (item){
                item->makeSound();
            }
        }
    }

    Instrument* loanOut() {
        for (size_t i = 0; i < collection.size(); i++){
            if (collection[i]){
                Instrument* copy = collection[i];
                collection[i] = nullptr;
                return copy;
            }
        }
        return nullptr;
    }

private:
    vector<Instrument*> collection;    
    
};

class Brass : public Instrument {
public:
    Brass(unsigned size) : size(size) {}

    void makeSound() const {
        Instrument::intro();
        cout << "blow on a mouthpiece of size " << size << endl;
    }

protected:
    unsigned getSize() const {
        return size;
    }

private:
    unsigned size;
};

class Trombone : public Brass {
public:
    Trombone(unsigned size) : Brass(size) {}

    void play() {
        cout << "Blat";
    }

    void identity(ostream& os) const {
        os << "Trombone: " << getSize();
    }
};

class Trumpet : public Brass {
public:
    Trumpet(unsigned size) : Brass(size) {}

    void play() {
        cout << "Toot";
    }

    void identity(ostream& os) const {
        os << "Trumpet: " << getSize();
    }
};

class String : public Instrument {
public:
    String(unsigned pitch) : pitch(pitch) {}

    void makeSound() const {
        Instrument::intro();
        cout << "bow a string with pitch " << pitch << endl;
    }

protected:
    unsigned getPitch() const {
        return pitch;
    }

private:
    const unsigned pitch;
};

class Violin : public String {
public:
    Violin(unsigned pitch) : String(pitch) {}

    void play() {
        cout << "Screech";
    }

    void identity(ostream& os) const {
        os << "Violin: " << getPitch();
    }
};

class Cello : public String {
public:
    Cello(unsigned pitch) : String(pitch) {}

    void play() {
        cout << "Squawk";
    }

    void identity(ostream& os) const {
        os << "Cello: " << getPitch();
    }
};

class Percussion : public Instrument {
public:
    void makeSound() const {
        Instrument::intro();
        cout << "hit me!" << endl;
    }
};

class Drum : public Percussion {
public:
    void play() {
        cout << "Boom";
    }

    void identity(ostream& os) const {
        os << "Drum";
    }
};

class Cymbal : public Percussion {
public:
    void play() {
        cout << "Crash";
    }

    void identity(ostream& os) const {
        os << "Cymbal";
    }
};

class Orch {
public:
    void addPlayer(Musician& rhs){
        orchestra.push_back(&rhs);
    }

    void play() {
        for (Musician* artist : orchestra){
            artist->play();
        }
        cout << endl;
    }
private:
    vector<Musician*> orchestra;
};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";
  
    cout << "Daily test ----------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    groucho.testPlay();	
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();
    harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
       mill.dailyTestPlay();
  
    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;

    //
    // PART TWO
    //
    
    cout << "\nP A R T  T W O\n";
    
    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;
}

