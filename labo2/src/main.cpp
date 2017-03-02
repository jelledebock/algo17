#include <iostream>
#include "sortvector.h"
#include "sorteermethode.h"
#include "Nstring.h"
#include "Mergesort.h"
#include "Mergesort_bu.h"

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

    STLSort<int> insertionSort;
    insertionSort.meet(10, 1000000, cout);

    STLSort<Nstring> stlSortString;
    stlSortString.meet(10,1000000, cout);

    Sortvector<int> random(10);
    random.vul_random_zonder_dubbels();
    cout<<"Voor: "<<random<<endl;
    Mergesort<int> mergesort;
    mergesort(random);
    cout<<"Na: "<<random<<endl;

    random.vul_random_zonder_dubbels();
    cout<<"Voor: "<<random<<endl;
    Mergesort_bu<int> mergesort_bu;
    mergesort_bu(random);
    cout<<"Na: "<<random<<endl;

    return 0;
}
