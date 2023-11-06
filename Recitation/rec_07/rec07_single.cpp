/*
  rec07_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to implement the methods and
  fix the cyclic association.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse(); 

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

// class Registrar {
//     friend ostream& operator<<(ostream& os, const Registrar& rhs);
// public:
//     Registrar();
//     bool addCourse(const string&);
//     bool addStudent(const string&);
//     bool enrollStudentInCourse(const string& studentName,
//                                const string& courseName);
//     bool cancelCourse(const string& courseName);
//     void purge();

// private:
//     size_t findStudent(const string&) const;
//     size_t findCourse(const string&) const;

//     vector<Course*> courses;
//     vector<Student*> students;
// };

Registrar::Registrar(){};

bool Registrar::addCourse(const string& courseName){
    if (findCourse(courseName) != courses.size()){
        return false;
    }

    courses.push_back(new Course(courseName));
    
    return true;
}

bool Registrar::addStudent(const string& studentName){
    if (findStudent(studentName) != students.size()){
        return false;
    }

    students.push_back(new Student(studentName));
    
    return true;
}

bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName){
    size_t courseIndex{findCourse(courseName)};
    size_t studentIndex{findStudent(studentName)};

    if ((studentIndex == students.size()) || (courseIndex == courses.size())){
        return false;
    }
    
    Course* coursePointer{courses[courseIndex]};
    Student* studentPointer{students[studentIndex]};

    if (!coursePointer->addStudent(studentPointer)){
        return false;
    };
    
    if (!studentPointer->addCourse(coursePointer)){
        return false;
    };
    
    return true;
}

bool Registrar::cancelCourse(const string& courseName){
    size_t index{findCourse(courseName)};

    if (index == courses.size()){
        return false;
    }

    Course* coursePointer{courses[index]};

    coursePointer->removeStudentsFromCourse();
    delete coursePointer;
    coursePointer = nullptr;

    for (size_t i{index}; i < courses.size(); i++){
        courses[i] = courses[i+1];
        courses.pop_back();
    }

    return true;
}

void Registrar::purge(){
    for (Course* course : courses){
        delete course;
        course = nullptr;
    }

    courses.clear();

    for (Student* student : students){
        delete student;
        student = nullptr;
    }

    students.clear();
}

size_t Registrar::findStudent(const string& studentName) const {
    for (size_t i{}; i < students.size(); i++){
        if (students[i]->getName() == studentName){
            return i;
        }
    }

    return students.size();
}

size_t Registrar::findCourse(const string& courseName) const {
    for (size_t i{}; i < courses.size(); i++){
        if (courses[i]->getName() == courseName){
            return i;
        }
    }

    return courses.size();
}

ostream& operator<<(ostream& os, const Registrar& aRegistrar){
    os << "Registrar's Report\nCourses:" << endl;
    for (const Course* const course : aRegistrar.courses){
        os << *course << endl;
    }
    os << "Students:" << endl;
    for (const Student* const student : aRegistrar.students){
        os << *student << endl;
    }
    return os;
}

// class Student {
//     friend ostream& operator<<(ostream& os, const Student& rhs);
// public:
//     // Student methods needed by Registrar
//     Student(const string& name);
//     const string& getName() const;
//     bool addCourse(Course*);

//     // Student method needed by Course
//     void removedFromCourse(Course*);

// private:
//     string name;
//     vector<Course*> courses;
// };

Student::Student(const string& name) : name(name) {}

const string& Student::getName() const {
    return name;
}

bool Student::addCourse(Course* aCourse){
    for (const Course* course : courses){
        if (aCourse == course){
            return false;
        }
    }

    courses.push_back(aCourse);

    return true;
}

void Student::removedFromCourse(Course* course){
    size_t index;
    for (size_t i{}; i < courses.size(); i++){
        if (course == courses[i]){
            index = i;
            break;
        }
    }

    for (size_t i{index}; i < courses.size(); i++){
        courses[i] = courses[i+1];
    }

    courses.pop_back();
}

ostream& operator<<(ostream& os, const Student& aStudent){
    os << aStudent.name << ": ";

    if (aStudent.courses.size() == 0){
        os << "No Courses";
        return os;
    }

    for (const Course* course : aStudent.courses){
        cout << course->getName() << " ";
    }

    return os;
}

// class Course {
//     friend ostream& operator<<(ostream& os, const Course& rhs);
// public:
//     // Course methods needed by Registrar
//     Course(const string& courseName);
//     const string& getName() const;
//     bool addStudent(Student*);
//     void removeStudentsFromCourse(); 

// private:
//     string name;
//     vector<Student*> students;
// };

Course::Course(const string& courseName) : name(courseName) {}

const string& Course::getName() const {
    return name;
}

bool Course::addStudent(Student* aStudent){
    for (const Student* student : students){
        if (aStudent == student){
            return false;
        }
    }
    students.push_back(aStudent);

    return true;
}

void Course::removeStudentsFromCourse(){
    for (Student* student : students){
        student->removedFromCourse(this);
    }

    students.clear();
}

ostream& operator<<(ostream& os, const Course& aCourse){
    os << aCourse.name << ": ";

    if (aCourse.students.size() == 0){
        os << "No Students";
        return os;
    }

    for (const Student* student : aCourse.students){
        cout << student->getName() << " ";
    }

    return os;
}
