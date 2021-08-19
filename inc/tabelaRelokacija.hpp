#pragma once
#include <iostream>
#include "relocation.hpp"


using namespace std;

class TabelaRelokacija {

private:
    struct Elem {
        Relocation *s; Elem *sled;
        Elem(Relocation *e) :s(e), sled(nullptr) {}
    };
    Elem *prvi = nullptr, *posl = nullptr;
    int size = 0;

public:

    TabelaRelokacija() = default;

    void dodaj(Relocation *s) {
        
        posl=(prvi?posl->sled:prvi) = new Elem(s);
        size++;
    }

    Relocation* dohvati(int index) {
        Elem* tek = prvi;
        for(int i=0; i<index; i++){
            tek = tek->sled;
        }
        return tek->s;

    }

    int velicina() {
        return size;
    }
    
    ~TabelaRelokacija() { 
        
        while(prvi) {
                Elem *pom = prvi;
                prvi = prvi->sled;
                delete pom;
        }

        posl = nullptr;
    }


};