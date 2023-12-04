// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    struct Node {
        int data = 0;
        Node* next = nullptr;
        Node* prior = nullptr;
    };

    friend ostream& operator<<(ostream& os, const List& rhs) {
        Node* curr = rhs.header->next;
        while (curr != rhs.trailer){
            os << curr->data << " ";
            curr = curr->next;
        }
        return os;
    }

public:
    List() : list_size(0), header(new Node), trailer(new Node) {
        header->next = trailer;
        trailer->prior = header;
    }

    List(const List& other) : list_size(0), header(new Node), trailer(new Node) {
        header->next = trailer;
        trailer->prior = header;
        for (int x : other){
            push_back(x);
        }
    }

    List& operator=(const List& other) {
        if (this != &other){
            clear();
            for (int x : other){
                push_back(x);
            }
        }
        return *this;
    }

    ~List(){
        clear();
        delete header;
        delete trailer;
        cout << "~List()" << endl;
    }

    class Iterator {
        friend List;
    public:
        Iterator(Node* where) : where(where) {};

        bool operator==(const Iterator& other) const {
            return where == other.where;
        }

        bool operator!=(const Iterator& other) const {
            return where != other.where;
        }

        Iterator& operator++() {
            where = where->next;
            return *this;
        }

        Iterator& operator--() {
            where = where->prior;
            return *this;
        }

        int& operator*() const {
            return where->data;
        }

    private:
        Node* where;
    };

    Iterator begin() {
        Iterator iter(header->next);
        return iter;
    }

    Iterator end() {
        Iterator iter(trailer);
        return iter;
    }

    class Const_Iterator {
        // friend List; // not necessary
    public:
        Const_Iterator(Node* where) : where(where) {};

        bool operator==(const Const_Iterator& other) const {
            return where == other.where;
        }

        bool operator!=(const Const_Iterator& other) const {
            return where != other.where;
        }

        Const_Iterator& operator++() {
            where = where->next;
            return *this;
        }

        Const_Iterator& operator--() {
            where = where->prior;
            return *this;
        }

        int operator*() const {
            return where->data;
        }

    private:
        const Node* where;
    };

    Const_Iterator begin() const {
        Const_Iterator iter(header->next);
        return iter;
    }

    Const_Iterator end() const {
        Const_Iterator iter(trailer);
        return iter;
    }

    Iterator insert(Iterator iter, int data) {
        Node* after = iter.where;
        Node* before = after->prior;
        Node* added = new Node{data}; // could have all been done here
        before->next = after->prior = added;
        added->prior = before;
        added->next = after;
        list_size++;
        return added;
        //return Iterator(added);
    }

    Iterator erase(Iterator iter) {
        Node* curr = iter.where;
        Node* after = curr->next;
        Node* before = curr->prior;
        delete curr;
        before->next = after;
        after->prior = before;
        list_size--;
        return after;
    }

    void push_back(int data) {
        Node* prev = trailer->prior;
        Node* added = new Node{data};
        prev->next = trailer->prior = added;
        added->prior = prev;
        added->next = trailer;
        list_size++;
    }

    void pop_back() {
        if (!list_size) {return;}
        Node* new_last = trailer->prior->prior;
        delete trailer->prior;
        new_last->next = trailer;
        trailer->prior = new_last;
        list_size--;
    }

    void push_front(int data) {
        Node* after = header->next;
        Node* added = new Node{data};
        header->next = after->prior = added;
        added->prior = header;
        added->next = after;
        list_size++;
    }

    void pop_front() {
        if (!list_size) {return;}
        Node* new_front = header->next->next;
        delete header->next;
        new_front->prior = header;
        header->next = new_front;
        list_size--;
    }

    void clear() {
        while (list_size) {
            pop_back();
        }
    }

    int& operator[](int index){
        Node* curr = header;
        for (size_t i = 0; i < index + 1; i++) {
            curr = curr->next;
        }
        return curr->data;
    }

    int operator[](int index) const {
        Node* curr = header;
        for (size_t i = 0; i < index + 1; i++) {
            curr = curr->next;
        }
        return curr->data;
    }

    int front() const {
        return header->next->data;
    }

    int& front() {
        return header->next->data;
    }

    int back() const {
        return trailer->prior->data;
    }

    int& back() {
        return trailer->prior->data;
    }

    int size() const {return list_size;}

private:
    Node* header;
    Node* trailer;
    int list_size;
};

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// // The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList) {
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << "Leaving doNothing\n";
}    

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);
    

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the Iterator type directly:\n";
    // Note you can choose to nest the Iterator class or not, your choice.
    //for (Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
    
    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}
