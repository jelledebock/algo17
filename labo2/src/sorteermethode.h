#ifndef __SORTEERMETHODE
#define __SORTEERMETHODE
#include "sortvector.h"
#include <iostream>
#include "chrono.h"
#include "csv.h"
    using std::move;
    using std::swap;
    using std::endl;
    using std::cout;
    using std::string;
#include <algorithm>   // voor sort()-methode uit STL
#include <sstream>

/** class Sorteermethode
    \brief abstracte klasse van methodes die een vector sorteren
*/
template <typename T>
class Sorteermethode{
    public:
/// \fn operator() sorteert de vector gegeven door het argument
        virtual void operator()(vector<T> & v) const = 0;

/// \fn meet(int kortste, int langste, ostream& os) schrijft naar os een overzicht (met de nodige ornamenten)
/// met de snelheid van de opgegeven sorteermethode *this. Er wordt 1 lijn uitgedrukt voor elke mogelijke
/// grootte. Deze groottes zijn kleinste, 10*kleinste, 100*kleinste,
/// enzovoorts, tot aan grootste.
/// Op een lijn staat de snelheid van de methode toegepast op
/// (1) een random tabel
/// (2) een al gesorteerde tabel.
/// (3) een omgekeerd gesorteerde tabel.

/// Deze functie werkt alleen als T een toekenning van een int toelaat,
/// zodat bv.
///    T a=5;
/// geldig is.
    void meet(int kortste, int langste, ostream& os);
    void meetCSV(int kortste, int langste, ostream& os, string bestandsnaam);



};
template <class T>
void Sorteermethode<T>::meetCSV(int kortste, int langste, ostream& os, const string bestandsnaam){
    Chrono chrono;
    CsvData csv(bestandsnaam);
    std::vector<std::vector<float>> data;

    for(int i=kortste; i<langste; i=i*10){
        Sortvector<T> random(i);
        Sortvector<T> gesorteerd(i);
        Sortvector<T> omgekeerd(i);

        std::vector<float> meetresultaat;
        meetresultaat.push_back((float)i);

        random.vul_random_zonder_dubbels();
        omgekeerd.vul_omgekeerd();

        //random gesorteerd testen
        chrono.start();
        operator()(random);
        chrono.stop();
        meetresultaat.push_back(chrono.tijd());

        //gesorteerd testen
        chrono.start();
        operator()(gesorteerd);
        chrono.stop();
        meetresultaat.push_back(chrono.tijd());

        //omgekeerd gesorteerd testen
        chrono.start();
        operator()(omgekeerd);
        chrono.stop();
        meetresultaat.push_back(chrono.tijd());

        csv.voegDataToe(meetresultaat);
    }
};

template <class T>
void Sorteermethode<T>::meet(int kortste, int langste, ostream& os){
    Chrono chrono;
    os<<std::setw(10)<<std::right<<"lengte"<<"\t"<<std::setw(10)<<"random"<<"\t"<<std::setw(10)<<"gesorteerd"<<"\t"<<std::setw(10)<<"omgekeerd"<<endl;
    for(int i=kortste; i<langste; i=i*10){
        os<<std::right<<std::setw(10)<<i<<"\t";
        Sortvector<T> random(i);
        Sortvector<T> gesorteerd(i);
        Sortvector<T> omgekeerd(i);

        random.vul_random_zonder_dubbels();
        omgekeerd.vul_omgekeerd();

        os<<std::fixed;
        os<<std::setw(10);

        //random gesorteerd testen
        chrono.start();
        operator()(random);
        chrono.stop();
        os<<std::right<<chrono.tijd()<<"\t";

        //gesorteerd testen
        chrono.start();
        operator()(gesorteerd);
        chrono.stop();
        os<<std::setw(10)<<std::right<<chrono.tijd()<<"\t";

        //omgekeerd gesorteerd testen
        chrono.start();
        operator()(omgekeerd);
        chrono.stop();
        os<<std::setw(10)<<std::right<<chrono.tijd();

        os<<endl;
    }
};

/** \class STLSort
   \brief STANDARD TEMPLATE LIBRARY SORT
*/
template <typename T>
class STLSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;
};

template <typename T>
void STLSort<T>::operator()(vector<T> & v) const{
    sort(v.begin(),v.end());
}

/** \class InsertionSort
*/
template <typename T>
class InsertionSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;   
};

template <typename T>
void InsertionSort<T>::operator()(vector<T> & v) const{
    for(int i=1; i<v.size(); i++){
        T h;
        h=move(v[i]);
        int j=i-1;
        while(j>=0 && h<v[j]){
            v[j+1] = move(v[j]);
            j--;
        }
        v[j+1] = move(h);
    }
}

/** \class Shellsort
*/
 
template <typename T>
class ShellSort : public Sorteermethode<T>{
    public:
        void operator()(vector<T> & v) const;
};
#endif 
