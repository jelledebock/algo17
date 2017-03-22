#include <iostream>
#include <vector>

#include "src/woordenlijst.h"
int main() {
    Woordenlijst woordenlijst("woordenlijst.txt");
    std::vector<std::pair<string,string>> grootste = woordenlijst.zoekGrootste();
    std::vector<std::pair<string,string>> langste = woordenlijst.zoekLangste();

    cout<<"Grootste groep anagrammen"<<endl;
    for(auto anagram : grootste){
        cout<<anagram.second<<" ";
    }
    cout<<endl;

    cout<<"Langste paar anagrammen"<<endl;
    for(auto anagram : langste){
        cout<<anagram.second<<" ";
    }
    cout<<endl;
    return 0;
}