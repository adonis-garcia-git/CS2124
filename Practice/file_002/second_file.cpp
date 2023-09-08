#include <iostream>

using namespace std;

int main()
{
    cout << "Enter an integer: ";

    int num_one{};
    cin >> num_one;

    cout << "Enter another integer: ";

    int num_two{};
    cin >> num_two;

    cout << num_one << " + " << num_two << " is " << num_one + num_two << '\n';
    cout << num_one << " - " << num_two << " is " << num_one - num_two << '\n';

    return 0;
}

