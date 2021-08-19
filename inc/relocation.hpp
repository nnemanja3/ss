#pragma once
#include <iostream>


using namespace std;


class Relocation {
private:
    int simbol;
    int sekcija;
    string tipRelokacije;
    int offset;

public:

    Relocation (int s, int se, string tip, int o){
        this->simbol = s;
        this->sekcija = se;

        this->tipRelokacije = tip;
        this->offset = o; 
    }

    void postaviSimbol(int s) {
        this->simbol = s;
    }

    int dohvatiSimbol() {
        return this->simbol;
    }

    void postaviSekcija(int s) {
        this->sekcija = s;
    }

    int dohvatiSekcija() {
        return this->sekcija;
    }

    void postaviTipRelokacije(string s) {
        this->tipRelokacije = s;
    }

    string dohvatiTipRelokacije() {
        return this->tipRelokacije;
    }

    void postaviOffset(int s) {
        this->offset = s;
    }

    int dohvatiOffset() {
        return this->offset;
    }

    

};