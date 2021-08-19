#pragma once
#include <iostream>
#include "simbol.hpp"


using namespace std;

class TabelaSimbola {

private:
    struct Elem {
        Simbol *s; Elem *sled;
        Elem(Simbol *e) :s(e), sled(nullptr) {}
    };
    Elem *prvi = nullptr, *posl = nullptr;
    int size;

public:

    TabelaSimbola() {
        size = 0;

        Simbol *s = new Simbol("UND", "");
        s->postaviRedniBr(0);
        this->dodaj(s);
        // s = this->dohvati(0);
        

        s = new Simbol("ABS", "");
        s->postaviSekciju(1);
        this->dodaj(s);

        

    }

    void dodaj(Simbol *s) {
        if(s ==nullptr) return;
        
        Simbol *simbol = s;
        if(simbol->dohvatiOznakuSekcije()) {
            Elem *tek = prvi;
            Elem *pom = nullptr;
            int i = 0;

            if(prvi) {
                // cout << "prvi" << endl;

                while(tek != nullptr && tek->s->dohvatiOznakuSekcije()){
                    // cout << "while" << endl;
                    pom = tek;
                    tek = tek->sled;
                    i++;
                }
                simbol->postaviRedniBr(i);
                // cout<<"STIGAO" <<endl;
                if(pom == nullptr) {
                    prvi = new Elem(simbol);
                    prvi->sled = tek;
                }else {
                    // cout <<"ima pom" << endl;
                    pom->sled = new Elem(simbol);
                    pom->sled->sled = tek;
                    if(tek == nullptr) {
                        posl = pom->sled;
                    }
                }

                while(tek != nullptr) {
                    //kada ubacimo sekciju azuriramo ostale redne brojeve
                    tek->s->postaviRedniBr(tek->s->dohvatiRedniBr() + 1);

                    tek = tek->sled;
                }

            }else {
                // cout<< "Nema prvi "<< endl;
                simbol->postaviRedniBr(size);
                posl= prvi = new Elem(simbol);
            }

            



        }else {
            // cout << "nije bilo sekcija pre"<<endl;
            simbol->postaviRedniBr(size);
            posl=(prvi?posl->sled:prvi) = new Elem(simbol);
        }
        size++;
        
        
    }

    //dohvata i ostale simbole
    Simbol* dohvatiSekciju(string imeSekcije){
        Elem *tek = prvi;
        while (tek != nullptr && tek->s->dohvatiNaziv() != imeSekcije ) {
            // cout <<"while sekcije" <<endl;
            tek = tek->sled;
        }
        // cout<<"dohvatiSekciju"<<endl;
        if(tek == nullptr) return nullptr;
        return tek->s;
    }

    Simbol* dohvati(int index) {
        Elem* tek = prvi;
        
        for(int i=0; i<index; i++){
            tek = tek->sled;
        }
        return tek->s;
        
        

    }

    int velicina() {
        return size;
    }

    bool postojiSimbol(string naziv) {
        Elem *tek = prvi;
        while (tek != nullptr) {
            // cout <<"while sekcije" <<endl;
            if(tek->s->dohvatiNaziv() == naziv){
                return true;
            }
            tek = tek->sled;
        }
        // cout<<"dohvatiSekciju"<<endl;
        return false;

    }
    
    ~TabelaSimbola() { 
        
        while(prvi) {
                Elem *pom = prvi;
                prvi = prvi->sled;
                delete pom;
        }
        posl = nullptr;
    }


};