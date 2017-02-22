#include <iostream>
#include "sortvector.h"

using namespace std;

int main()
{
    Sortvector<int> range(10);
    cout<<range;
    range.draai_om();
    cout<<range;
    range.shuffle();
    cout<<range;
    range.vul_omgekeerd();
    cout<<range;
    range.vul_random();
    cout<<range;
    range.vul_random_zonder_dubbels();
    cout<<range;
    return 0;
}
