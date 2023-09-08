#include <iostream>

using namespace std;

int readFromUser()
{
    cout << "Enter an interger: ";
    int num{};
    cin >> num;

    return num;
}

int doubleNumber(int x)
{
    return x * 2;
}

int main()
{
    cout << doubleNumber(readFromUser()) << '\n';
}