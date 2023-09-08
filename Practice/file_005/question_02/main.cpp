#include <iostream>
#include "io.h"

using namespace std;

int main()
{
    cout << "Enter first number: ";
    int num1{readNumber()};
    cout << "Enter second number: ";
    int num2{readNumber()};

    writeAnswer(num1, num2);

    return 0;
}