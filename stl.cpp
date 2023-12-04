#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

char* myFind(char* start, char* stop, char target) {
    char* curr = start;
    while (curr != stop) {
        if (*curr == target) return curr;
        curr++;
    }
    return stop;
}

list<char>::iterator myFind(list<char>::iterator start, list<char>::iterator stop, char target) {
    list<char>::iterator curr = start;
    while (curr != stop) {
        if (*curr == target) return curr;
        curr++;
    }
    return stop;
}

template <typename Iter, typename Target>
Iter myFind(Iter start, Iter stop, Target target) {
    Iter curr = start;
    while (curr != stop) {
        if (*curr == target) return curr;
        curr++;
    }
    return stop;
}

template <typename Iter, typename Predicate>
Iter myFind_if(Iter start, Iter stop, Predicate pred) {
    Iter curr = start;
    while (curr != stop) {
        if (pred(*curr)) return curr;
        curr++;
    }
    return stop;
}

bool isEven (int val) {
    return val % 2 == 0;
}

// Functor
struct IsEvenFunct {
    // function call operator
    bool operator() (int val) const {
        return val % 2 == 0;
    }
};

struct IsMultiple {
    IsMultiple(int divisor) : divisor(divisor) {}

    // function call operator
    bool operator() (int val) const {
        return val % divisor == 0;
    }

    int divisor;
};

template<typename T>
void print (T val) {
    cout << val << endl;
}

int main() {

    char array[] = "Bjarne Stroustrup";
    int len = 17;
    //sort(array, array+len);  // half open range

    vector<char> vc (array, array+len);
    sort(vc.begin(), vc.end());

    list<char> lc (vc.begin(), vc.end());

    list<char>::iterator where = find(lc.begin(), lc.end(), 't'); 

    // not being passed a list, just a place to start and end
    // will return whatever type passed in as the second argument if not found
    where = find(lc.begin(), lc.end(), 'Q');
    if (where == lc.end()) {
        cout << "Failed to find 'Q'\n";
    }

    vector<char>::iterator where2 = find(vc.begin()+2, vc.end()-3, 't'); // showcases function templating 

    list<int> li {1,5,3,7,6,8,10,17};

    list<int>::iterator where3 = find_if(li.begin(), li.end(), isEven);

    // lambda function
    where3 = find_if(li.begin(), li.end(), [] (int val) {return val % 2 == 0;});

    bool isItEven = [] (int val) {return val % 2 == 0;};
    isItEven = [] (int val) -> bool {return val % 2 == 0;};
    [] {cout << "hello world\n";} ();

    IsEvenFunct ief;
    where3 = find_if(li.begin(), li.end(), ief);
    where3 = find_if(li.begin(), li.end(), IsEvenFunct()); // default constructor call for temporary use
    where3 = find_if(li.begin(), li.end(), IsMultiple(17));
};
