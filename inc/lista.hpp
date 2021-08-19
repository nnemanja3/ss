#pragma once
#include <iostream>


using namespace std;

class Lista {

private:
    struct Elem {
        string s; Elem *sled;
        Elem(string e) :s(e), sled(nullptr) {}
    };
    Elem *prvi = nullptr, *posl = nullptr;
    int size = 0;

public:

    Lista() = default;

    void dodaj(string s) {
        
        posl=(prvi?posl->sled:prvi) = new Elem(s);
        size++;
    }

    string dohvati(int index) {
        Elem* tek = prvi;
        for(int i=0; i<index; i++){
            tek = tek->sled;
        }
        return tek->s;

    }

    int velicina() {
        return size;
    }
    
    ~Lista() { 
        
        while(prvi) {
                Elem *pom = prvi;
                prvi = prvi->sled;
                delete pom;
        }

        posl = nullptr;
    }


};