#include <gtest/gtest.h>
#include "../src/sortvector.h"
#include "../src/sorteermethode.h"

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