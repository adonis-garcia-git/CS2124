/*
  abstract.cpp
  Inclass Sec A
*/

#include <iostream>
using namespace std;

class Shape { // Abstract class
public:
    Shape(int x, int y) : x(x), y(y) {}
    void move(int x, int y) { this->x = x;  this->y = y; }
    //virtual void draw() { /*cout << "Default stuff... "; */}
    virtual void draw() = 0;  // abstract method / pure virtual method / must be overwritten / makes class abstract
    void commonDrawingCode() { cout << "drawing a "; }
private:
    int x, y;
};

void Shape::draw() { cout << "drawing a "; } // illegal since pure virtual funcs cannot be defined

class Triangle : public Shape {
public:
    Triangle(int x, int y) : Shape(x,y) {}
    void draw() override {
	//cout << "drawing a Triangle\n";
	//	commonDrawingCode();
	Shape::draw();
	cout << "Triangle\n";
    }
};

class Equilateral : public Triangle {
public:
    Equilateral(int x, int y) : Triangle(x,y) {}
};

class Circle : public Shape {
public:
  Circle(int x, int y) : Shape(x,y) {}
};

int main() {
    Shape aShape(3,4); // Won't compile // can't make instance of abstract class
    Triangle tri(3,4);
    tri.draw();
    Equilateral(12, 13); // FIne
    Circle circ(10,10);  // Won't compile // has to override the pure virtual function draw
    circ.draw();
}
