#include <iostream>
#include <vector>
using namespace std;

struct Complex {
    int real;
    int imag;
    Complex(int real, int imag) : real(real), imag(imag) {}
};

ostream& operator<<(ostream& os, const Complex& rhs){
    os << rhs.real << ", " << rhs.imag << endl;
    return os;
}

int main(){
    int* p = new int[10];
    for (size_t i = 0; i < 10; i++){
        p[i] = i * i;
    }
    
    int* q = &p[5];
    cout << &p[5] << endl;
    cout << *(p+5) << endl;
    cout << q[-2] << endl;

    Complex eight{6, 0};
    // Complex eight;
    // eight.real = 6;
    // eight.imag = 0;
    cout << eight.real << ", " << eight.imag << endl;

    vector<Complex> vec;
    vec.emplace_back(7,0); // this doesn't work unless constructor is defined
    cout << vec[0] << endl;
}
