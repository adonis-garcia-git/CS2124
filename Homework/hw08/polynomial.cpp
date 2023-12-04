/*
Polynomial Class CPP File
Adonis Garcia
*/

#include "polynomial.h"
using namespace std;

ostream& operator<<(ostream& os, const Polynomial& rhs){
    Polynomial::Node* curr = rhs.header->next;
    int count = rhs.degree;
    bool began = false;
    while (curr){
        if (curr->val != 0){
            if (began) os << "+";
            if (count) {
                began = true;
                if (curr->val == -1) os << "-";
                if (curr->val != 1 && curr->val != -1) os << curr->val;
                os << "x";
                if (count != 1) os << "^" << count;
            }
            if (!count) {
                os << curr->val;
            }
        }
        curr = curr->next;
        count--;
    }
    return os;
}

Polynomial::Polynomial()
: header(new Node{0, new Node{0}}), degree(0) {}

Polynomial::Polynomial(const vector<int>& input) 
: header(new Node), degree(0) {
    Node* curr = header;
    for (const int x : input){
        curr->next = new Node{x};
        curr = curr->next;
        degree++;
    }
    if (degree) degree--;
}

Polynomial& Polynomial::operator+=(const Polynomial& other){
    Node* curr = header->next;
    Node* other_curr = other.header->next;
    int count;
    if (other.degree > degree){
        count = other.degree - degree;
        copy_higher_degree(other.header->next, count);
        while (count) {
            other_curr = other_curr->next;
            count--;
        }
    }
    if (degree > other.degree){
        count = degree - other.degree;
        while (count) {
            curr = curr->next;
            count--;
        }
    }
    while (curr) {
        curr->val += other_curr->val;
        curr = curr->next;
        other_curr = other_curr->next;
    }
    return *this;
}

void Polynomial::copy_higher_degree(const Node* node, int count){
    Node* before = header;
    Node* after = before->next;
    const Node* curr = node;
    degree+=count;
    while (count){
        before->next = new Node{curr->val};
        before = before->next;
        curr = curr->next;
        count--;
    }
    before->next = after;
}   

Polynomial Polynomial::operator+(const Polynomial& other){
    Polynomial result; // could be improved with copy construct
    result += *this;
    result += other;
    return result;
}

bool Polynomial::operator==(const Polynomial& other) const{
    Node* curr = header->next;
    Node* other_curr = other.header->next;
    if (degree != other.degree) return false;
    while (curr) {
        if (curr->val != other_curr->val) return false;
        curr = curr->next;
        other_curr = other_curr->next;
    }
    return true;
}
