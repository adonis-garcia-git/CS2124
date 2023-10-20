#include "registrar.h"
#include "student.h"
#include "course.h"

using namespace std;

Registrar::Registrar(){};

bool Registrar::addCourse(const string& courseName){
    courses.push_back(new Course(courseName));
    
    return true;
}

bool Registrar::addStudent(const string& studentName){
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

    coursePointer->addStudent(studentPointer);
    studentPointer->addCourse(coursePointer);
    
    return true;
}

bool Registrar::cancelCourse(const string& courseName){
    size_t index{findCourse(courseName)};
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
        course->removeStudentsFromCourse();
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
