#include <gtest/gtest.h>
#include "../src/sortvector.h"
#include "../src/sorteermethode.h"
#include "../src/Mergesort.h"
#include "../src/Mergesort_bu.h"


TEST(Sortvector, vul_range_test)
{
    Sortvector<int> sv(6);
    sv.vul_range();
    for(int i=0;i<6;i++)
        EXPECT_EQ(sv[i], i);
}

TEST(Sortvector, vul_range_test_doubles)
{
    Sortvector<double> sv(6);
    sv.vul_range();
    for(int i=0;i<6;i++)
        EXPECT_EQ(sv[i], i);
}

TEST(Sortvector, draai_om_test)
{
    Sortvector<int> sv(6);
    sv.vul_range();
    sv.draai_om();
    for(int i=5;i>=0;i--)
    EXPECT_EQ(sv[5-i], i);
}

TEST(Sortvector, vul_omgekeerd_test)
{
    Sortvector<int> sv(6);
    sv.vul_omgekeerd();
    for(int i=0;i<6;i++)
    EXPECT_EQ(sv[i], 5-i);
}

TEST(Sortvector, test_is_gesorteerd_functie)
{
    Sortvector<int> sv(6);
    EXPECT_EQ(sv.is_gesorteerd(), true);
}

TEST(Sortvector, test_is_niet_gesorteerd_functie)
{
    Sortvector<int> sv(6);
    sv.vul_omgekeerd();
    EXPECT_EQ(sv.is_gesorteerd(), false);
}

TEST(Sorteermethode, test_insertion_sort)
{
    Sortvector<int> sv(6);
    sv.vul_random_zonder_dubbels();
    EXPECT_EQ(sv.is_gesorteerd(), false);
    InsertionSort<int> insertionSort;
    insertionSort(sv);
    EXPECT_EQ(sv.is_gesorteerd(), true);
}

TEST(Mergesort, test_mergesort_random){
    vector<int> vec {2,0,2,4,7,6,3,1,10,11};
    vector<int> sorted {0,1,2,2,3,4,6,7,10,11};

    Mergesort<int> mergesort;
    mergesort(vec);
    EXPECT_EQ(vec, sorted);
}


TEST(Mergesort, test_mergesort_omgekeerd){
    Sortvector<int> vec(20);
    vec.vul_omgekeerd();

    Mergesort<int> mergesort;
    mergesort(vec);

    EXPECT_EQ(vec.is_gesorteerd(), true);
}

TEST(Mergesort, test_mergesort_reeds_gesorteerd){
    Sortvector<int> vec(20);
    vec.vul_range();

    Mergesort<int> mergesort;
    mergesort(vec);

    EXPECT_EQ(vec.is_gesorteerd(), true);
}

TEST(Mergesort_bu, test_mergesort_bu_random){
    vector<int> vec {2,0,2,4,7,6,3,1,10,11};
    vector<int> sorted {0,1,2,2,3,4,6,7,10,11};

    Mergesort_bu<int> mergesort_bu;
    mergesort_bu(vec);
    EXPECT_EQ(vec, sorted);
}


TEST(Mergesort_bu, test_mergesort_bu_omgekeerd){
    Sortvector<int> vec(20);
    vec.vul_omgekeerd();

    Mergesort_bu<int> mergesort_bu;
    mergesort_bu(vec);

    EXPECT_EQ(vec.is_gesorteerd(), true);
}

TEST(Mergesort_bu, test_mergesort_bu_reeds_gesorteerd){
    Sortvector<int> vec(20);
    vec.vul_range();

    Mergesort_bu<int> mergesort_bu;
    mergesort_bu(vec);

    EXPECT_EQ(vec.is_gesorteerd(), true);
}