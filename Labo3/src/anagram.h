//
// Created by Jelle De Bock on 15/03/17.
//
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#ifndef LABO3_ANAGRAM_H
#define LABO3_ANAGRAM_H

class Anagram{
public:
    Anagram(string woord);
    void sorteerWoord();
    string geefWoord();

    string woord;
};

Anagram::Anagram(string woord) {
    this->woord=woord;
    sorteerWoord();
}

string Anagram::geefWoord() {
    return woord;
}

void Anagram::sorteerWoord() {
    for(int i=0; i<woord.size(); i++){
        char kleinste=woord[i];
        int kleinste_index=i;
        for(int j=i+1; j<woord.size(); j++){
            if(woord[j]<kleinste){
                kleinste=woord[j];
                kleinste_index=j;
            }
        }
        //zet op zijn plek
        woord[kleinste_index]=woord[i];
        woord[i]=kleinste;
    }
}

#endif //LABO3_ANAGRAM_H
