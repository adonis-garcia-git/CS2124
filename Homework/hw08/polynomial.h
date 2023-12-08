/*
Polynomial Class Header File
Adonis Garcia
*/

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <iostream>

// The Polynomial class represents a mathematical polynomial.
class Polynomial {
    // Node structure used for linked list representation of the polynomial.
    struct Node {
        int val = 0;
        Node* next = nullptr;
    };

    // Overloads the output operator for the polynomial objects.
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);

public:
    // Default constructor. Creates a polynomial representative of just a 0.
    Polynomial();

    // Constructor that creates a polynomial from a vector of coefficients.
    Polynomial(const std::vector<int>& input);

    // Copy constructor. Creates a new polynomial as a copy of another.
    Polynomial(const Polynomial& other);

    // Copy assignment operator. Assigns one polynomial to another.
    Polynomial& operator=(const Polynomial& other);

    // Destructor. Frees the memory allocated by the polynomial.
    ~Polynomial();

    // Adds another polynomial to this polynomial.
    Polynomial& operator+=(const Polynomial& other);

    // Copies the higher degree terms from another polynomial node.
    void copy_higher_degree(const Node* node, int count);

    // Adds two polynomials and returns the result.
    Polynomial operator+(const Polynomial& other);

    // Compares two polynomials for equality.
    bool operator==(const Polynomial& other) const;

    // Compares two polynomials for inequality.
    bool operator!=(const Polynomial& other) const;

    // Evaluates the polynomial for a given value of x.
    int evaluate(int val) const;

    // Clears leading zeros in the polynomial representation.
    void clear_zeros();  

private:
    Node* header;  
    int degree;    
};

#endif
