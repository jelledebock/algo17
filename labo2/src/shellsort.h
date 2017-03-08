//
// Created by jelle on 08.03.17.
//

#ifndef LABO2_SHELLSORT_H
#define LABO2_SHELLSORT_H

#include <vector>

//Sedgewick's increments, used in the shellsort algorithm
vector<int> INCREMENTS = {  1391376, 463792, 198768, 86961, 33936,
                            13776, 4592, 1968, 861, 336,
                            112, 48, 21, 7, 3, 1
};

template <typename T>
class Shellsort : public Sorteermethode<T>{
public:
    void operator()(vector<T> & v) const;
};

template <typename T>
void Shellsort<T>::operator()(vector <T> &v) const {
    //Ga over alle increments
    for(int i = 0 ; i < INCREMENTS.size() ; i++){
        int increment = INCREMENTS[i];
        //Controleer of increment niet te groot is voor onze array
        if(increment < v.size()){
            //Ga k-sorteren voor alle elementen startende van het increment
            for(int j = increment ; j < v.size() ; j++){
                T temp = v[j];
                int k = j;
                //Insertion sort stap, plaats j-de element op zijn juiste plek, telkens increment-stapjes verder springend
                while(k-increment>=0 && v[k-increment]>temp){
                    v[k]=std::move(v[k-increment]);
                    k-=increment;
                }
                v[k]=std::move(temp);
            }
        }
    }
}

#endif //LABO2_SHELLSORT_H
