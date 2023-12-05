/*
Polynomial Class Header File
Adonis Garcia
*/

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <iostream>

class Polynomial {
    struct Node {
        int val = 0;
        Node* next = nullptr;
    };

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);

public:
    Polynomial();

    Polynomial(const std::vector<int>& input);

    Polynomial(const Polynomial& other);

    Polynomial& operator=(const Polynomial& other);

    ~Polynomial();

    Polynomial& operator+=(const Polynomial& other);

    void copy_higher_degree(const Node* node, int count);

    Polynomial operator+(const Polynomial& other);

    bool operator==(const Polynomial& other) const;

    bool operator!=(const Polynomial& other) const;

    int evaluate(int val) const;  

private:    
    Node* header;
    int degree;
};

#endif
