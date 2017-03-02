//
// Created by jelle on 02.03.17.
//
#include "sorteermethode.h"

#ifndef LABO2_MERGESORT_BU_H
#define LABO2_MERGESORT_BU_H

template <typename T>
class Mergesort_bu : public Sorteermethode<T>{
public:
    void operator()(vector<T> & v) const;
private:
    void mergesort_bu(vector<T> &, vector<T> &v, int, int) const;
};

template <typename T>
void merge_bu(vector<T> &, vector<T> &, int, int);

template <typename T>
void Mergesort_bu<T>::operator()(vector <T> &v) const {
    vector<T> temp(v.size());
    int breedte=1;
    while(breedte<v.size()){
        int l=0;
        while(l+breedte<v.size()){
            merge_bu(v, temp, l, breedte);
            l=l+breedte*2;
        }
        breedte*=2;
    }
}

template <typename T>
void merge_bu(vector<T> &vec, vector<T> &temp, int l, int width){
    int i=l;
    int j=l+width;

    int m = l+width;
    int r = l+2*width>vec.size()?vec.size():l+2*width;
    int k=l;

    for(int s=l; s<r; s++){
        if(i<m && (j>=r || vec[i] <= vec[j])){
            temp[s]=vec[i++];
        }else{
            temp[s]=vec[j++];
        }
    }

    for(int s=l; s<r; s++){
        vec[s]=temp[s];
    }
}
#endif //LABO2_MERGESORT_BU_H
