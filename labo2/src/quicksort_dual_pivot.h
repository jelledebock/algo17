//
// Created by jelle on 07.03.17.
//

#ifndef LABO2_QUICKSORT_DUAL_PIVOT_H
#define LABO2_QUICKSORT_DUAL_PIVOT_H

template <typename T>
class Quicksort_Dual_Pivot : public Sorteermethode<T>{
public:
    void operator()(vector<T> & v) const;
private:
    void quicksort_Dual_Pivot(vector<T> &, int, int) const;
};

template <typename T>
void Quicksort_Dual_Pivot<T>::operator()(vector <T> &v) const {
    quicksort_Dual_Pivot(v,0, v.size()-1);
}

template <typename T>
void Quicksort_Dual_Pivot<T>::quicksort_Dual_Pivot(vector <T> &v, int l, int r) const {
    if (l < r) {
        //Pivots
        T p1 = v[l];
        T p2 = v[r];

        //Swap the 2 pivots if p1>p2
        if (p1 > p2) {
            v[l] = std::move(p2);
            v[r] = std::move(p1);
            p1 = v[l];
            p2 = v[r];
        }

        int k = l + 1;
        int g = r - 1;
        int m = k;

        while (m <= g) {
            if (v[m] < p1) {
                T temp = std::move(v[k]);
                v[k] = std::move(v[m]);
                v[m] = std::move(temp);
                k++;
            } else if (v[m] >= p2) {
                while (v[g] > p2 && m < g) {
                    g--;
                }
                T temp = std::move(v[g]);
                v[g] = std::move(v[m]);
                v[m] = std::move(temp);

                g--;

                if (v[m] < p1) {
                    T temp = std::move(v[m]);
                    v[m] = std::move(v[k]);
                    v[k] = temp;
                    k++;
                }
            }
            m++;
        }
        //Zet pivots op hun plek
        k = k - 1;
        g = g + 1;
        T temp = std::move(v[k]);
        v[k] = std::move(v[l]);
        v[l] = std::move(temp);

        temp = std::move(v[g]);
        v[g] = std::move(v[r]);
        v[r] = std::move(temp);

        quicksort_Dual_Pivot(v, l, k - 1);
        quicksort_Dual_Pivot(v, k + 1, g - 1);
        quicksort_Dual_Pivot(v, g + 1, r);
    }
}

#endif //LABO2_QUICKSORT_DUAL_PIVOT_H
