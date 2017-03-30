#include <iostream>
#include <vector>
#include <fstream>
#include "binboom.h"
int main() {
    Binboom<string> boom;
    ifstream input("jacht.txt");
    boom.lees(input);
    boom.schrijf(cout);
    return 0;
}