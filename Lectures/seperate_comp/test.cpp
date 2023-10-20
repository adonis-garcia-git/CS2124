#include "Princess.h"
#include "FrogPrince.h"

#include <iostream>
#include <string>

using namespace std;
using namespace Fantasy;

int main() {
    Princess snowy("Snow White");
    FrogPrince froggy("Froggy");
    snowy.marries(froggy);
}

// begin() and end() are overloaded with different versions of const
// operator[] is overloaded with different versions of const

//not providing a necessary function results in linking error
