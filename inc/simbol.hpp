#pragma once
#include <iostream>


using namespace std;

class Simbol {

private:
    int redniBr;
    string naziv;
    int sekcija;
    int ofset;
    char lokal;
    char ext;

    bool oznakaSekcije;
    int size;
    string pravaPristupa;

public: 

    Simbol(string n, int s, int o) {
        this->naziv = n;
        this->sekcija = s;
        this->ofset = o;
        this->lokal = 'l';

        this->oznakaSekcije = false;

        this->ext = 'n';
    }

    Simbol(string n, string pp) {
        this->naziv = n;
        this->sekcija = 0;
        this->ofset = 0;
        this->lokal = 'l';
        
        this->ext = 'n';
        
        this->oznakaSekcije = true;
        this->size = 0;
        this->pravaPristupa = pp;

    }

    int dohvatiRedniBr() {
        return redniBr;
    }

    void postaviRedniBr(int r) {
        this->redniBr = r;
    }

    string dohvatiNaziv() {
        return naziv;
    }

    void postaviNaziv(string r) {
        this->naziv = r;
    }

    int dohvatiSekciju() {
        return sekcija;
    }

    void postaviSekciju(int r) {
        this->sekcija = r;
    }

    int dohvatiOfset() {
        return ofset;
    }

    void postaviOfset(int r) {
        this->ofset = r;
    }

    char dohvatiLokal() {
        return lokal;
    }

    void postaviLokal(char r) {
        this->lokal = r;
    }



    bool dohvatiOznakuSekcije() {
        return oznakaSekcije;
    }

    void postaviOznakuSekcije(bool r) {
        this->oznakaSekcije = r;
    }

    int dohvatiVelicinuSekcije() {
        return size;
    }

    void postaviVelicinuSekcije(int r) {
        this->size = r;
    }

    string dohvatiPravaPristupa() {
        return pravaPristupa;
    }

    void postaviPravaPristupa(string r) {
        this->pravaPristupa = r;
    }

    char dohvatiExtern(){
        return ext;
    }

    void postaviExtern(char chr) {
        this->ext = chr;
    }



};
