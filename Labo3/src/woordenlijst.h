//
// Created by Jelle De Bock on 15/03/17.
//

#ifndef LABO3_WOORDENLIJST_H
#define LABO3_WOORDENLIJST_H

#include <iostream>
#include <vector>
#include <fstream>
#include "anagram.h"
using namespace std;

class Woordenlijst{
public:
    Woordenlijst(string bestandsnaam);
    void overloop_anagrammen();
    std::vector<std::pair<string,string>> zoekGrootste();
    std::vector<std::pair<string, string>> zoekLangste();
private:
    std::vector<std::pair<string, string>> anagrammen;

    int zoekWoord(string gesorteerd_woord);
};

std::vector<std::pair<string,string>> Woordenlijst::zoekGrootste(){
    int maxgrootte = 0;
    int beginmaxgroep = 0;
    int begingroep = 0;

    while(begingroep<anagrammen.size()-1){
        int hulp;
        string fp = anagrammen[begingroep].first;
        hulp=begingroep;
        while(hulp<anagrammen.size()-1 && anagrammen[hulp].first==fp){
            hulp++;
        }
        int grootte;
        grootte=hulp-begingroep;
        if(grootte>maxgrootte){
            maxgrootte = grootte;
            beginmaxgroep = begingroep;
        }
        begingroep = hulp;
    }

    vector<pair<string,string>> maximaal(anagrammen.begin()+beginmaxgroep,anagrammen.begin()+beginmaxgroep+maxgrootte);

    return maximaal;

};


void Woordenlijst::overloop_anagrammen() {
    for(auto anagram : anagrammen){
        cout<<anagram.first<<"\t";
        cout<<anagram.second<<" ";
        cout<<endl;
    }
}

Woordenlijst::Woordenlijst(string bestandsnaam) {
    ifstream input(bestandsnaam);

    if(input.good()){
        while(!input.eof()){
            string woord;
            input>>woord;

            Anagram anagram(woord);
            string gesorteerd = anagram.geefWoord();
            std::pair<string, string> p;
            p.first=gesorteerd;
            p.second=woord;
            anagrammen.push_back(p);
        }
        sort(anagrammen.begin(),anagrammen.end());
    }
}

int Woordenlijst::zoekWoord(string gesorteerd_woord) {
    int i=0;
    while(i<anagrammen.size()&&anagrammen[i].first<gesorteerd_woord){
        i++;
    }
    if(i!=anagrammen.size() && anagrammen[i].first==gesorteerd_woord){
        return i;
    }
    return -1;
}

std::vector<std::pair<string, string>> Woordenlijst::zoekLangste() {
        int maxlengtefppaar = 0;
        int beginmaxpaar = 0;
        int beginpaar = 0;

        while (beginpaar < anagrammen.size() - 1) {
            int hulp;
            string fp = anagrammen[beginpaar].first;
            hulp = beginpaar;
            while (hulp < anagrammen.size() - 1 && anagrammen[hulp].first == fp) {
                hulp++;
            }
            int grootte;
            grootte = hulp - beginpaar;

            if (grootte >= 2) {
                int lengtefppaar = fp.length();
                if (lengtefppaar >= maxlengtefppaar) {
                    maxlengtefppaar = lengtefppaar;
                    beginmaxpaar = beginpaar;
                }
            }
            beginpaar = hulp;
        }

        vector<pair<string, string>> maximaal(anagrammen.begin() + beginmaxpaar, anagrammen.begin() + beginmaxpaar + 1);

        return maximaal;
}

#endif //LABO3_WOORDENLIJST_H
