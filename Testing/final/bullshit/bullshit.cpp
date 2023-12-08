#include <iostream>
using namespace std;

bool isEven(int val) {return val % 2 == 0;}

template <typename Iter, typename Pred>
int count_if(Iter start, Iter end, Pred pred){
    int count = 0;
    while (start != end){
        if (pred(*start)) count++;
        start++;
    }
    return count;
}

int main(){
    int arr[] = {2,5,2,4,5,7,2};
    cout << count_if(arr, arr+8, isEven);
}

count = 0;
for (vector<double>::iterator iter = myList.begin(); iter != myList.end(); iter++){
    count += *iter;
}

cout << count;

bool removeLastValue(const Node* node, int val){
    Node* before;
    Node* toBeRemoved = nullptr;
    Node* curr = node;
    while (curr->next){
        if (curr->next->data == val) {
            before = curr;
            toBeRemoved = curr->next;
        }
        curr = curr->next;
    }
    if (toBeRemoved) {
        before->next = toBeRemoved->next;
        return true;
    }
    return false;
}

class Company{
public:
    Company(){}

    void hire(Performer& other){
        if (other.isHired()){
            performers.push_back(&other);
        }
        other.gotHired();
    }

    void showtime() const {
        for (const Performer* perf : performers){
            perf->perform();
        }
    }

private:
    vector<Performer*> performers;
};

class Performer{
public:
    Performer(const string& name) : name(name), hired(false) {}

    bool isHired() const {return hired;}

    void gotHired() {hired = true;}

    virtual void perform() const = 0;

    const string& getName() const {return name;}

private:
    const string name;
    bool hired;
};

class Actor : public Performer {
public:
    Actor(const string& name, const string& script)
    : Performer(name), script(script) {}
    
    void perform() const {
        cout << "I am " << getName() << ". " << script << endl;
    }

private:
    const string script;
};

class Mime : public Performer{
public:
    Mime(const string& name) : Performer(name) {}

    void perform() const {
        cout << "(Silence)" << endl;
    }
};


class Iterator {
public:
    Iterator(Node* where) : where(where) {}

    int& operator*() const {
        return where->val;
    }

    Iterator operator++() {
        where = where->next;
        return *this;
    }

    bool operator!=(const Iterator& other) const {
        return where != other.where;
    }

private:
    Node* where;
};
