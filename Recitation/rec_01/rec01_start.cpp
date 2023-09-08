/*
  rec01_start.cpp
  Fall 2023
  jbs
*/
#include <iostream>
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
    using namespace std;
    cout << "hello" << '\n';


    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    cout << "x is: " << x << '\n';
    

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


    // Task 8  Looping to successfully open a file, asking user for the name
    

    // Task 9  Looping, reading file word by "word".


    // Task 10 Open a file of integers, read it in, and display the sum.


    // Taks 11 Open and read a file of integers and words. Display the sum.


    //
    // Vectors
    //

    // Task 12 Filling a vector of ints

    
    // Task 13 Displaying the vector THREE times
    //         a) using the indices,

    //         b) using a "ranged for"

    //         c) using indices again but backwards


    // Task 14. Initialize a vector with the primes less than 20. 

    
}

