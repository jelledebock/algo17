#ifndef __SORTVECTOR
#define __SORTVECTOR
/**
 \class sortvector
 \brief is een klasse van sorteerbare vectoren
 Bovenop de vectoreigenschappen zijn er hulpfuncties om sorteervergelijkingen
 te vergemakkelijken.
*/
#include <iostream>
   using std::istream;
   using std::ostream;
    using std::move;
    using std::swap;
#include <iomanip>   // voor setw
#include <cstdlib>   // voor rand - opletten!! 
#include <vector>
#include <cstdlib>
#include <ctime>
    using std::vector;

template<class T>
class Sortvector:public vector<T>{
  public:

    /// \fn Constructor: het argument geeft de grootte aan
    /// bij constructie zal de tabel opgevuld worden met
    /// n verschillende Ts in random volgorde
    /// (zie hulplidfuncties)
    Sortvector(int);
    
    Sortvector(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(Sortvector<T>&& v) = delete;
    Sortvector(Sortvector<T>&& v) = delete;

    /// \fn vul_range vul vector met de waarden T(0)...T(size()-1) in volgorde
    void vul_range();
    void draai_om();
    void vul_omgekeerd();
    void shuffle();
    void vul_random_zonder_dubbels();
    void vul_random(); //< nog niet implementeren
    
    bool is_gesorteerd() const;
    /// \fn is_range controleert of *this eruit ziet als het resultaat van vul_range(), d.w.z.
    /// dat, voor alle i, (*this)[i]==T(i);
    bool is_range() const;

    friend ostream& operator<<(ostream& os, const Sortvector<T>& s){
        s.schrijf(os);
        return os;
    }

  private: 
    void schrijf(ostream & os)const;
    
};

template <class T>
Sortvector<T>::Sortvector(int aantal) : vector<T>(aantal){
    srand(time(0));
    vul_range();
}

template <class T>
void Sortvector<T>::schrijf(ostream & os)const{
    for(auto&& t : *this){
        os<<t<<" ";
    }
    os<<"\n";
}

template <class T>
void Sortvector<T>::vul_range() {
    for(int i=0; i<(*this).size(); i++){
        (*this)[i]=i;
    }
}

template <class T>
void Sortvector<T>::draai_om(){
    int n = (*this).size();
    for(int i=0; i<((int)n/2);i++){
        int j = n-1-i;
        T temp = std::move((*this)[j]);
        (*this)[j]=std::move((*this)[i]);
        (*this)[i]=std::move(temp);
    }
}

template <class T>
void Sortvector<T>::vul_omgekeerd() {
    int n = (*this).size();
    for (int i = 0; i < n; i++) {
        (*this)[i]=n-1-i;
    }
}

template <class T>
void Sortvector<T>::shuffle(){
    //Fisher-Yates shuffle
    int n = (*this).size();
    for(int i=n-1; i>=1;i--){
        int j = rand()%(i+1);
        T temp = std::move((*this)[j]);
        (*this)[j]=std::move((*this)[i]);
        (*this)[i]=std::move(temp);
    }
}

template <class T>
void Sortvector<T>::vul_random_zonder_dubbels(){
    vul_range();
    shuffle();
}

template <class T>
void Sortvector<T>::vul_random(){
    int n = (*this).size();
    for(int i=0 ; i<n ; i++){
        (*this)[i]=rand()%n;
    }
}

template <class T>
bool Sortvector<T>::is_gesorteerd() const {
    int i=0;
    int n=(*this).size();
    while(i<n-1 && (*this)[i]<(*this)[i+1]){
        i++;
    }
    if(i<n-1){
        return false;
    }
    else{
        return true;
    }
}

template <class T>
bool Sortvector<T>::is_range() const {
    int i=0;
    while(i<(*this).size() && i==(*this)[i]){
        i++;
    }
    if(i>(*this).size())
        return true;
    else
        return false;
}
#endif
