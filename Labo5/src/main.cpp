#include <iostream>
#include "getallen.h"

int main(int argc, char* argv[]) {
    int number_of_digits = 4;
    if(argc==2) {
        number_of_digits = atoi(argv[1]);
        cout << "Trying to find number with length of " << number_of_digits << endl;
    }
    Getal g(number_of_digits);
    GetallenFlex getallenSolver(g);
    getallenSolver.geefOplossing();
    return 0;
}