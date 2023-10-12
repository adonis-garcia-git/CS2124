/*
  rec05-start.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Section {
     class TimeSlot {
          friend ostream& operator<<(ostream& os, const TimeSlot& aTimeSlot);

     public:
          TimeSlot(const string& aDay, unsigned int anHour) 
          : day(aDay), hour(anHour) {}

     private:
          const string day;
          const unsigned int hour;
     };

     class Record {
          friend ostream& operator<<(ostream& os, const Record& aRecord);

     public:
          Record(const string& aName) : name(aName), grades(14, -1) {}

          const string& getName() const {return name;} //?

          void updateGrade(int aGrade, int aWeek) {
               grades[aWeek - 1] = aGrade;
          }

     private:
          const string name;
          vector<int> grades;
     };

     friend ostream& operator<<(ostream& os, const Section& aSection);
     friend ostream& operator<<(ostream& os, const TimeSlot& aTimeSlot);
     friend ostream& operator<<(ostream& os, const Record& aRecord);

public:
     Section(const string& secName, const string& aDay, unsigned int anHour)
     : sec_name(secName), time_slot(aDay, anHour) {}

     void addStudent(const string& aName) {
          records.push_back(new Record(aName));
     }

     void addGrade(const string& aName, int aGrade, int aWeek) {
          for (size_t i{}; i < records.size(); i++) {
               if (records[i]->getName() == aName) {
                    records[i]->updateGrade(aGrade, aWeek);
                    break;
               }
          }
     }

     void reset() {
          for (size_t i{}; i < records.size(); i++) {
               delete records[i];
               records[i] = nullptr;
          }

          records.clear();
     }

     Section(const Section& anotherSection) 
     : sec_name(anotherSection.sec_name), time_slot{anotherSection.time_slot} {
          for (size_t i{}; i < (anotherSection.records).size(); i++) {
               records.push_back(new Record(*(anotherSection.records)[i]));
          }
     }

     ~Section() {
          cout << "Section " << sec_name << " is being deleted" << endl;
          for (size_t i{}; i < records.size(); i++) {
               cout << "Deleting " << records[i]->getName() << endl;
               delete records[i];
               records[i] = nullptr;
          }

          records.clear();
     }

     const string& getName() const {return sec_name;}

private:
     const string sec_name;
     const TimeSlot time_slot;
     vector<Record*> records;
};

class LabWorker {
     friend ostream& operator<<(ostream& os, const LabWorker& aLabWorker);

public:
     LabWorker(const string& aName) : name(aName), section(nullptr) {}

     void addSection(Section& aSection) {
          section = &aSection;
     }

     void addGrade(const string& aName, int aGrade, int aWeek) {
          if (!section) {
               return;
          }
          
          section->addGrade(aName, aGrade, aWeek);
     }

private:
     const string name;
     Section* section;
};

ostream& operator<<(ostream& os, const Section::TimeSlot& aTimeSlot) {
     // [Day: Tuesday, Start time: 4pm]
     unsigned int hour{aTimeSlot.hour};
     string pm_or_am{"am"};

     if (aTimeSlot.hour > 12) {
          hour -= 12;
          pm_or_am = "pm";
     }

     os << "[Day: " << aTimeSlot.day << ", Start time: "
          << hour << pm_or_am << "]";

     return os;
}

ostream& operator<<(ostream& os, const Section::Record& aRecord) {
     // Name: John, Grades: -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 
     os << "\nName: " << aRecord.name << ", Grades: ";

     for (size_t i{}; i < (aRecord.grades).size(); i++) {
          os << " " << (aRecord.grades)[i];
     }

     return os;
}

ostream& operator<<(ostream& os, const LabWorker& aLabWorker) {
     // Moe does not have a section
     if (!aLabWorker.section) {
          os << aLabWorker.name << " does not have a section" << endl;
     }

     else {
          os << aLabWorker.name << " has section " << *aLabWorker.section;
     }

     return os;
}

ostream& operator<<(ostream& os, const Section& aSection) {
     // Section: A2, Time slot: [Day: Tuesday, Start time: 4pm], Students: None
     os << "Section: " << aSection.sec_name << ", Time slot: " << aSection.time_slot
          << ", Students: ";

     if ((aSection.records).size() == 0) {
          os << "None";
          return os;
     }

     for (size_t i{}; i < (aSection.records).size(); i++) {
          os << *(aSection.records)[i];
     }

     return os;
}



// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";

    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main
