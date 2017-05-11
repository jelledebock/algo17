#include "backtrackflex.h"
#include <vector>
#include <iostream>

using namespace std;

#ifndef LABO5_NEWGETALLEN_H
#define LABO5_NEWGETALLEN_H

class Getal{
        public:
        Getal(){};
        Getal(int n){
            getal.resize(0);
            for(int i = 0 ; i < n ; i++){
                getal.push_back(0);
            }
        };

        ~Getal(){
            pos=0;
        };
        Getal(const Getal &other){
            getal.resize(0);
            for(int i = 0 ; i < other.lengte() ; i++){
                getal.push_back(other.getNumber(i));
            }
            pos = other.getPos();
        };

        Getal& operator=(const Getal& other){
            getal.resize(0);
            for(int i = 0 ; i < other.lengte() ; i++){
                getal.push_back(other.getNumber(i));
            }
            pos = other.getPos();

            return *this;
        }

        Getal& operator=(const Getal&& other){
            getal.resize(other.lengte());
            for(int i = 0 ; i < other.lengte() ; i++){
                getal.push_back(other.getNumber(i));
            }
            pos = other.getPos();

            return *this;
        }

        void setNumber(int pos, int num){
            getal[pos]=num;
        };

        int getNumber(int pos) const{
            return getal[pos];
        };

        vector<int> getGetal() const{
            return getal;
        };

        void addDigit(int num){
            if(pos<getal.size()){
                getal[pos]=num;
                pos+=1;
            }
            else{
                throw "Out of Getal bound";
            }
        };

        int lengte() const{
            return getal.size();
        };

        bool controleer() const{
            //Controleer de vier criteria
            //Criterium 1
            int j=getal.size()-1;
            int sum_of_4_digits = 0;
            while(j>0 && j!=getal.size()-5){
                sum_of_4_digits+=getal[j];
                j--;
            }
            if(sum_of_4_digits>=13)
                return false;
            //Criterium 2
            vector<bool> aanwezig(10,false);
            j=getal.size()-1;
            while(j>0 && j!=getal.size()-4){
                if(aanwezig[getal[j]])
                    return false;
                j--;
            }
            //Criterium 3
            if(getal.size()>=6) {
                if (getal[getal.size() - 1] == getal[getal.size() - 7])
                    return false;
            }
            return true;
        };

        int sumOfDigits() const{
            //Criterium 4
            int sum_of_digits = 0;
            for(int i=0; i<getal.size(); i++){
                sum_of_digits+=getal[i];
            }
            return sum_of_digits;
        };

        int getPos() const{ return pos; };
    friend ostream& operator<<(ostream &os, const Getal& getal);
private:
        vector<int> getal;
        int pos=0;
};

ostream& operator<<(ostream &os, const Getal& getal){
    for(int i=getal.lengte()-1 ; i>=0; i--){
        os<<getal.getNumber(i);
    }
    os<<"(POS = "<<getal.getPos()<<")";
    return os;
}

class GetallenFlex : public Backtrackflex<Getal>{
    public:
        GetallenFlex(Getal&);
        void geefOplossing();
    protected:
        bool controle();
        void verwerk();
        vector<Getal> geefVerdere();
    private:
        int n;
        int maxsum=0;
        bool controleer_criteria();
        Getal beste_oplossing;
};

GetallenFlex::GetallenFlex(Getal& gt){
    //cout<<"START MET "<<gt<<endl;
    n=gt.lengte();
    Backtrackflex::voegToeAanDeeloplossing(gt);
}

void GetallenFlex::geefOplossing() {
    losOp(true);
    cout<<"Beste oplossing: ";
    cout<<beste_oplossing;
    cout<<endl;
}

vector<Getal> GetallenFlex::geefVerdere() {
    const Getal * laatste = deeloplossing.back();
    vector<Getal> mogelijkheden;

    //cout<<"LAATSTE GETAL "<<*laatste<<endl;
    //Get last number
    if(laatste->getPos()<n){
        for(int i=0;i<9;i++){
            Getal mogelijkheid=*laatste;
            mogelijkheid.addDigit(i);
            //cout<<"\tTOEVOEGEN: ";
            //cout<<mogelijkheid;
            //cout<<endl;
            mogelijkheden.push_back(mogelijkheid);
        }
    }

    return std::move(mogelijkheden);
}

void GetallenFlex::verwerk() {
    beste_oplossing = *deeloplossing.back();
}

bool GetallenFlex::controle() {
    return controleer_criteria();
}

bool GetallenFlex::controleer_criteria() {
    if(deeloplossing.size()>0) {
        const Getal mogelijkheid = *deeloplossing.back();
        bool eerste_drie_oke = mogelijkheid.controleer();
        int sum_of_digits = mogelijkheid.sumOfDigits();

        if(eerste_drie_oke && sum_of_digits>beste_oplossing.sumOfDigits()){
            return true;
        }
    }
    return false;

}

#endif //LABO5_NEWGETALLEN_H
