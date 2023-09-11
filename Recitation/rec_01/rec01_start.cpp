/*
  rec01_start.cpp
  Fall 2023
  jbs
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    std::cout << "hello" << '\n';


    // Task 2  Printing hello ...  Using "using namespace"
    cout << "hello" << '\n';


    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    // cout << "x is: " << x << '\n';
    

    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y{17};
    int z{2000000017};
    double pie{3.14159};
    cout << "x size is: " << sizeof(x) << '\n';
    cout << "y size is: " << sizeof(y) << '\n';
    cout << "z size is: " << sizeof(z) << '\n';
    cout << "pie size is: " << sizeof(pie) << '\n';

    
    // Task 5  Attempt to assign the wrong type of thing to a variable
    // x = "felix"
    // results in a syntax error which is a compilation error


    //
    // Conditions
    //

    // Task 6  Testing for a range
    if ((y >= 10) && (y <= 20))
    {
      cout << "y is in between 10 and 20" << '\n';
    }
    else
    {
      cout << "y is not in between 10 and 20" << '\n';
    }
    
    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
    for (int i{10}; i <= 20; i++)
    {
      cout << i << " ";
    }
    cout << endl;
    // Then with a while loop
    int j{10};
    while (j <= 20)
    {
      cout << j << " ";
      j++;
    }
    cout << endl;
    // Finally with a do-while loop
    int k{10};
    do 
    {
      cout << k << " ";
      k++;
    } while (k <= 20);
    cout << endl;


    // Task 8  Looping to successfully open a file, asking user for the name
    ifstream ifs;
    string name;
    do {
      cout << "File name: ";
      cin >> name;
      ifs.open(name);
    } while (!ifs);

    // Task 9  Looping, reading file word by "word".
    string word;
    while (ifs >> word)
    {
      cout << word << '\n';
    }
    ifs.close();

    // Task 10 Open a file of integers, read it in, and display the sum.
    ifstream int_file("integers.txt");
    int sum{};
    int num{};
    if (!int_file)
    {
      cerr << "Could not open file\n";
      exit(1);
    }
    while (int_file >> num)
    {
      sum += num;
    }
    cout << "The sum is: " << sum << '\n';
    int_file.close();


    // Task 11 Open and read a file of integers and words. Display the sum.
    ifstream mixed_file("mixed.txt");
    int sum2{};
    int num2{};
    if (!mixed_file)
    {
      cerr << "Could not open file\n";
      exit(1);
    }
    while (mixed_file >> num2)
    {
      sum2 += num2;
    }
    cout << "The sum is: " << sum2 << '\n';
    mixed_file.close(); //reading loop ends once it reaches a non int

    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> vectorOfInts;
    for (int i{10}; i <= 100; i+=2)
    {
      vectorOfInts.push_back(i);
    }
    
    // Task 13 Displaying the vector THREE times

    //         a) using the indices,
    for (size_t i{}; i < vectorOfInts.size(); i++)
    {
      cout << vectorOfInts[i] << " ";
    }
    cout << endl;

    //         b) using a "ranged for"
    for (int i: vectorOfInts)
    {
      cout << i << " ";
    }
    cout << endl;

    //         c) using indices again but backwards
    for (size_t i{vectorOfInts.size()}; i > 0; i--)
    {
      cout << vectorOfInts[i-1] << " ";
    }
    cout << endl;

    // Task 14. Initialize a vector with the primes less than 20. 
    vector<int> primesVector{2, 3, 5, 7, 11, 13, 17, 19};
    for (int i: primesVector)
    {
      cout << i << " ";
    }
}

