//
// Created by jelle on 22.03.17.
//

#ifndef LABO2_QUICKSORT_H
#define LABO2_QUICKSORT_H
template <typename T>
class Quicksort : public Sorteermethode<T>{
public:
    void operator()(vector<T> & v) const;
private:
    void quicksort(vector<T> &, int, int) const;
};

template <typename T>
void Quicksort<T>::operator()(vector <T> &v) const {
    quicksort(v,0, v.size()-1);
}

template <typename T>
void Quicksort<T>::quicksort(vector <T> &v, int l, int r) const {
    //Rangschik deelvector v[l]..[r]
    if(l<r) {
        T pivot = v[l];
        int i=l, j=r;
        while(v[j]>pivot){
            j--;
        }
        while(i<j){
            swap(v[i],v[j]);
            i++;
            while(v[i]<pivot)
                i++;
            j--;
            while(v[j]>pivot)
                j--;
        }
        quicksort(v, l, j);
        quicksort(v, j+1, r);
    }
}
#endif //LABO2_QUICKSORT_H
