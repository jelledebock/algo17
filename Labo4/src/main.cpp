#include <iostream>
#include <vector>
#include <fstream>
#include "binboom.h"

using namespace std;

void print_zin(string header, vector<string> zin){
    cout<<header<<":"<<endl;
    for(string woord : zin){
        cout<<woord<<" ";
    }
    cout<<endl;
}

int main() {
    Binboom<string> boom;
    ifstream input("jacht.txt");
    boom.lees(input);
    vector<string> inorder;
    vector<string> preorder;
    vector<string> postorder;

    auto inorderf = [&inorder] (string&& waarde) {inorder.push_back(waarde);};
    auto preorderf = [&preorder] (string&& waarde) {preorder.push_back(waarde);};
    auto postorderf = [&postorder] (string&& waarde) {postorder.push_back(waarde);};

    boom.DEbezoek(preorderf,inorderf,postorderf);

    print_zin("Vraag", preorder);
    print_zin("Antwoord", inorder);

    boom.schrijf(cout);
    return 0;
}