#ifndef LABO2_NSTRING_H
#define LABO2_NSTRING_H

#include <iostream>
#include <string>

class Nstring : public std::string{
public:
    Nstring(int waarde):string(std::to_string(waarde)){};
    Nstring():string(){};

    void operator=(const int &num){
        (*this).insert(0,std::to_string(num));
    };

    friend ostream& operator<<(ostream& os, const Nstring s){
        os<<s;
        return os;
    };
};
#endif //LABO2_NSTRING_H
