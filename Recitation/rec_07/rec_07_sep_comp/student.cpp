#include "registrar.h"
#include "student.h"
#include "course.h"

using namespace std;

Student::Student(const string& name) : name(name) {}

const string& Student::getName() const {
    return name;
}

bool Student::addCourse(Course* course){
    courses.push_back(course);

    return true;
}

void Student::removedFromCourse(Course* course){
    size_t index;
    for (size_t i{}; i < courses.size(); i++){
        if (course == courses[i]){
            index = i;
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

    for (Course* course : aStudent.courses){
        cout << course->getName() << " ";
    }

    return os;
}
