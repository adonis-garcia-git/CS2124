#include "registrar.h"
#include "student.h"
#include "course.h"

using namespace std;

namespace BrooklynPoly {

Course::Course(const string& courseName) : name(courseName) {}

const string& Course::getName() const {
    return name;
}

bool Course::addStudent(Student* student){
    students.push_back(student);

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

    for (Student* student : aCourse.students){
        cout << student->getName() << " ";
    }

    return os;
}

}
