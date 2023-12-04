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

    Polynomial& operator+=(const Polynomial& other);

    void copy_higher_degree(const Node* node, int count);

    Polynomial operator+(const Polynomial& other);

    bool operator==(const Polynomial& other) const;

private:
    Node* header;
    int degree;
};

#endif
