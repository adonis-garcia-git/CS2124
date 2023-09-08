#include <iostream>
#include "io.h"

using namespace std;

int readNumber()
{
    int num;
    cin >> num;
    return num;
}

void writeAnswer(int x, int y)
{
    cout << x << " + " << y << " = " << x + y << '\n';
}