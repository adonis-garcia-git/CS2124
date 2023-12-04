#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next = nullptr;
};

void listPrint(const Node* headPtr) {
    const Node* curr = headPtr;
    while (curr != nullptr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

int listSize(const Node* headPtr) {
    int count = 0;
    const Node* curr = headPtr;
    while (curr != nullptr) {
        ++count;
        curr = curr->next;
    }
    return count;
}

void listAddHead(Node*& headPtr, int data) {
    // // Create new Node
    // Node* theNewNode = new Node{data};
    // // Make new node point to old head
    // theNewNode->next = headPtr;
    // Node* theNewNode = new Node{data, headPtr}; // better
    // Make the head point to new node
    // headPtr = theNewNode;
    headPtr = new Node{data, headPtr}; // best
}

Node* listFindTail(Node* headPtr) {
    if (!headPtr) return nullptr;
    Node* curr = headPtr;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    return curr;
}

void listAddTail(Node*& headPtr, int data) {
    if (!headPtr) {
        headPtr = new Node{data};
    } else {
    listFindTail(headPtr)->next = new Node{data};
    }
}

void listRemoveHead(Node*& headPtr) {
    if (!headPtr) return;
    // remember the old second node
    Node* oldSecond = headPtr->next;
    // get rid of old one
    delete headPtr;
    // make the head point to old second node
    headPtr = oldSecond;
}

void listRemoveTail(Node*& headPtr) {
    if (!headPtr) return;
    if (!headPtr->next) {
        delete headPtr;
        headPtr = nullptr;
        return;
    }

    Node* curr = headPtr;
    while (curr->next->next != nullptr) {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;

}
