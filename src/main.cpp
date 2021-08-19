// #pragma once
//ako slucajno ispisuje duplu 1934 linija
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include <regex>

#include "../inc/lista.hpp"
#include "../inc/tabelaSimbola.hpp"
#include "../inc/simbol.hpp"

#include "../inc/relocation.hpp"
#include "../inc/tabelaRelokacija.hpp"

using namespace std;


void prikazTabeleSimbola(TabelaSimbola *tabelaSimbola){

    cout<< "Redni broj  Naziv   Sekcija  Ofset  Lokal   velicina    prava pristupa" <<endl  ;

    for(int i = 0; i<tabelaSimbola->velicina(); i++) {
        Simbol *s = tabelaSimbola->dohvati(i);
        if(s != nullptr)
        cout<< "    "<< s->dohvatiRedniBr() << "     " << s->dohvatiNaziv() << "     " <<
         s->dohvatiSekciju() << "     " << s->dohvatiOfset() << "     " << s->dohvatiLokal();
        if(s->dohvatiOznakuSekcije()) {
            cout << "    "<< s->dohvatiVelicinuSekcije() << "    "<< s->dohvatiPravaPristupa();
        }
        cout << endl;
    }

    // cout<<"velicina" << tabelaSimbola->velicina();

}

void prikazTabeleRelokacija(TabelaRelokacija *tabelaRelokacija){

    cout<< "Simbol   Sekcija  Tip Relokacije  Offset" <<endl  ;

    for(int i = 0; i<tabelaRelokacija->velicina(); i++) {
        Relocation *s = tabelaRelokacija->dohvati(i);
        if(s != nullptr)
        cout<< "    "<< s->dohvatiSimbol() << "     " << s->dohvatiSekcija() << "     " <<
         s->dohvatiTipRelokacije() << "     " << s->dohvatiOffset() << endl;
    }

    // cout<<"velicina" << tabelaSimbola->velicina();

}

bool proveraTabeleSimbolaDefinisanost(TabelaSimbola *tabelaSimbola) {

    for(int i = 0; i< tabelaSimbola->velicina(); i++){
        Simbol *s = tabelaSimbola->dohvati(i);
        if(s->dohvatiSekciju() == 0) {
            if(s->dohvatiExtern() != 'e'){
                return false;
            }
        }
    }

    return true;
    
}

//proverava i vise naredbi
bool proveraViseDirektiva(Lista *tokeniLinije){
    int brojDirektiva = 0;
    for(int i=0; i<tokeniLinije->velicina(); i++) {
        string s = tokeniLinije->dohvati(i);
        if(s[s.length()-1] == ','){
            s.erase(s.size()-1);
        }
        if(s == ".section" || s == ".extern" || s == ".global" || s == ".word" || s == ".skip" || s == ".equ" || s == ".end" 
        || s == "halt" || s == "int" || s == "iret" || s == "call" || s == "ret" || s == "jmp" 
        || s == "jeq" || s == "jne" || s == "jgt" || s == "push" || s == "pop" || s == "xchg" 
        || s == "add" || s == "sub" || s == "mull" || s == "div" || s == "cmp" || s == "not" 
        || s == "and" || s == "or" || s == "xor" || s == "test" || s == "shl" || s == "shr" 
        || s == "ldr" || s == "str" ){
            brojDirektiva++;
        }
    }
    if(brojDirektiva > 1) return true;
    return false;

}

bool proveraLabelaNijePrva(Lista *tokeniLinije, regex labelaReg) {
    for(int i=0; i<tokeniLinije->velicina(); i++) {
        string s = tokeniLinije->dohvati(i);
        if(regex_match(s, labelaReg) && i != 0) {
            return true;
        }
    }

    return false;
}

int convertHexToDecimal(string heksaBroj) {

    unsigned int x;   
    std::stringstream ss;
    ss << std::hex << heksaBroj;
    ss >> x;
    // cout<<x<<endl;
    return x;

    int velicina = heksaBroj.length();
    int tezina = 1;
    int broj = 0;
    int dokle;
    if(heksaBroj[0] == '-'){
        dokle = 2;
        // cout<<"MINUS"<<endl;
    }else {
        dokle = 1;
    }
    for(int i = velicina-1; i!= dokle; i--){
        switch (heksaBroj[i])
        {
        case '0':
            broj = broj + 0 * tezina;
            break;
        case '1':
            broj =broj + 1*tezina;
            break;
        case '2':
            broj =broj + 2*tezina;
            break;
        case '3':
            broj =broj + 3*tezina;
            break;
        case '4':
            broj =broj + 4*tezina;
            break;
        case '5':
            broj =broj + 5*tezina;
            break;
        case '6':
            broj =broj + 6*tezina;
            break;
        case '7':
            broj =broj + 7*tezina;
            break;
        case '8':
            broj =broj + 8*tezina;
            break;
        case '9':
            broj =broj + 9*tezina;
            break;
        case 'A':
            broj =broj + 10*tezina;
            break;
        case 'B':
            broj =broj + 11*tezina;
            break;
        case 'C':
            broj =broj + 12*tezina;
            break;
        case 'D':
            broj =broj + 13*tezina;
            break;
        case 'E':
            broj =broj + 14*tezina;
            break;
        case 'F':
            broj =broj + 15*tezina;
            break;

        }
        if(tezina == 1) {
            tezina = 16;
        }else {
            tezina *= 16;
        }
    }
    if(heksaBroj[0] == '-'){
        broj = 0 - broj;
    }

    return broj;
}

string convertDecimalToHex(short decimal_value) {
    std::stringstream ss;
    ss<< std::hex << decimal_value; // int decimal_value
    std::string res ( ss.str() );

    // std::cout << res;
    return res;
}

int dohvatiBrojRegistra(string registar) {
    if(registar == "r0"){
        return 0;
    }
    if(registar == "r1"){
        return 1;
    }
    if(registar == "r2"){
        return 2;
    }
    if(registar == "r3"){
        return 3;
    }
    if(registar == "r4"){
        return 4;
    }
    if(registar == "r5"){
        return 5;
    }
    if(registar == "r6" || registar == "sp"){
        return 6;
    }
    if(registar == "r7" || registar == "pc"){
        return 7;
    }
    if(registar == "psw"){
        return 8;
    }

    return 0;
}

string decimalToBin(int n) {
    string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}

int binToDecimal(string bin) {
    int broj = 0;
    int tezina = 1;
    int velicina = bin.length();
    for(int i = velicina - 1; i>=0; i--) {
        // cout<<"STIGAO"<<endl;
        // cout<<"tezina: " <<tezina<<endl;
        int br;
        if(bin[i] == '1'){
            br = 1;
        }else {
            br = 0;
        }
        broj += br *tezina;
        if(tezina == 1) {
            tezina = 2;
        }else{
            tezina = 2 * tezina;
        }
    }
    return broj;

}

bool proveraDefinisanostiSimbola(TabelaSimbola *tabelaSimbola) {
    bool ret = false;
    for(int i=1; i<tabelaSimbola->velicina(); i++){
        if(tabelaSimbola->dohvati(i)->dohvatiSekciju() == 0) {
            if(tabelaSimbola->dohvati(i)->dohvatiExtern() != 'e') {
                ret = true;
                cout<< "Greska simbol "<< tabelaSimbola->dohvati(i)->dohvatiNaziv() << " nije definisan" <<endl; 
            }
        }
    }
    return ret;
}

int proveraSintaksnoOperand(string operand, bool operacijaSkoka, TabelaSimbola *tabelaSimbola, Lista *tokeniLinije, bool labela, bool PuPoCall) {
    string reg = "r0|r1|r2|r3|r4|r5|r6|r7|sp|pc|psw";
    string literalBroj = "-?[0-9]+";
    string literalHex ="-?(0x)([a-fA-F0-9]+)";
    string simbolStr = "([a-z]|[A-Z])[a-z|A-Z|0-9|_]*";
    
    
    regex detektovanjeLiteralaPodatak("\\$?(("+literalBroj+")|("+literalHex +"))");
    regex regDirPodatak("(" + reg +")");
    regex regIndPodatak("\\[(" + reg +")\\]");
    regex regIndPomPocetakPodatak("\\[(" + reg +")");
    regex regIndPomKrajPodatak("(("+ literalBroj+")|("+literalHex+")|("+simbolStr+"))\\]");
    regex detektovanjeSimbolaPodatak("(\\$|\\%)?("+simbolStr+")");
    
    regex detektovanjeSimbola("(\\*|\\%)?("+simbolStr+")");
    regex detektovanjeLiterala("\\*?(("+literalBroj+")|("+literalHex +"))");
    regex registar(reg);
    regex regDir("\\*(" + reg +")");
    regex regInd("\\*\\[(" + reg +")\\]");
    regex regIndPomPocetak("\\*\\[(" + reg +")");
    regex regIndPomKraj("(("+ literalBroj+")|("+literalHex+")|("+simbolStr+"))\\]");
    regex simbolOriginalReg(simbolStr);

    // cout<<"operand "<< operand <<endl;
    if(operacijaSkoka) {
        // cout<<"USAO"<<endl;
        if(regex_match(operand, registar)) {
            cout<<"Sintaksna greska na liniji ";
            return 0;
        }
        if(regex_match(operand, detektovanjeLiterala)) {
            // cout<<"USAO1"<<endl;
            if(labela) {
                if(tokeniLinije->velicina() != 3){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }else{
                if(tokeniLinije->velicina() != 2){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }
            
            return 5;
        }
        if(regex_match(operand, regDir)){
            if(labela) {
                if(tokeniLinije->velicina() != 3){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }else{
                if(tokeniLinije->velicina() != 2){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }
            return 3;
        }
        if(regex_match(operand, regInd)){
            if(labela) {
                if(tokeniLinije->velicina() != 3){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }else{
                if(tokeniLinije->velicina() != 2){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }

            return 3;
        }
        if(regex_match(operand, regIndPomPocetak)){
            int velicina = tokeniLinije->velicina();
            if(labela) {
                if(velicina != 5){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }else{
                if(velicina != 4){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }
            int i;
            if(labela){
                i = 3;
            }else{
                i = 2;
            }
            string sledeci = tokeniLinije->dohvati(i);
            if(sledeci != "+"){
                cout<<"Sintaksna greska na liniji ";
                return 0;
            }

            if(labela){
                i = 4;
            }else{
                i = 3;
            }
            // cout<<"USAO"<<endl;
            sledeci = tokeniLinije->dohvati(i);
            if(!regex_match(sledeci, regIndPomKraj)){
                // cout<<"USAO"<<endl;
                cout<<"Sintaksna greska na liniji ";
                return 0;
            }
            // }else{
            //     // cout<<sledeci<<endl;
            //     sledeci.erase(sledeci.size()-1);
            //     // cout<<sledeci<<endl;
            //     if(regex_match(sledeci, simbolOriginalReg)){
            //         // cout<<"USAO"<<endl;
            //         if(!tabelaSimbola->postojiSimbol(sledeci)){
            //             // cout<<"USAO1"<<endl;
            //             cout<<"Nedefinisan simbol na liniji ";
            //             return 0;
            //         }
            //     }
            // }
            // cout<<"USAO1"<<endl;
            return 5;
        }
        if(regex_match(operand, detektovanjeSimbola)) {
            if(labela) {
                if(tokeniLinije->velicina() != 3){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }else{
                if(tokeniLinije->velicina() != 2){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }
            // cout<<"USAO"<<endl;
            // string op = "";
            // if(operand[0] == '*' || operand[0] == '%'){
            //     for(int i=1; i<operand.length(); i++){
            //         op += operand[i];
            //     }
            // }else{
            //     op = operand;
            // }
            // if(!tabelaSimbola->postojiSimbol(op)){
            //     cout<< "Nedefinisan simbol na liniji ";
            //     return 0;
            // }else{
            //     return 5;
            // }
            return 5;
        }

        

    }else { // odavde pocinje za operacije sa podacima ldr, str
        if(regex_match(operand, detektovanjeLiteralaPodatak)) {
            int velicina = tokeniLinije->velicina();
            if(labela){
                if(velicina != 4){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }else{
                if(velicina != 3){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }
            
            return 5;
        }
        
        
        if(regex_match(operand, regDirPodatak)){
            int velicina = tokeniLinije->velicina();
            if(labela){
                if(velicina != 4){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }else{
                if(velicina != 3){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }

            return 3;
        }
        if(regex_match(operand, regIndPodatak)){
            int velicina = tokeniLinije->velicina();
            if(labela){
                if(velicina != 4){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }else{
                if(velicina != 3){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }

            return 3;
        }
        if(regex_match(operand, regIndPomPocetakPodatak)){
            int velicina = tokeniLinije->velicina();
            if(labela) {
                if(velicina != 6){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }else{
                if(velicina != 5){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }
            int i;
            if(labela){
                i = 4;
            }else{
                i = 3;
            }
            string sledeci = tokeniLinije->dohvati(i);
            if(sledeci != "+"){
                cout<<"Sintaksna greska na liniji ";
                return 0;
            }

            if(labela){
                i = 5;
            }else{
                i = 4;
            }
            // cout<<"USAO"<<endl;
            sledeci = tokeniLinije->dohvati(i);
            if(!regex_match(sledeci, regIndPomKrajPodatak)){
                // cout<<"USAO"<<endl;
                cout<<"Sintaksna greska na liniji ";
                return 0;
            }

            return 5;
        }
        if(regex_match(operand, detektovanjeSimbolaPodatak)) {
            if(labela) {
                if(tokeniLinije->velicina() != 4){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }else{
                if(tokeniLinije->velicina() != 3){
                    cout<<"Sintaksna greska na liniji ";
                    return 0;
                }
            }
            
            return 5;
        }
        
        

    }


    cout<< "Sintaksna greska na liniji ";
    return 0;
}

int main(int argc, char *argv[])
{

    // if (argc < 4)
    // {
    //     cout << "Neispravan broj argumenata komandne linije " << endl;
    //     return 0;
    // }

    string imeIzlaznogFajla;
    string imeUlaznogFajla;
    //============
    string asembler = argv[0];
    if(argc == 2) {
        
        if(asembler == "asembler" || asembler == "./asembler"){
            imeUlaznogFajla = argv[1];

            imeIzlaznogFajla = "asm.txt";
        }else {
            cout << "Greska, pogresan format u komandnoj liniji "<<endl;
            exit(-1);
        }
    }else{
        if(argc == 4) {
            if(asembler == "asembler" || asembler == "./asembler"){
                string opcija = argv[1];
                if(opcija == "-o"){
                    imeIzlaznogFajla = argv[2];
                    imeUlaznogFajla = argv[3];
                }else{
                    cout << "Greska, pogresan format u komandnoj liniji "<<endl;
                    exit(-1); 
                }

                
            }else {
                cout << "Greska, pogresan format u komandnoj liniji "<<endl;
                exit(-1);
            }

        }else {
            cout << "Greska, pogresan broj argumenata komandne linije "<<endl;
            exit(-1);
        }
    }

    // string asembler = argv[1];

    // if ("asembler" == asembler)
    // {
    //     if (strcmp("-o", argv[2]) == 0)
    //     {
    //         imeIzlaznogFajla = argv[3];
    //         imeUlaznogFajla = argv[4];
    //     }
    //     else
    //     {
    //         imeUlaznogFajla = argv[2];
    //         imeIzlaznogFajla = argv[3];
    //     }
    // }

    ifstream ulazniFajl(imeUlaznogFajla);
    if (ulazniFajl.is_open() == false)
    {
        cout << "Greska ulazni fajl sa tim imenom ne postoji" << endl;
        exit(-1);
    }
    

    string linija;
    string rec = "";
    int brojLinije = 1;
    //napravili smo listu za tokene, odnosno reci
    Lista *tokeniLinije = new Lista();
    //da li je prepoznat komentar u liniji
    bool komentar = false;
    //napravimo praznu tabelu relokacija
    TabelaRelokacija *tabelaRelokacija = new TabelaRelokacija();
    //napravimo praznu tabelu simbola
    TabelaSimbola *tabelaSimbola = new TabelaSimbola();
    //redni broj sekcije u tabeli simbola 
    int tekucaSekcija = 0;
    //Location counter;
    int locationCounter = 0;
    //detektovali labelu
    string labela = "";
    //u tekucoj liniji labela
    bool tekucaLinijaLabela = false;
    //za gresku
    bool detektovanaGreska = false;
    //ako nismo usli ni u jedan if odnosno nismo prepoznali nista
    //ispisemo da imamo sintaksnu gresku
    bool postojiSintaksnaGreska = true;
    //ako end ne postoji greska, mora postojati na kraju programa
    bool end = false;



    // boost::regex sectionReg ("'.section'");
    //regex za prepoznavanje labele
    regex labelaReg("(([a-z]|[A-Z])[a-z|A-Z|0-9|_]*:)");

    regex simbolUListiReg("(([a-z]|[A-Z])[a-z|A-Z|0-9|_]*,)"); //i ovo kao identifikator u listi
    regex simbolReg("([a-z]|[A-Z])[a-z|A-Z|0-9|_]*"); //moze da se koristi i kao identifikator
    regex nazivSekcijeReg("([a-zA-Z_][a-zA-Z_0-9]*)+");
    regex brojReg("-?[0-9]+"); //literal
    regex brojUListiReg("-?([0-9]+,)");//literal u listi
    regex heksaBrojreg("-?(0x)([a-fA-F0-9]+)");//literal 
    regex heksaBrojUListireg("-?(0x)([a-fA-F0-9]+,)");//literal u listi
    regex proveraZaWordReg("[a-fA-F8-9]");
    regex programskiDostupniRegistriReg("r0|r1|r2|r3|r4|r5|r6|r7|sp|pc|psw");
    regex registarUListiReg("r0,|r1,|r2,|r3,|r4,|r5,|r6,|r7,|sp,|pc,|psw,");
    // regex nazivSekcijeReg("[a-zA-Z_][a-zA-Z_0-9]*\\.[a-zA-Z0-9]+");

    // regex nazivSekcijeReg("[a-z]|[A-Z])[a-z|A-Z|0-9|_]*");

    while (getline(ulazniFajl, linija)){
        postojiSintaksnaGreska = true;
        tekucaLinijaLabela = false;
        int duzinaLinije = linija.size();

        for (int i = 0; i < duzinaLinije; i++){
            char znak = linija[i];
            if (znak == '#'){
                komentar = true;
            }
            if (!komentar){
                if (znak == ' ' || i == duzinaLinije - 1 || znak == '\t'){
                    if (i == duzinaLinije - 1){
                        if(znak != ' ' && znak != '\t'){
                            rec += znak;
                        } 
                    }
                    if (rec != ""){
                        tokeniLinije->dodaj(rec);
                        // cout << rec << endl;
                    }
                    rec = "";
                }
                else{
                    rec += znak;
                }
            }
        }

        // if(regex_match (linija, sectionReg) ) {
        //     cout << "Pronadjena sekcija " << endl;
        // }
        // if(regex_match (linija, identifikator) ) {
        //     cout << "Linija " << brojLinije << ":" << linija << endl;
        //     cout << "Pronadjen identifikator " << endl;
        // }

        
        

        // string labela = "";
        // if(tokeniLinije->velicina()!= 0){
        //     rec = tokeniLinije->dohvati(0);
        // }
        
        
        
        
        // if(regex_match (rec, labelaReg) ) {
        //     labela = rec;
        //     cout<< "LABELA :" << labela << endl;
        // }
        
        if(tokeniLinije->velicina() == 0) {
            komentar = false;
            delete tokeniLinije;
            tokeniLinije = new Lista();
            brojLinije++;
            continue;
        }

        //ako detektujemo vise direktiva u jednoj liniji vrati gresku
        bool viseDirektiva = proveraViseDirektiva(tokeniLinije);
        bool labelaNijePrva = proveraLabelaNijePrva(tokeniLinije, labelaReg);
        if(viseDirektiva || labelaNijePrva) {
            detektovanaGreska = true;
            if(viseDirektiva)  {
                cout<<"Greska na liniji "<< brojLinije <<" vise direktiva u jednoj liniji"<<endl;
            }else {
                cout<<"Greska na liniji "<< brojLinije <<" labela mora bini na pocetku linije"<<endl;
            }
            
            komentar = false;
            delete tokeniLinije;
            tokeniLinije = new Lista();
            brojLinije++;
            continue;
        }

        string word = tokeniLinije->dohvati(0);

        if(regex_match(word, labelaReg)) {
            // cout<<"LABELA" <<endl;
            // postojiSintaksnaGreska = false;
            if(tekucaSekcija == 0) {
                detektovanaGreska = true;
                cout<<"Greska na liniji "<< brojLinije <<" labela mora biti unutar sekcije"<<endl;
            }else {
                if(labela != "") {
                    if(tabelaSimbola->postojiSimbol(labela)) {
                        Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                        s->postaviSekciju(tekucaSekcija);
                        s->postaviOfset(locationCounter);
                        labela = "";
                    }else {
                        Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                        tabelaSimbola->dodaj(s);
                        labela="";
                    }
                    
                }



                for(int i=0; i<word.size()-1; i++) {
                    labela += word[i];
                }

                //dodali smo simbol u tabelu simbola
                // Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                // tabelaSimbola->dodaj(s);
                bool postojiSimbol = tabelaSimbola->postojiSimbol(labela);
                //ako je sekcija simbola jednaka 0 onda to znaci da je nedefinisan
                //pa ga mi dodefinisemo
                if(postojiSimbol && tabelaSimbola->dohvatiSekciju(labela)->dohvatiSekciju() != 0) {
                    
                    labela = "";
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" visestruko definisanje"<<endl;
                }else {
                    tekucaLinijaLabela = true;
                    if(tokeniLinije->velicina() != 1) {
                        
                        // cout<<"LABELA != 1" <<endl;
                        word = tokeniLinije->dohvati(1);
                    }
                }

                
                
            }
            
            

            //cout<<"labela " << labela << endl;
        }
        
        

        if(word == ".section") {
            postojiSintaksnaGreska = false;
            bool greskaSekcija = false;
            
            if(tekucaLinijaLabela) {
                if(tokeniLinije->velicina() > 3) {
                    greskaSekcija = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" sintaksna greska"<<endl;
                }
                if(tokeniLinije->velicina() == 2) {
                    greskaSekcija = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" Sekcija mora imati ime"<<endl;
                }

            }else {
                if(tokeniLinije->velicina() > 2) {
                    greskaSekcija = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" Sekcija moze imati samo jedno ime"<<endl;
                }
                if(tokeniLinije->velicina() == 1) {
                    greskaSekcija = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" Sekcija mora imati ime"<<endl;
                }
            }
            if(!greskaSekcija) {
                if(labela != "") {
                    if(tabelaSimbola->postojiSimbol(labela)) {
                        Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                        s->postaviSekciju(tekucaSekcija);
                        s->postaviOfset(locationCounter);
                        labela = "";
                    }else {
                        Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                        tabelaSimbola->dodaj(s);
                        labela="";
                    }
                    
                }

                if(tekucaSekcija != 0) {
                    Simbol *s = tabelaSimbola->dohvati(tekucaSekcija);
                    s->postaviVelicinuSekcije(locationCounter);
                }

                locationCounter = 0;

                string imeSekcije = "";
                if(tekucaLinijaLabela) {
                    imeSekcije = tokeniLinije->dohvati(2);
                }else {
                    imeSekcije = tokeniLinije->dohvati(1);
                }

                // if(regex_match(imeSekcije, nazivSekcijeReg)){
                //         cout<<"usli u regex sekcije"<<endl;
                // }
                if(!regex_match(imeSekcije, nazivSekcijeReg)) {
                    detektovanaGreska=true;
                    cout<<"Greska na liniji "<< brojLinije <<" sintaksna greska"<<endl;
                }else{
                        
                    Simbol *s = new Simbol(imeSekcije, "R"); //treba samo srediti prava pristupa
                    if(tabelaSimbola->postojiSimbol(imeSekcije)){
                        detektovanaGreska = true;
                        cout<<"Greska na liniji "<< brojLinije <<" visestruko definisanje"<<endl;
                    }else{
                        tabelaSimbola->dodaj(s);
                
                        s = tabelaSimbola->dohvatiSekciju(imeSekcije);
                        if(s != nullptr){
                            tekucaSekcija = s->dohvatiRedniBr();
                            s->postaviSekciju(tekucaSekcija);
                        }
                    }
                }


            }
            
            
        }

        

        //prepoznavanje .extern direktive
        if(word == ".extern") {
            postojiSintaksnaGreska = false;
            //mora da ima neke simbole
            bool greskaExtern = false;
            if(tekucaLinijaLabela) {
                if(tokeniLinije->velicina() == 2) {
                    greskaExtern = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" mora se znati koji se simbol uvozi"<<endl;
                }
            }else {
                if(tokeniLinije->velicina() == 1) {
                    greskaExtern = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" mora se znati koji se simbol uvozi"<<endl;
                }
            }
            if(!greskaExtern) {
                if(labela != "") {
                    if(tabelaSimbola->postojiSimbol(labela)) {
                        Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                        s->postaviSekciju(tekucaSekcija);
                        s->postaviOfset(locationCounter);
                        labela = "";
                    }else {
                        Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                        tabelaSimbola->dodaj(s);
                        labela="";
                    }
                    
                }

                int i;
                if(tekucaLinijaLabela) {
                    i = 2;
                }else {
                    i = 1;
                }

                //ako je tekucaSekcija = 0 to znaci da je to ona nulta UND
                    for(i; i<tokeniLinije->velicina(); i++){

                        string nazivSimbola = tokeniLinije->dohvati(i);
                        bool mozeDodajSimbol = true;
                        if(i != tokeniLinije->velicina()-1) {
                            if(regex_match(nazivSimbola, simbolUListiReg)) {
                                nazivSimbola.erase(nazivSimbola.size()-1);
                            }else{
                                mozeDodajSimbol = false;
                                detektovanaGreska = true;
                                cout<<"Greska na liniji "<< brojLinije <<" sintaksna greska"<<endl;
                            }
                        }else {
                            if(!regex_match(nazivSimbola, simbolReg)) {
                                mozeDodajSimbol = false;
                                detektovanaGreska = true;
                                cout<<"Greska na liniji "<< brojLinije <<" sintaksna greska"<<endl;
                            }
                        }
                        if(mozeDodajSimbol) {
                            if(tabelaSimbola->postojiSimbol(nazivSimbola)){
                                detektovanaGreska = true;
                                cout<<"Greska na liniji "<< brojLinije <<" visestruko definisanje"<<endl;
                            }else{
                                //ako treba drugi argument ispraviti na tekucaSekcija
                                Simbol *simbol = new Simbol(nazivSimbola, 0, 0);
                                simbol->postaviLokal('g');
                                simbol->postaviExtern('e');
                                tabelaSimbola->dodaj(simbol);
                            }
                            
                        }
                        
                    }

                        
                
                    
                
            }

        }
        

        //prepoznavanje global direktive
        if(word == ".global") {
            postojiSintaksnaGreska = false;
            bool greskaGlobal = false;
            if(tekucaLinijaLabela) {
                if(tokeniLinije->velicina() == 2) {
                    greskaGlobal = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" mora se znati koji se proglasava globalnim"<<endl;
                }
            }else {
                if(tokeniLinije->velicina() == 1) {
                    greskaGlobal = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" mora se znati koji se proglasava globalnim"<<endl;
                }
            }

            if(!greskaGlobal) {

                if(labela != "") {
                    if(tabelaSimbola->postojiSimbol(labela)) {
                        Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                        s->postaviSekciju(tekucaSekcija);
                        s->postaviOfset(locationCounter);
                        labela = "";
                    }else {
                        Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                        tabelaSimbola->dodaj(s);
                        labela="";
                    }
                    
                }

                int index;
                if(tekucaLinijaLabela) {
                    index = 2;
                }else {
                    index = 1;
                }

                for(index; index<tokeniLinije->velicina(); index++){

                    string nazivSimbola = tokeniLinije->dohvati(index);
                    // cout << nazivSimbola << endl;
                    bool mozeDodajSimbol = true;
                    if(index != tokeniLinije->velicina()-1) {
                        if(regex_match(nazivSimbola, simbolUListiReg)) {
                            nazivSimbola.erase(nazivSimbola.size()-1);
                        }else{
                            mozeDodajSimbol = false;
                            detektovanaGreska = true;
                            cout<<"Greska na liniji "<< brojLinije <<" sintaksna greska"<<endl;
                        }
                    }else {
                        // cout<<nazivSimbola.length() << endl;
                        if(!regex_match(nazivSimbola, simbolReg)) {
                            // cout<<"usao"<<endl;
                            mozeDodajSimbol = false;
                            detektovanaGreska = true;
                            cout<<"Greska na liniji "<< brojLinije <<" sintaksna greska"<<endl;
                        }
                    }
                    if(mozeDodajSimbol) {
                    //dohvatimo simbole iz ts i azuriramo njihove vrednosti lokal
                    //ako ne postoji u ts onda greska, nedefinisani simbol
                    //ova funkcija vraca i ostale simbole ne samo sekcije
                        Simbol *s = tabelaSimbola->dohvatiSekciju(nazivSimbola);
                        if(s == nullptr) {
                            Simbol *s = new Simbol(nazivSimbola, 0, 0);
                            s->postaviLokal('g');
                            tabelaSimbola->dodaj(s);

                        }else {
                            s->postaviLokal('g');
                        }
                    }

                }
                


            }
            
        }

       

        if(word == ".word") {
            postojiSintaksnaGreska = false;
            bool greskaWord = false;
            if(tekucaSekcija == 0) {
                greskaWord = true;
                detektovanaGreska = true;
                cout<<"Greska na liniji "<< brojLinije <<" .word mora unutar sekcije"<<endl;
            }
            if(tekucaLinijaLabela){
                if(tokeniLinije->velicina() == 2) {
                    greskaWord = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" nedostaje lista simbola/literala za .word"<<endl;
                }
            }else {
                if(tokeniLinije->velicina() == 1) {
                    greskaWord = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" nedostaje lista simbola/literala za .word"<<endl;
                }
            }
            if(!greskaWord) {

                if(labela != "") {
                    if(tabelaSimbola->postojiSimbol(labela)) {
                        Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                        s->postaviSekciju(tekucaSekcija);
                        s->postaviOfset(locationCounter);
                        labela = "";
                    }else {
                        Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                        tabelaSimbola->dodaj(s);
                        labela="";
                    }
                    
                }
                int i;
                if(tekucaLinijaLabela) {
                    i = 2;
                }else {
                    i = 1;
                }
                for(i; i<tokeniLinije->velicina(); i++){

                    string naziv = tokeniLinije->dohvati(i);
                    bool mozeDalje = true;
                    if(i == tokeniLinije->velicina()-1){
                        if(!regex_match(naziv, simbolReg)){
                            if(!regex_match(naziv, brojReg)){
                                if(!regex_match(naziv, heksaBrojreg)) {
                                    mozeDalje = false;
                                    detektovanaGreska = true;
                                    cout<<"Greska na liniji "<< brojLinije <<" sintaksna greska"<<endl;
                                }
                            }

                        }

                    }else {
                        if(!regex_match(naziv, simbolUListiReg)){
                            if(!regex_match(naziv, brojUListiReg)){
                                if(!regex_match(naziv, heksaBrojUListireg)) {
                                    mozeDalje = false;
                                    detektovanaGreska = true;
                                    cout<<"Greska na liniji "<< brojLinije <<" sintaksna greska"<<endl;
                                }
                            }

                        }  
                    }
                    if(mozeDalje) {
                        locationCounter += 2;
                    }
                    



                }
            }

        }

        

        if(word == ".skip"){
            
            postojiSintaksnaGreska = false;
            bool greskaSkip = false;
            if(tekucaSekcija == 0) {
                // cout<<"SKIP"<< endl;
                greskaSkip = true;
                detektovanaGreska = true;
                cout<<"Greska na liniji "<< brojLinije <<" .skip mora unutar sekcije"<<endl;
            }
            if(tekucaLinijaLabela){
                if(tokeniLinije->velicina() == 2) {
                    // cout<<"SKIP1"<< endl;
                    greskaSkip = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" nedostaje literal za .skip"<<endl;
                }
                if(tokeniLinije->velicina() > 3) {
                    greskaSkip = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" sintaksna greska"<<endl;
                }
            }else {
                if(tokeniLinije->velicina() == 1) {
                    // cout<<"SKIP2"<< endl;
                    greskaSkip = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" nedostaje literal za .skip"<<endl;
                }
                if(tokeniLinije->velicina() > 2) {
                    greskaSkip = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije <<" sintaksna greska"<<endl;
                }
            }

            if(!greskaSkip) {

                if(labela != "") {
                    if(tabelaSimbola->postojiSimbol(labela)) {
                        Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                        s->postaviSekciju(tekucaSekcija);
                        s->postaviOfset(locationCounter);
                        labela = "";
                    }else {
                        Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                        tabelaSimbola->dodaj(s);
                        labela="";
                    }
                    
                }

                // cout<<"SKIP3"<< endl;
                int index;
                if(tekucaLinijaLabela){
                    index = 2;
                }else {
                    index = 1;
                }
                string literal = tokeniLinije->dohvati(index);
                // cout<<"SKIP4"<< endl;
                // cout << "LITERAL" <<literal << endl;
                bool literalOk = true;
                if(!regex_match(literal, brojReg)){
                    if(!regex_match(literal, heksaBrojreg)){
                        literalOk = false;
                        detektovanaGreska = true;
                        cout<<"Greska na liniji "<< brojLinije <<" literal u nepravilnom formatu"<<endl;
                    }
                }
                
                if(literalOk){
                    if(regex_match(literal, brojReg)){
                        //pretvaranje stringa u broj
                        //cout<< "BROJ"<< endl;
                        if(literal[0] == '-'){
                            detektovanaGreska = true;
                            cout<<"Greska na liniji "<< brojLinije <<" ne moze negativan broj za skip"<<endl;
                        }else {
                            
                            int x = stoi(literal);
                            if(x > 65535) { //to znaci da je pomeraj veci od 0xFFFF, a nase adrese su 16obitne
                                detektovanaGreska = true;
                                cout<<"Greska na liniji "<< brojLinije <<" nema toliko memorije"<<endl;
                       
                            }else {
                                // int uvecaj = (int) literal;
                                locationCounter += x;
                            }
                            
                        }
                        
                    }
                    if(regex_match(literal, heksaBrojreg)){
                        if(literal[0] == '-'){
                            detektovanaGreska = true;
                            cout<<"Greska na liniji "<< brojLinije <<" ne moze negativan broj za skip"<<endl;
                        }else {
                            if(literal.length() > 6) { //0xFFFF ima 6 karaktera
                                detektovanaGreska = true;
                                cout<<"Greska na liniji "<< brojLinije <<" nema dovoljno memorije"<<endl;
                            }else {
                                int x = convertHexToDecimal(literal);
                                // cout << "VREDNOST LITERALA SKIP" << x << endl;
                                locationCounter += x;
                            }
                            
                        }
                        
                    }
                    
                }
            }

        }

        // if(brojLinije == 44) {
        //     cout << word.length() << endl;
        // }

        if(word == ".equ") {
            //vrednost simbola moze biti maksimalano 4 heksa cifre
            //treba ograniciti to i preko decimalnih brojeva
            //treba resiti problem prekoracenja brojeva, simbol moze imati najvise 4 heksa cifre
            //pritom sve je u komplementu dvojke 
            postojiSintaksnaGreska = false;
            bool greskaEqu = false;
            if(tekucaLinijaLabela) {
                //labela: .equ simbol, broj
                //ako ima razlicit broj od 4 znaci da nesto fali
                if(tokeniLinije->velicina() != 4) {
                    greskaEqu = true;
                    detektovanaGreska = true;
                    cout << "Greska na liniji " << brojLinije << " sintaksna greska" << endl;
                }
            }else {
                //.equ simbol, broj
                if(tokeniLinije->velicina() != 3) {
                    greskaEqu = true;
                    detektovanaGreska = true;
                    cout << "Greska na liniji " << brojLinije << " sintaksna greska" << endl;
                }
            }

            if(!greskaEqu) {
                // cout<<"EQU"<<endl;
                if(labela != "") {
                    if(tabelaSimbola->postojiSimbol(labela)) {
                        Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                        s->postaviSekciju(tekucaSekcija);
                        s->postaviOfset(locationCounter);
                        labela = "";
                    }else {
                        Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                        tabelaSimbola->dodaj(s);
                        labela="";
                    }
                    
                }

                int i;
                if(tekucaLinijaLabela){
                    i = 2;
                }else {
                    i = 1;
                }

                string simbol = tokeniLinije->dohvati(i);
                if(!regex_match(simbol, simbolUListiReg)) {
                    detektovanaGreska = true;
                    cout << "Greska na liniji " << brojLinije << " sintaksna greska" << endl;
                }else {
                    
                    simbol.erase(simbol.size()-1);
                    // cout<<simbol<<endl;
                    bool simbolPosotji = tabelaSimbola->postojiSimbol(simbol);
                    

                        if(tekucaLinijaLabela) {
                            i = 3;
                        }else{
                            i = 2;
                        }
                        string literal = tokeniLinije->dohvati(i);
                        if(regex_match(literal, brojReg)){
                            int br = stoi(literal);

                            // cout << br << "DASDA" << endl;
                            if(br > 65535 || br < -32768) {
                                detektovanaGreska = true;
                                cout<< "Greska na liniji " << brojLinije << " vrednost simbola na 2B" << endl;
                            }else {
                                // cout<<"VREDNOST "<< convertDecimalToHex(br) <<endl;
                                if(simbolPosotji) {
                                    // cout<< "POSTOJI SIMBOL"<<endl;
                                    Simbol *s = tabelaSimbola->dohvatiSekciju(simbol);
                                    //ovo znaci da je u sekciji 0, tj nije definisan, samo se nasao global pre ovoga
                                    if(s->dohvatiSekciju() == 0){
                                        s->postaviSekciju(1);
                                        s->postaviOfset(br);
                                    }else {
                                        detektovanaGreska = true;
                                        cout << "Greska na liniji " << brojLinije << " visestruko definisanje" << endl;
                                    }
                                    
                                }else {
                                    // cout<<"NE POSTOJI SIMBOL"<<endl;
                                    Simbol *s = new Simbol(simbol, 1, br);
                                    tabelaSimbola->dodaj(s);
                                }
                                
                            }

                        }else {
                            if(regex_match(literal, heksaBrojreg)){
                                if(literal[0] == '-'){
                                    string proveri = "";
                                    proveri += literal[3];
                                    //ako je -0xFFFF to ima 7 znakova maksimalan broj sto moze da se napise
                                    //svi brojevi veci od 0x8000 njihova negativna predstava na 16bita izgleda kao pozitivan broj
                                    //sto je pogresno zato ogranicenje da negativno ide (-0xFFFF do -0x8001)
                                    if(literal.length() > 7 || regex_match(proveri, proveraZaWordReg)) {
                                        if(literal != "-0x8000"){
                                            detektovanaGreska = true;
                                            cout<< "Greska na liniji " << brojLinije << " .equ simbol na 2B" << endl;
                                        }
                                    }
                                }else {
                                    if(literal.length() > 6) {
                                        detektovanaGreska = true;
                                        cout<< "Greska na liniji " << brojLinije << " .equ simbol na 2B" << endl;
                                    }
                                }
                                short br = convertHexToDecimal(literal);
                                // cout<<"BROJ "<<convertDecimalToHex(br);
                                if(simbolPosotji){
                                    // cout<< "POSTOJI SIMBOL"<<endl;
                                    Simbol *s = tabelaSimbola->dohvatiSekciju(simbol);
                                    //ovo znaci da je u sekciji 0, tj nije definisan, samo se nasao global pre ovoga
                                    if(s->dohvatiSekciju() == 0){
                                        s->postaviSekciju(1);
                                        s->postaviOfset(br);
                                    }else {
                                        detektovanaGreska = true;
                                        cout << "Greska na liniji " << brojLinije << " visestruko definisanje" << endl;
                                    }
                                }else {
                                    Simbol *s = new Simbol(simbol, 1, br);
                                    tabelaSimbola->dodaj(s);
                                }
                                
                                // cout<< "hex to decimal  " << br << endl;
                                // string broj = convertDecimalToHex(br);
                                // cout<< broj<< endl;

                            }else {
                                detektovanaGreska = true;
                                cout << "Greska na liniji " << brojLinije << " sintaksna greska" << endl;
                            }
                        }

                    


                    
                }
            }
        }

       

        if(word == ".end") {
            postojiSintaksnaGreska = false;

            if(labela != "") {
                if(tabelaSimbola->postojiSimbol(labela)) {
                    Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                    s->postaviSekciju(tekucaSekcija);
                    s->postaviOfset(locationCounter);
                    labela = "";
                }else {
                    Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                    tabelaSimbola->dodaj(s);
                    labela="";
                }
                    
            }

            if(tekucaSekcija != 0) {
                Simbol *s = tabelaSimbola->dohvati(tekucaSekcija);
                s->postaviVelicinuSekcije(locationCounter);
            }
            end = true;
            break;
        }

        
      
        if(word == "halt" || word == "int" || word == "iret" || word == "call" || word == "ret" || word == "jmp" 
        || word == "jeq" || word == "jne" || word == "jgt" || word == "push" || word == "pop" || word == "xchg" 
        || word == "add" || word == "sub" || word == "mull" || word == "div" || word == "cmp" || word == "not" 
        || word == "and" || word == "or" || word == "xor" || word == "test" || word == "shl" || word == "shr" 
        || word == "ldr" || word == "str" ){
            
            if(labela != "") {
                if(tabelaSimbola->postojiSimbol(labela)) {
                    Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                    s->postaviSekciju(tekucaSekcija);
                    s->postaviOfset(locationCounter);
                    labela = "";
                }else {
                    Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                    tabelaSimbola->dodaj(s);
                    labela="";
                }
                    
            }

        }


        if(word == "halt") {
            postojiSintaksnaGreska = false;
            bool greskaHalt = false;
            if(tekucaSekcija == 0) {
                greskaHalt = true;
                detektovanaGreska = true;
                cout<<"Greska na liniji "<< brojLinije << " halt mora unutar sekcije da bude" << endl;
            }
            if(tekucaLinijaLabela) {
                if(tokeniLinije->velicina() != 2) {
                    greskaHalt = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije << " sintaksna greska" << endl;
                }
            }else {
                if(tokeniLinije->velicina() != 1) {
                    greskaHalt = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije << " sintaksna greska" << endl;
                }
            }
            
            if(!greskaHalt) {
                if(labela != "") {
                    if(tabelaSimbola->postojiSimbol(labela)) {
                        Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                        s->postaviSekciju(tekucaSekcija);
                        s->postaviOfset(locationCounter);
                        labela = "";
                    }else {
                        Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                        tabelaSimbola->dodaj(s);
                        labela="";
                    }
                    
                }
                locationCounter++;
            }
        }

     

        if(word == "int"){
            postojiSintaksnaGreska = false;
            bool greskaInt = false;
            if(tekucaSekcija == 0) {
                greskaInt = true;
                detektovanaGreska = true;
                cout<<"Greska na liniji "<< brojLinije << " int mora unutar sekcije da bude" << endl;
            }
            if(tekucaLinijaLabela) {
                if(tokeniLinije->velicina() != 3) {
                    greskaInt = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije << " sintaksna greska" << endl;
                }
            }else {
                if(tokeniLinije->velicina() != 2) {
                    greskaInt = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije << " sintaksna greska" << endl;
                }
            }

            if(!greskaInt) {
                if(labela != "") {
                    if(tabelaSimbola->postojiSimbol(labela)) {
		                Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                        s->postaviSekciju(tekucaSekcija);
                        s->postaviOfset(locationCounter);
                        labela = "";
                    }else {
                        Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                        tabelaSimbola->dodaj(s);
                        labela="";
                    }
                }

                int i;
                if(tekucaLinijaLabela) {
                    i = 2;
                }else{
                    i = 1;
                }
                string registar = tokeniLinije->dohvati(i);
                if(!regex_match(registar, programskiDostupniRegistriReg)) {
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije << " sintaksna greska" << endl;
                }else {
                    locationCounter += 2;
                }
                
            }
        }

     
        if(word == "iret") {
            postojiSintaksnaGreska = false;
            bool greskaIret = false;
            if(tekucaSekcija == 0) {
                greskaIret = true;
                detektovanaGreska = true;
                cout<<"Greska na liniji "<< brojLinije << " iret mora unutar sekcije da bude" << endl;
            }
            if(tekucaLinijaLabela) {
                if(tokeniLinije->velicina() != 2) {
                    greskaIret = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije << " sintaksna greska" << endl;
                }
            }else {
                if(tokeniLinije->velicina() != 1) {
                    greskaIret = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije << " sintaksna greska" << endl;
                }
            }

            if(!greskaIret) {
                if(labela != "") {
                    if(tabelaSimbola->postojiSimbol(labela)) {
		                Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                        s->postaviSekciju(tekucaSekcija);
                        s->postaviOfset(locationCounter);
                        labela = "";
                    }else {
                        Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                        tabelaSimbola->dodaj(s);
                        labela="";
                    }
                }

                locationCounter++;
            }
        }

   

        if(word == "ret"){
            postojiSintaksnaGreska = false;
            bool greskaRet = false;
            if(tekucaSekcija == 0) {
                greskaRet = true;
                detektovanaGreska = true;
                cout<<"Greska na liniji "<< brojLinije << " ret mora unutar sekcije da bude" << endl;
            }
            if(tekucaLinijaLabela) {
                if(tokeniLinije->velicina() != 2) {
                    greskaRet = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije << " sintaksna greska" << endl;
                }
            }else {
                if(tokeniLinije->velicina() != 1) {
                    greskaRet = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije << " sintaksna greska" << endl;
                }
            }
            if(!greskaRet) {
                if(labela != "") {
                    if(tabelaSimbola->postojiSimbol(labela)) {
                        Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                        s->postaviSekciju(tekucaSekcija);
                        s->postaviOfset(locationCounter);
                        labela = "";
                    }else {
                        Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                        tabelaSimbola->dodaj(s);
                        labela="";
                    }
                }

                locationCounter++;
            }
        }

       

        if(word == "xchg" || word == "add" || word == "sub" || word == "mul" || word == "div" || word == "cmp" 
         || word == "and" || word == "or" || word == "xor" || word == "test" || word == "shl" || word == "shr"){
             
            postojiSintaksnaGreska = false;
            bool greska = false;
            if(tekucaSekcija == 0) {
                greska = true;
                detektovanaGreska = true;
                cout<<"Greska na liniji "<< brojLinije << " mora biti unutar sekcije" << endl;
            }
            if(tekucaLinijaLabela) {
                if(tokeniLinije->velicina() != 4) {
                    greska = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije << " sintaksna greska" << endl;
                }
            }else {
                if(tokeniLinije->velicina() != 3) {
                    greska = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije << " sintaksna greska" << endl;
                }
            }

            if(!greska) {
                if(labela != "") {
                    if(tabelaSimbola->postojiSimbol(labela)) {
                        Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                        s->postaviSekciju(tekucaSekcija);
                        s->postaviOfset(locationCounter);
                        labela = "";
                    }else {
                        Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                        tabelaSimbola->dodaj(s);
                        labela="";
                    }
                }
                int i;
                if(tekucaLinijaLabela) {
                    i = 2;
                }else {
                    i = 1;
                }

                string regD = tokeniLinije->dohvati(i);
                if(!regex_match(regD, registarUListiReg)) {
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<<brojLinije<<" sintaksna greska"<<endl;
                }else {
                    regD.erase(regD.size()-1);
                    if(tekucaLinijaLabela) {
                        i = 3;
                    }else {
                        i = 2;
                    }
                    string regS = tokeniLinije->dohvati(i);
                    if(!regex_match(regS, programskiDostupniRegistriReg)) {
                        detektovanaGreska = true;
                        cout<<"Greska na liniji "<<brojLinije<<" sintaksna greska"<<endl;
                    }else {
                        locationCounter += 2;
                    }
                }



                
            }
        }

        if(word == "not"){
            // cout<< "USAO" <<endl;
            postojiSintaksnaGreska = false;
            bool greskaNot = false;
            if(tekucaSekcija == 0) {
                greskaNot = true;
                detektovanaGreska = true;
                cout<<"Greska na liniji "<< brojLinije << " not mora unutar sekcije da bude" << endl;
            }
            if(tekucaLinijaLabela) {
                if(tokeniLinije->velicina() != 3) {
                    greskaNot = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije << " sintaksna greska" << endl;
                }
            }else {
                if(tokeniLinije->velicina() != 2) {
                    greskaNot = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<< brojLinije << " sintaksna greska" << endl;
                }
            }
            if(!greskaNot) {
                // cout<<"USAO"<<endl;
                if(labela != "") {
                    if(tabelaSimbola->postojiSimbol(labela)) {
                        Simbol *s = tabelaSimbola->dohvatiSekciju(labela);
                        s->postaviSekciju(tekucaSekcija);
                        s->postaviOfset(locationCounter);
                        labela = "";
                    }else {
                        Simbol *s = new Simbol(labela, tekucaSekcija, locationCounter);
                        tabelaSimbola->dodaj(s);
                        labela="";
                    }
                }
                int i;
                if(tekucaLinijaLabela) {
                    i = 2;
                }else {
                    i = 1;
                }

                string regD = tokeniLinije->dohvati(i);
                // cout<<regD<<endl;
                if(!regex_match(regD, programskiDostupniRegistriReg)) {
                    detektovanaGreska = true;
                    // cout<<"USAO" <<endl;
                    cout<<"Greska na liniji "<<brojLinije<<" sintaksna greska"<<endl;
                }else {
                    locationCounter += 2;
                }
            }
        }


        if(word == "call" || word == "jmp" || word == "jeq" || word == "jne" || word == "jgt"){
            postojiSintaksnaGreska = false;
            bool greska = false;
            if(tekucaSekcija == 0) {
                greska = true;
                detektovanaGreska = true;
                cout<<"Greska na liniji " << brojLinije << " mora biti unutar sekcije"<<endl;
            }
            if(tekucaLinijaLabela) {
                if(tokeniLinije->velicina() <3) {
                    greska = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji " << brojLinije << " sintaksna greska"<<endl;
                }
            }else{
                if(tokeniLinije->velicina() <2) {
                    greska = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji " << brojLinije << " sintaksna greska"<<endl;
                }
            }
            if(!greska) {
                int i;
                if(tekucaLinijaLabela) {
                    i = 2;
                }else {
                    i = 1;
                }
                string operand = tokeniLinije->dohvati(i);
                // cout<<operand <<endl;
                int resenje = proveraSintaksnoOperand(operand, true, tabelaSimbola, tokeniLinije, tekucaLinijaLabela, false);
                if(resenje == 0) {
                    detektovanaGreska = true;
                    cout<<brojLinije <<endl;
                }else{
                    locationCounter += resenje;
                }
                // cout<< "Resenje " <<resenje<<endl;

            }
           
            
        }//kraj za call, jmp..

        if(word == "ldr" || word == "str"){
            postojiSintaksnaGreska = false;
            bool greska = false;
            if(tekucaSekcija == 0) {
                greska = true;
                detektovanaGreska = true;
                cout<<"Greska na liniji " << brojLinije << " mora biti unutar sekcije"<<endl;
            }
            if(tekucaLinijaLabela) {
                if(tokeniLinije->velicina() <4) {
                    greska = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji " << brojLinije << " sintaksna greska"<<endl;
                }
            }else{
                if(tokeniLinije->velicina() <3) {
                    greska = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji " << brojLinije << " sintaksna greska"<<endl;
                }
            }
            if(!greska) {

                //treba ispitati regD pre ovoga
                int i;
                if(tekucaLinijaLabela){
                    i = 2;
                }else{
                    i = 1;
                }
                string registar = tokeniLinije->dohvati(i);
                if(!regex_match(registar, registarUListiReg)){
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<<brojLinije << " sintaksna greska"<<endl;
                }else{
                    if(tekucaLinijaLabela) {
                        i = 3;
                    }else {
                        i = 2;
                    }
                    string operand = tokeniLinije->dohvati(i);
                    // cout<<operand <<endl;
                    int resenje = proveraSintaksnoOperand(operand, false, tabelaSimbola, tokeniLinije, tekucaLinijaLabela, false);
                    if(resenje == 0) {
                        detektovanaGreska = true;
                        cout<<brojLinije <<endl;
                    }else{
                        locationCounter += resenje;
                    
                    }
                    // cout<< "Resenje " <<resenje<<endl;
                }

                

            }

        }//kraj za ldr i str
        

        if(word == "push" || word == "pop") {

            postojiSintaksnaGreska = false;
            bool greska = false;
            if(tekucaSekcija == 0) {
                greska = true;
                detektovanaGreska = true;
                cout<<"Greska na liniji "<<brojLinije << " mora biti unutar sekcije " <<endl;
            }
            if(tekucaLinijaLabela) {
                if(tokeniLinije->velicina() != 3){
                    greska = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<<brojLinije << " sintaksna greska " <<endl;
                }
            }else {
                if(tokeniLinije->velicina() != 2){
                    greska = true;
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<<brojLinije << " sintaksna greska " <<endl;
                }
            }

            if(!greska) {
                int i;
                if(tekucaLinijaLabela) {
                    i = 2;
                }else{
                    i = 1;
                }

                string regDest = tokeniLinije->dohvati(i);
                if(!regex_match(regDest, programskiDostupniRegistriReg)) {
                    detektovanaGreska = true;
                    cout<<"Greska na liniji "<<brojLinije << " sintaksna greska " <<endl;
                }else {
                    // int brojRegDest = dohvatiBrojRegistra(regDest);
                    // cout << brojRegDest<<endl;
                    locationCounter += 3;
                    
                }
                

            }
        }

        
        

        
        
        
        if(postojiSintaksnaGreska) {
            //proveravamo da li je labela prepoznata i stoji sama u liniji
            //ako jeste onda nije greska, ako nije onda je greska
            //!detektovanaGreska da ne bi ispisivao duplu gresku
            //ako slucajno ispisuje duplu gresku odkomentarisati 
            if((!tekucaLinijaLabela || !(tokeniLinije->velicina() == 1)) /*&& !detektovanaGreska*/){
                detektovanaGreska = true;
                cout<<"Greska na liniji "<< brojLinije <<" sintaksna greska"<<endl;
            }
            // cout<<"POSTOJI" <<endl;
            // cout<<word<<"   "<<word.length()<<endl;
            
        }
        




        
        // for(int i=0; i<tokeniLinije->velicina(); i++){
        //     cout << tokeniLinije->dohvati(i)<<endl;
        // }
            
        
        //kraj komentara je na kraju reda
        komentar = false;
        //brisemo listu jer krecemo u obradu novog reda
        delete tokeniLinije;
        tokeniLinije = new Lista();
        brojLinije++;
    }
    if(proveraDefinisanostiSimbola(tabelaSimbola)) {
        detektovanaGreska = true;
    }
    if(!end) {
        cout<<"Mora postojati end na kraju programa"<< endl;
        exit(-1);
    }
    // if(!detektovanaGreska){
    //     prikazTabeleSimbola(tabelaSimbola);
    // }
    if(detektovanaGreska) {
        exit(-1);
    }



    

    //pocinje drugi prolaz asemblera
    komentar = false;
    delete tokeniLinije;
    tokeniLinije = new Lista();
    brojLinije = 1;
    rec = "";
    locationCounter = 0;
    tekucaSekcija = 0;
    
    ulazniFajl.close();

    ifstream ulazniFajl1(imeUlaznogFajla);
    if (ulazniFajl1.is_open() == false)
    {
        cout << "Greska ulazni fajl sa tim imenom ne postoji" << endl;
        exit(-1);
    }
    ofstream izlazniFajl(imeIzlaznogFajla);
    if (izlazniFajl.is_open() == false)
    {
        cout << "Greska ulazni fajl sa tim imenom ne postoji" << endl;
        exit(-1);
    }

    izlazniFajl << "#tabela simbola \n";

    izlazniFajl<< "#Redni broj   Naziv              Sekcija    Ofset   Lokal   Velicina Sekcije \n"  ;

    for(int i = 0; i<tabelaSimbola->velicina(); i++) {

        string ispis;
        Simbol *s = tabelaSimbola->dohvati(i);
        if(s != nullptr){
            ispis ="    " + to_string(s->dohvatiRedniBr());
            int j = to_string(s->dohvatiRedniBr()).length();
            for(j; j<11; j++){
                ispis += " ";
            }
            ispis += s->dohvatiNaziv();
            j = s->dohvatiNaziv().length();
            for(j; j<20; j++) {
                ispis += " ";
            }
            ispis += to_string(s->dohvatiSekciju()) + "         " + convertDecimalToHex(s->dohvatiOfset());  //to_string(s->dohvatiOfset());
            // j = to_string(s->dohvatiOfset()).length();
            j = convertDecimalToHex(s->dohvatiOfset()).length();
            for(j; j<8; j++) {
                ispis += " ";
            }
            ispis += s->dohvatiLokal();
            
        }
        
        if(s->dohvatiOznakuSekcije()) {
            ispis += + "        " + convertDecimalToHex(s->dohvatiVelicinuSekcije()); //to_string(s->dohvatiVelicinuSekcije());
        }
        ispis += "\n";
        izlazniFajl << ispis;
    }
    izlazniFajl << "\n";


    

    while (getline(ulazniFajl1, linija)){
        // cout<<"DRUGI PROLAZ"<<endl;
        postojiSintaksnaGreska = true;
        tekucaLinijaLabela = false;
        int duzinaLinije = linija.size();

        for (int i = 0; i < duzinaLinije; i++){
            char znak = linija[i];
            if (znak == '#'){
                komentar = true;
            }
            if (!komentar){
                if (znak == ' ' || i == duzinaLinije - 1 || znak == '\t'){
                    if (i == duzinaLinije - 1){
                        if(znak != ' ' && znak != '\t'){
                            rec += znak;
                        } 
                    }
                    if (rec != ""){
                        tokeniLinije->dodaj(rec);
                        // cout << rec << endl;
                    }
                    rec = "";
                }
                else{
                    rec += znak;
                }
            }
        }

        if(tokeniLinije->velicina() == 0) {
            komentar = false;
            delete tokeniLinije;
            tokeniLinije = new Lista();
            brojLinije++;
            continue;
        }

        string word = tokeniLinije->dohvati(0);

        if(regex_match(word, labelaReg)) {
            // cout<<"LABELA" <<endl;
            for(int i=0; i<word.size()-1; i++) {
                labela += word[i];
            }
            bool postojiSimbol = tabelaSimbola->postojiSimbol(labela);
            if(tokeniLinije->velicina() != 1) {
                tekucaLinijaLabela = true;
                // cout<<"LABELA != 1" <<endl;
                word = tokeniLinije->dohvati(1);
            }

        }

        if(word == ".section"){
            string nazivSekcije;
            if(tekucaLinijaLabela) {
                nazivSekcije = tokeniLinije->dohvati(2);
            }else {
                nazivSekcije = tokeniLinije->dohvati(1);
            }
            if(tekucaSekcija != 0 && tabelaRelokacija->velicina() !=0) {
                izlazniFajl<< "\n";
                izlazniFajl<< "\n";
                izlazniFajl<< "#tabela relokacija za sekciju " ;
                izlazniFajl<< tabelaSimbola->dohvati(tekucaSekcija)->dohvatiNaziv();
                izlazniFajl << "\n";
                izlazniFajl<< "Simbol  Tip Relokacije  Offset" << "\n"  ;
                for(int i = 0; i<tabelaRelokacija->velicina(); i++) {
                    Relocation *s = tabelaRelokacija->dohvati(i);
                    if(s != nullptr){
                        string daIspisem;
                        daIspisem = "  " + to_string(s->dohvatiSimbol()) + "     " +
                        s->dohvatiTipRelokacije();
                        int j = s->dohvatiTipRelokacije().length();
                        for(j; j<19; j++) {
                            daIspisem += " ";
                        }
                        daIspisem += convertDecimalToHex(s->dohvatiOffset()) + "\n";
                        izlazniFajl << daIspisem;
                    }
                    
                }
            }
            Simbol *simbol = tabelaSimbola->dohvatiSekciju(nazivSekcije);
            if(simbol->dohvatiVelicinuSekcije() != 0){
                izlazniFajl << "\n";
                izlazniFajl << "#.section "<< nazivSekcije <<"\n";
            }

            delete tabelaRelokacija;
            tabelaRelokacija = new TabelaRelokacija();

            tekucaSekcija = tabelaSimbola->dohvatiSekciju(nazivSekcije)->dohvatiRedniBr();
            locationCounter = 0;
        }

        // if(word == ".extern") {

        // }

        // if(word == ".global") {
        //     for(int i=1; i<tokeniLinije->velicina(); i++){

        //         string nazivSimbola = tokeniLinije->dohvati(i);
        //         bool mozeDodajSimbol = true;
        //         if(i != tokeniLinije->velicina()-1) {
        //             if(regex_match(nazivSimbola, simbolUListiReg)) {
        //                 nazivSimbola.erase(nazivSimbola.size()-1);
        //             }else{
        //                 mozeDodajSimbol = false;
        //                 detektovanaGreska = true;
        //                 cout<<"Greska na liniji "<< brojLinije <<" sintaksna greska"<<endl;
        //             }
        //         }else {
        //             if(!regex_match(nazivSimbola, simbolReg)) {
        //                 mozeDodajSimbol = false;
        //                 detektovanaGreska = true;
        //                 cout<<"Greska na liniji "<< brojLinije <<" sintaksna greska"<<endl;
        //             }
        //         }
        //         if(mozeDodajSimbol) {
        //             //dohvatimo simbole iz ts i azuriramo njihove vrednosti lokal
        //             //ako ne postoji u ts onda greska, nedefinisani simbol
        //             //ova funkcija vraca i ostale simbole ne samo sekcije
        //             Simbol *s = tabelaSimbola->dohvatiSekciju(nazivSimbola);
        //             if(s == nullptr) {
        //                 detektovanaGreska = true;
        //                 cout<<"Greska na liniji "<< brojLinije <<" simbol nije definisan"<<endl;
        //             }else {
        //                 s->postaviLokal('g');
        //             }
        //         }
        //     }
        // }



        if(word == ".word") {
            // cout<<"STIGAO " <<endl;
            int i;
            if(tekucaLinijaLabela) {
                i = 2;
            }else {
                i = 1;
            }
            for(i; i<tokeniLinije->velicina(); i++){
                
                string naziv = tokeniLinije->dohvati(i);
                string broj;
                if(i == tokeniLinije->velicina()-1){
                    if(regex_match(naziv, simbolReg)){
                        if(!tabelaSimbola->postojiSimbol(naziv)) {
                            detektovanaGreska = true;
                            cout<<"Greska na liniji "<< brojLinije <<" simbol nije definisan"<<endl;
                        }else{
                            Simbol *s = tabelaSimbola->dohvatiSekciju(naziv);
                            int vrednost;
                            //redni broj simbola, koju sekciju popravljamo, kako (apsolutno adresa je 16 bita), offset gde se to nalazi
                            Relocation *r = new Relocation(s->dohvatiRedniBr(), tekucaSekcija, "R_HYPO_16", locationCounter);
                            if(s->dohvatiLokal() == 'l'){
                                //ako je lokalni simbol njegovu vrednost ugradjujemo u sam predmetni program
                                //a treba da se radi u odnosu na sekciju gde je definisan simbol
                                vrednost = s->dohvatiOfset();
                                r->postaviSimbol(s->dohvatiSekciju());
                            }else {
                                vrednost = 0;
                            }
                            
                            //ako je sekcija u kojoj je definisan pod rednim brojem 1
                            //to znaci da je dodat equ direktivom
                            //za takve simbole nema dodavanja relokacionog zapisa samo se 
                            //ubacuje njihova vrednost
                            if(s->dohvatiSekciju() == 1) {
                                vrednost = s->dohvatiOfset();
                                delete r;
                            }else {
                                tabelaRelokacija->dodaj(r);
                            }
                            

                            // cout<<"VREDNOST " << convertDecimalToHex(vrednost) <<endl;
                            broj = convertDecimalToHex(vrednost);
                            
                            
                            //treba da se upise u izlazni fajl
                            //i treba napraviti relokacioni zapis, za apsolutno adresiranje
                        }
                    }
                    if(regex_match(naziv, brojReg)){
                        int br = stoi(naziv);

                        // cout << br << "DASDA" << endl;
                        if(br > 65535 || br < -32768) {
                            detektovanaGreska = true;
                            cout<< "Greska na liniji " << brojLinije << " word je velicine 2B" << endl;
                        }else {
                            // cout<<"VREDNOST "<< convertDecimalToHex(br) <<endl;
                            broj = convertDecimalToHex(br);
                        }
                        
                    }
                    if(regex_match(naziv, heksaBrojreg)) {
                        if(naziv[0] == '-'){
                            string proveri = "";
                            proveri += naziv[3];
                            if(naziv.length() > 7 || regex_match(proveri, proveraZaWordReg)) {
                                if(naziv != "-0x8000"){
                                    detektovanaGreska = true;
                                    cout<< "Greska na liniji " << brojLinije << " word je velicine 2B" << endl;
                                }
                            }
                        }else {
                            if(naziv.length() > 6) {
                                detektovanaGreska = true;
                                cout<< "Greska na liniji " << brojLinije << " word sa maksimalno 4 heksa cifre" << endl;
                            }
                        }
                        short br = convertHexToDecimal(naziv);
                        // cout<< "hex to decimal  " << br << endl;
                        broj = convertDecimalToHex(br);
                        // cout<< broj<< endl;
                    }
                } else {
                    if(regex_match(naziv, simbolUListiReg)){
                        naziv.erase(naziv.size()-1);
                        if(!tabelaSimbola->postojiSimbol(naziv)) {
                            detektovanaGreska = true;
                            cout<<"Greska na liniji "<< brojLinije <<" simbol nije definisan"<<endl;
                        }else{
                            Simbol *s = tabelaSimbola->dohvatiSekciju(naziv);
                            int vrednost;
                            //redni broj simbola, koju sekciju popravljamo, kako (apsolutno adresa je 16 bita), offset gde se to nalazi
                            Relocation *r = new Relocation(s->dohvatiRedniBr(), tekucaSekcija, "R_HYPO_16", locationCounter);
                            if(s->dohvatiLokal() == 'l'){
                                //ako je lokalni simbol njegovu vrednost ugradjujemo u sam predmetni program
                                //a treba da se radi u odnosu na sekciju gde je definisan simbol
                                vrednost = s->dohvatiOfset();
                                r->postaviSimbol(s->dohvatiSekciju());
                            }else {
                                vrednost = 0;
                            }

                            if(s->dohvatiSekciju() == 1) {
                                vrednost = s->dohvatiOfset();
                                delete r;
                            }else {
                                tabelaRelokacija->dodaj(r);
                            }

                            // cout<<"VREDNOST " << convertDecimalToHex(vrednost) <<endl;
                            broj = convertDecimalToHex(vrednost);
                            //treba da se upise u izlazni fajl
                        }
                    }
                    if(regex_match(naziv, brojUListiReg)){
                        naziv.erase(naziv.size()-1);
                        int br = stoi(naziv);
                        // cout<<br << endl;
                        if(br > 65535 || br < -32768) {
                            detektovanaGreska = true;
                            cout<< "Greska na liniji " << brojLinije << " word je velicine 2B" << endl;
                        }else {
                            // cout<<"VREDNOST "<< convertDecimalToHex(br) <<endl;
                            broj = convertDecimalToHex(br);
                        }
                        // broj = convertDecimalToHex(br);
                        // cout<<"VREDNOST "<< convertDecimalToHex(br) <<endl;
                    }
                    if(regex_match(naziv, heksaBrojUListireg)) {
                        naziv.erase(naziv.size()-1);
                        if(naziv[0] == '-'){
                            string proveri = "";
                            proveri += naziv[3];
                            if(naziv.length() > 7 || regex_match(proveri, proveraZaWordReg)) {
                                if(naziv != "-0x8000"){
                                    detektovanaGreska = true;
                                    cout<< "Greska na liniji " << brojLinije << " word je velicine 2B" << endl;
                                }
                            }
                        }else {
                            if(naziv.length() > 6) {
                                detektovanaGreska = true;
                                cout<< "Greska na liniji " << brojLinije << " word sa maksimalno 4 heksa cifre" << endl;
                            }
                        }
                        short br = convertHexToDecimal(naziv);
                        // cout<< "hex to decimal  " << br << endl;
                        broj = convertDecimalToHex(br);
                        // cout<< broj<< endl;
                    }

                    
                    
                    
                }
                
                // if(locationCounter % 4 == 0) izlazniFajl << "\n";
                // locationCounter += 2;
                string ispis = "";
                            if(broj.length() > 4) {
                                detektovanaGreska = true;
                                cout <<"Greska na liniji " << brojLinije << " prekoracenje"<<endl;
                            }

                            int velicina = broj.length();
                            if(velicina == 1) {
                                ispis = "0";
                                ispis += broj[0];
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                                ispis += "00";
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                            }
                            if(velicina == 2) {
                                ispis = "";
                                ispis += broj[0];
                                ispis += broj[1];
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                                ispis += "00";
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                            }
                            if(velicina == 3) {
                                ispis = "0";
                                ispis += broj[2];
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                                ispis += broj[0];
                                ispis += broj[1];
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                            }
                            if(velicina == 4) {
                                
                                ispis += broj[2];
                                ispis += broj[3];
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                                ispis += broj[0];
                                ispis += broj[1];
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                            }

                            izlazniFajl << ispis;
            }
        }

        if(word == ".skip"){
            int index;
            if(tekucaLinijaLabela) {
                index = 2;
            }else {
                index = 1;
            }


            string literal = tokeniLinije->dohvati(index);
            int x;
            if(regex_match(literal, brojReg)) {
                x = stoi(literal);
                
                // locationCounter += x;
            }
            if(regex_match(literal, heksaBrojreg)){
                x = convertHexToDecimal(literal);
            }

            for(int i = 0; i<x; i++){
                // if(locationCounter % 4 == 0) izlazniFajl << "\n";
                izlazniFajl << "00";
                locationCounter++;
                if(locationCounter % 10 == 0) izlazniFajl << "\n";
                else izlazniFajl << " ";
                // locationCounter +=1;
            }
            // int x = stoi(literal);
            // //generisati sadrzaj u predmetnom programu
            // locationCounter += x;
        }


        if(word == ".end") {
            if(tekucaSekcija != 0 && tabelaRelokacija->velicina() !=0) {
                izlazniFajl<< "\n";
                izlazniFajl<< "\n";
                izlazniFajl<< "#tabela relokacija za sekciju " ;
                izlazniFajl<< tabelaSimbola->dohvati(tekucaSekcija)->dohvatiNaziv();
                izlazniFajl << "\n";
                izlazniFajl<< "Simbol  Tip Relokacije  Offset" << "\n"  ;
                for(int i = 0; i<tabelaRelokacija->velicina(); i++) {
                    Relocation *s = tabelaRelokacija->dohvati(i);
                    if(s != nullptr){
                        string daIspisem;
                        daIspisem = "  " + to_string(s->dohvatiSimbol()) + "     " +
                        s->dohvatiTipRelokacije();
                        int j = s->dohvatiTipRelokacije().length();
                        for(j; j<19; j++) {
                            daIspisem += " ";
                        }
                        daIspisem += convertDecimalToHex(s->dohvatiOffset()) + "\n";
                        izlazniFajl << daIspisem;
                    }
                }
            }
            break;
        }

        if(word == "halt") {

            izlazniFajl << "00";// << "halt"<<endl;
            locationCounter++;
            if(locationCounter % 10 == 0) izlazniFajl << "\n";
            else izlazniFajl << " ";
        }

        if(word == "int") {
            int i;
            if(tekucaLinijaLabela) {
                i = 2;
            }else {
                i = 1;
            }

            string registar = tokeniLinije->dohvati(i);
            int regBr = dohvatiBrojRegistra(registar);
            string bin = decimalToBin(regBr);
            bin += "1111";

            // cout<<"REGISTAR " << regBr<< " " << bin <<endl;
            int decimal = binToDecimal(bin);
            // cout<< binToDecimal(bin)<<endl;
            // cout<< convertDecimalToHex(decimal)<<endl;
            string ispis = "10";
            locationCounter++;
            if(locationCounter % 10 == 0) ispis += "\n";
            else ispis += " ";
            ispis += convertDecimalToHex(decimal);
            locationCounter++;
            if(locationCounter % 10 == 0) ispis += "\n";
            else ispis += " ";
            izlazniFajl << ispis;
            // locationCounter += 2;

        }

        if(word == "iret") {

            izlazniFajl << "20";
            locationCounter++;
            if(locationCounter % 10 == 0) izlazniFajl << "\n";
            else izlazniFajl << " ";
        }

        if(word == "ret") {
            izlazniFajl << "40";
            locationCounter++;
            if(locationCounter % 10 == 0) izlazniFajl << "\n";
            else izlazniFajl << " ";
        }

        if(word == "xchg" || word == "add" || word == "sub" || word == "mul" || word == "div" || word == "cmp" 
         || word == "and" || word == "or" || word == "xor" || word == "test" || word == "shl" || word == "shr"){

            int i;
            if(tekucaLinijaLabela) {
                i = 2;
            }else {
                i = 1;
            }
            string prvi = tokeniLinije->dohvati(i);
            prvi.erase(prvi.size()-1);
            if(tekucaLinijaLabela) {
                i = 3;
            }else {
                i = 2;
            }
            string drugi = tokeniLinije->dohvati(i);
            int regD = dohvatiBrojRegistra(prvi);
            int regS = dohvatiBrojRegistra(drugi);
            string destionation = convertDecimalToHex(regD);
            string source = convertDecimalToHex(regS);
            string ispis;
            if(word == "xchg"){
                ispis = "60";
            }
            if(word == "add") {
                ispis = "7";
                ispis += "0";

            }
            if(word == "sub"){
                ispis = "7";
                ispis += "1";
            }
            if(word == "mul"){
                ispis = "7";
                ispis += "2";
            }
            if(word == "div"){
                ispis = "7";
                ispis += "3";
            }
            if(word == "cmp"){
                ispis = "7";
                ispis += "4";
            }
            if(word == "and"){
                ispis = "8";
                ispis += "1";
            }
            if(word == "or"){
                ispis = "8";
                ispis += "2";
            }
            if(word == "xor"){
                ispis = "8";
                ispis += "3";
            }
            if(word == "test"){
                ispis = "8";
                ispis += "4";
            }
            if(word == "shl"){
                ispis = "9";
                ispis += "0";
            }
            if(word == "shr"){
                ispis = "9";
                ispis += "1";
            }

            locationCounter++;
            if(locationCounter % 10 == 0) ispis += "\n";
            else ispis += " ";
            
            ispis += destionation + source;
            locationCounter++;
            if(locationCounter % 10 == 0) ispis += "\n";
            else ispis += " ";
            izlazniFajl <<ispis;

            // locationCounter += 2;
        }

        if(word == "not"){
            int i;
            if(tekucaLinijaLabela) {
                i = 2;
            }else {
                i = 1;
            }
            string prvi = tokeniLinije->dohvati(i);
            int regD = dohvatiBrojRegistra(prvi);
            string ispis = "80";
            locationCounter++;
            if(locationCounter % 10 == 0) ispis += "\n";
            else ispis += " ";
            ispis += convertDecimalToHex(regD) + "0";

            locationCounter++;
            if(locationCounter % 10 == 0) ispis += "\n";
            else ispis += " ";
            izlazniFajl << ispis;
        }



        if(word == "call" || word == "jmp" || word == "jeq" || word == "jne" || word == "jgt"){
            int i;
            if(tekucaLinijaLabela) {
                i = 2;
            }else{
                i = 1;
            }
            string operand = tokeniLinije->dohvati(i);

            string literalBroj = "-?[0-9]+";
            string literalHex ="-?(0x)([a-fA-F0-9]+)";
            string reg = "r0|r1|r2|r3|r4|r5|r6|r7|sp|pc|psw";
            string simbolStr = "([a-z]|[A-Z])[a-z|A-Z|0-9|_]*";
            regex detektovanjeLiterala("\\*?(("+literalBroj+")|("+literalHex +"))");
            regex regDir("\\*(" + reg +")");
            regex regInd("\\*\\[(" + reg +")\\]");
            regex regIndPomPocetak("\\*\\[(" + reg +")");
            regex regIndPomKraj("(("+ literalBroj+")|("+literalHex+")|("+simbolStr+"))\\]");
            regex simbolOriginalReg(simbolStr);
            regex detektovanjeSimbola("(\\*|\\%)?("+simbolStr+")");
            
            string ispis;
            string broj;
            if(word == "call") {
                ispis = "30";
                locationCounter++;
                if(locationCounter % 10 == 0) ispis += "\n";
                else ispis += " ";
            }
            if(word == "jmp") {
                ispis = "50";
                locationCounter++;
                if(locationCounter % 10 == 0) ispis += "\n";
                else ispis += " ";
            }
            if(word == "jeq") {
                ispis = "51";
                locationCounter++;
                if(locationCounter % 10 == 0) ispis += "\n";
                else ispis += " ";
            }
            if(word == "jne") {
                ispis = "52";
                locationCounter++;
                if(locationCounter % 10 == 0) ispis += "\n";
                else ispis += " ";
            }
            if(word == "jgt") {
                ispis = "53";
                locationCounter++;
                if(locationCounter % 10 == 0) ispis += "\n";
                else ispis += " ";
            }

            ispis += "f";
            bool usao = false;
            if(regex_match(operand, detektovanjeLiterala)) {
                usao = true;
                // cout<<"USAO"<<endl;
                string adresiranje;
                if(operand[0] == '*'){
                    adresiranje = "4";
                    operand.erase(operand.begin());
                }else{
                    adresiranje = "0";
                }
                // cout<<operand<<endl;
                if(regex_match(operand, brojReg)){
                    int br = stoi(operand);
                    // cout<<br<<endl;
                    //adresa sa koje se cita ili sama adresa ne sme biti negativna
                    //65535 je 0xFFFF
                    if(br > 65535 || br < 0) {
                        detektovanaGreska = true;
                        cout<< "Greska na liniji " << brojLinije << " neposredna vrednost maks 2B" << endl;
                    }else {
                        // cout<<"VREDNOST "<< convertDecimalToHex(br) <<endl;
                        broj = convertDecimalToHex(br);
                    }
                    
                    
                }else{
                    //ako nije broj onda je heksa
                    if(regex_match(operand, heksaBrojreg)) {
                        if(operand[0] == '-'){
                            detektovanaGreska = true;
                            cout<< "Greska na liniji " << brojLinije << " ne sme negativna vrednost" << endl;
                        }else {
                            if(operand.length() > 6) {
                                detektovanaGreska = true;
                                cout<< "Greska na liniji " << brojLinije << " maksimalno 4 heksa cifre" << endl;
                            }
                        }
                        short br = convertHexToDecimal(operand);
                        // cout<< "hex to decimal  " << br << endl;
                        broj = convertDecimalToHex(br);
                        // cout<< broj<< endl;
                    }
                }//kraj elsa za heksa literale
                ispis += "0";
                locationCounter++;
                if(locationCounter % 10 == 0) ispis += "\n";
                else ispis += " ";
                ispis += "0";
                ispis += adresiranje;
                locationCounter++;
                if(locationCounter % 10 == 0) ispis += "\n";
                else ispis += " ";
                if(broj.length() == 1) {
                    ispis+= "00";
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis += "0"+broj;
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                }
                if(broj.length() == 2){
                    ispis += "00";
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis += broj;
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                }
                if(broj.length() == 3){
                    // cout<<"BROJ " <<broj[0]<<endl;
                    ispis += "0";
                    ispis += broj[0];
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis += broj[1];
                    ispis += broj[2];
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    // cout<<"ispis "<<ispis<<endl;
                }
                if(broj.length() == 4){
                    ispis += broj[0];
                    ispis += broj[1];
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis += broj[2];
                    ispis += broj[3];
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                }
                
                // locationCounter += 5;
                izlazniFajl <<ispis;

                
            }//kraj prepoznavanja literala

            // cout<<"OPERAND" << operand <<endl;
            if(!usao) {

            
                if(regex_match(operand, regDir)){
                    // cout<<"USAO"<<endl;
                    usao = true;
                    operand.erase(operand.begin());
                    int registar = dohvatiBrojRegistra(operand);

                    ispis += convertDecimalToHex(registar);
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis += "01";
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";

                    // locationCounter += 3;
                    izlazniFajl << ispis;
                }//kraj prepoznavanja regisarski direktnog
            }

            if(!usao) {

            
                if(regex_match(operand, regInd)){
                    usao = true;
                    operand.erase(0, 2);
                    operand.erase(operand.size()-1);

                    int registar = dohvatiBrojRegistra(operand);

                    ispis += convertDecimalToHex(registar);
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis += "02";
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";

                    // locationCounter += 3;
                    izlazniFajl<<ispis;
                }//kraj registarski indirektnog

            }

            if(!usao){

            

                if(regex_match(operand, regIndPomPocetak)){
                    usao = true;
                    operand.erase(0, 2);
                    int registar = dohvatiBrojRegistra(operand);
                    ispis += convertDecimalToHex(registar);
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis += "03";
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";

                    int i;
                    if(tekucaLinijaLabela){
                        i = 4;
                    }else{
                        i = 3;
                    }
                    string sledeci = tokeniLinije->dohvati(i);
                    // cout<<sledeci<<endl;
                    sledeci.erase(sledeci.size()-1);
                    string broj;
                    if(regex_match(sledeci, simbolOriginalReg)){
                        if(!tabelaSimbola->postojiSimbol(sledeci)) {
                            detektovanaGreska = true;
                            cout<<"Greska na liniji "<<brojLinije << " nedefinisani simbol"<<endl;
                        }else {

                            //posto je koriscen simbol mora da se napravi relokacioni zapis
                            Simbol *s = tabelaSimbola->dohvatiSekciju(sledeci);
                            //locationCounter+3 to je bilo 
                            Relocation *r = new Relocation(s->dohvatiRedniBr(), tekucaSekcija, "R_HYPO_16" ,locationCounter);
                            int br = s->dohvatiOfset();
                            if(s->dohvatiLokal() == 'l'){

                                br = s->dohvatiOfset();
                                r->postaviSimbol(s->dohvatiSekciju());
                            }else {
                                br = 0;
                            }

                            if(s->dohvatiSekciju() == 1) {
                                br = s->dohvatiOfset();
                                delete r;
                            }else {
                                tabelaRelokacija->dodaj(r);
                            }

                            
                            if(br > 65535 || br < 0) {
                                detektovanaGreska = true;
                                cout<< "Greska na liniji " << brojLinije << " neposredna vrednost maks 2B" << endl;
                            }else {
                                // cout<<"VREDNOST "<< convertDecimalToHex(br) <<endl;
                                broj = convertDecimalToHex(br);
                            }
                        }

                    }else{
                        
                        //ako nije simbol onda je literal
                        if(regex_match(sledeci, brojReg)){
                            int br = stoi(sledeci);
                            // cout<<br<<endl;
                            //adresa sa koje se cita ili sama adresa ne sme biti negativna
                            //65535 je 0xFFFF
                            if(br > 65535 || br < -32768) {
                                detektovanaGreska = true;
                                cout<< "Greska na liniji " << brojLinije << " neposredna vrednost maks 2B" << endl;
                            }else {
                                // cout<<"VREDNOST "<< convertDecimalToHex(br) <<endl;
                                broj = convertDecimalToHex(br);
                            }
                        
                            // cout<<"BROJ" << broj <<endl;
                        }else{
                            //ako nije broj onda je heksa
                            if(regex_match(sledeci, heksaBrojreg)) {
                                if(operand[0] == '-'){
                                    string proveri = "";
                                    proveri += sledeci[3];
                                    if(sledeci.length() > 7 || regex_match(proveri, proveraZaWordReg)) {
                                        if(sledeci != "-0x8000"){
                                            detektovanaGreska = true;
                                            cout<< "Greska na liniji " << brojLinije << " word je velicine 2B" << endl;
                                        }
                                    }
                                }else {
                                    if(operand.length() > 6) {
                                        detektovanaGreska = true;
                                        cout<< "Greska na liniji " << brojLinije << " word sa maksimalno 4 heksa cifre" << endl;
                                    }
                                }
                                short br = convertHexToDecimal(sledeci);
                                // cout<< "hex to decimal  " << br << endl;
                                broj = convertDecimalToHex(br);
                                // cout<< broj<< endl;
                            }
                        }

                        
                        // izlazniFajl << ispis;
                    
                        

                    }

                    // cout<<"BROJ"<<endl;
                        if(broj.length() == 1) {
                            ispis+= "00";
                            locationCounter++;
                            if(locationCounter % 10 == 0) ispis += "\n";
                            else ispis += " ";
                            ispis +=  "0"+broj;
                            locationCounter++;
                            if(locationCounter % 10 == 0) ispis += "\n";
                            else ispis += " ";
                        }
                        if(broj.length() == 2){
                            ispis += "00";
                            locationCounter++;
                            if(locationCounter % 10 == 0) ispis += "\n";
                            else ispis += " ";
                            ispis += broj;
                            locationCounter++;
                            if(locationCounter % 10 == 0) ispis += "\n";
                            else ispis += " ";
                        }
                        if(broj.length() == 3){
                            // cout<<"BROJ " <<broj[0]<<endl;
                            ispis += "0";
                            ispis += broj[0];
                            locationCounter++;
                            if(locationCounter % 10 == 0) ispis += "\n";
                            else ispis += " ";
                            ispis += broj[1];
                            ispis += broj[2];
                            locationCounter++;
                            if(locationCounter % 10 == 0) ispis += "\n";
                            else ispis += " ";
                            // cout<<"ispis "<<ispis<<endl;
                        }
                        if(broj.length() == 4){
                            ispis += broj[0];
                            ispis += broj[1];
                            locationCounter++;
                            if(locationCounter % 10 == 0) ispis += "\n";
                            else ispis += " ";
                            ispis += broj[2];
                            ispis += broj[3];
                            locationCounter++;
                            if(locationCounter % 10 == 0) ispis += "\n";
                            else ispis += " ";
                        }

                    // locationCounter += 5;
                    izlazniFajl << ispis;
                    
                }//kraj registarski indirektno sa pomerajem

            }

            if(!usao){

            
                if(regex_match(operand, detektovanjeSimbola)) {
                    usao = true;
                    string broj;

                    if(operand[0] == '*'){
                        operand.erase(operand.begin());
                        if(!tabelaSimbola->postojiSimbol(operand)) {
                            detektovanaGreska = true;
                            cout<<"Greska na liniji "<<brojLinije << " nedefinisani simbol"<<endl;
                        }else {

                            Simbol *s = tabelaSimbola->dohvatiSekciju(operand);
                            int vrednost;
                            //locationCounter+3 to je bilo 
                            ispis += "0";
                            locationCounter++;
                            if(locationCounter % 10 == 0) ispis += "\n";
                            else ispis += " ";
                            ispis +=   "04";
                            locationCounter++;
                            if(locationCounter % 10 == 0) ispis += "\n";
                            else ispis += " ";
                            
                            Relocation *r = new Relocation(s->dohvatiRedniBr(), tekucaSekcija, "R_HYPO_16", locationCounter);
                            if(s->dohvatiLokal() == 'l'){
                                vrednost = s->dohvatiOfset();
                                r->postaviSimbol(s->dohvatiSekciju());
                            }else { 
                                vrednost = 0;
                            }
                            if(s->dohvatiSekciju() == 1) {
                                vrednost = s->dohvatiOfset();
                                delete r;
                            }else {
                                tabelaRelokacija->dodaj(r);
                            }

                            broj = convertDecimalToHex(vrednost);

                            
                        }

                    }else{
                        if(operand[0] == '%'){

                            operand.erase(operand.begin());
                            if(!tabelaSimbola->postojiSimbol(operand)) {
                                detektovanaGreska = true;
                                cout<<"Greska na liniji "<<brojLinije << " nedefinisani simbol"<<endl;
                            }else {
                                ispis += "7";
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                                ispis +=  "05";
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                                Simbol *s = tabelaSimbola->dohvatiSekciju(operand);
                                int vrednost;
                                //locationCounter+3 to je bilo 
                                // cout <<"LC=" << locationCounter << endl;
                                Relocation *r = new Relocation(s->dohvatiRedniBr(), tekucaSekcija, "R_HYPO_PC16", locationCounter);
                                if(s->dohvatiSekciju() != 1) {
                                
                                    if(s->dohvatiLokal() == 'l'){
                                        // vrednost = s->dohvatiOfset();
                                        
                                        //labela - * - 2, labela predstavlja simbol na koji se skace,
                                        //* je trenutna vrednost lc, ovde uvecavamo tek na kraju pa zato ide ovako
                                        //-2 toliko zauzima payload 
                                        if(s->dohvatiSekciju() == tekucaSekcija){
                                            vrednost = s->dohvatiOfset() - (locationCounter /*+ 3*/) - 2;
                                            delete r;
                                        }else{
                                            vrednost = s->dohvatiOfset() - 2;
                                            r->postaviSimbol(s->dohvatiSekciju());
                                            tabelaRelokacija->dodaj(r);

                                        }
                                        
                                    }else { 
                                        if(s->dohvatiSekciju() == tekucaSekcija){
                                            vrednost = s->dohvatiOfset() - (locationCounter /*+ 3*/) - 2;
                                            delete r;
                                        }else{
                                            vrednost = -2;
                                            tabelaRelokacija->dodaj(r);
                                        }
                                        
                                    }
                                    
                                }else { // ako je simbol dodat sa equ
                                    // vrednost = s->dohvatiOfset();
                                    // delete r;
                                    //ako nije dobro onda ovo iznad
                                    vrednost = s->dohvatiOfset() - 2;
                                    r->postaviTipRelokacije("R_HYPO_PC_ABS_16");
                                    tabelaRelokacija->dodaj(r);
                                }
                                

                                broj = convertDecimalToHex(vrednost);

                                
                            }

                        }else {

                            if(!tabelaSimbola->postojiSimbol(operand)) {
                                detektovanaGreska = true;
                                cout<<"Greska na liniji "<<brojLinije << " nedefinisani simbol"<<endl;
                            }else {
                                ispis += "0";
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                                ispis += "00";
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";

                                Simbol *s = tabelaSimbola->dohvatiSekciju(operand);
                                int vrednost;
                                //locationCounter+3 to je bilo 
                                Relocation *r = new Relocation(s->dohvatiRedniBr(), tekucaSekcija, "R_HYPO_16", locationCounter);
                                if(s->dohvatiLokal() == 'l'){
                                    vrednost = s->dohvatiOfset();
                                    r->postaviSimbol(s->dohvatiSekciju());
                                }else { 
                                    vrednost = 0;
                                }
                                if(s->dohvatiSekciju() == 1) {
                                    vrednost = s->dohvatiOfset();
                                    delete r;
                                }else {
                                    tabelaRelokacija->dodaj(r);
                                }

                                broj = convertDecimalToHex(vrednost);

                                
                            }

                        }
                    }
                    

                    if(broj.length() == 1) {
                        ispis+= "00";
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        ispis += "0"+broj;
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                    }
                    if(broj.length() == 2){
                        ispis += "00";
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        ispis += broj;
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                    }
                    if(broj.length() == 3){
                        // cout<<"BROJ " <<broj[0]<<endl;
                        ispis += "0";
                        ispis += broj[0];
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        ispis += broj[1];
                        ispis += broj[2];
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        // cout<<"ispis "<<ispis<<endl;
                    }
                    if(broj.length() == 4){
                        ispis += broj[0];
                        ispis += broj[1];
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        ispis += broj[2];
                        ispis += broj[3];
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                    }
                    // locationCounter += 5;
                    izlazniFajl << ispis;
                    
                
                }//kraj prepoznavanja simbola

            }
            
        


        }//kraj za call, jmp itd


        if(word == "ldr" || word == "str"){
            int i;
            if(tekucaLinijaLabela){
                i = 2;
            }else {
                i = 1;
            }
            string registar = tokeniLinije->dohvati(i);
            registar.erase(registar.size()-1);
            int brojRegistra = dohvatiBrojRegistra(registar);

            // cout << "BROJ" <<brojReg<<endl;
            if(tekucaLinijaLabela){
                i = 3;
            }else {
                i = 2;
            }
            string operand = tokeniLinije->dohvati(i);


            string reg = "r0|r1|r2|r3|r4|r5|r6|r7|sp|pc|psw";
            string literalBroj = "-?[0-9]+";
            string literalHex ="-?(0x)([a-fA-F0-9]+)";
            string simbolStr = "([a-z]|[A-Z])[a-z|A-Z|0-9|_]*";

            regex detektovanjeLiteralaPodatak("\\$?(("+literalBroj+")|("+literalHex +"))");
            regex regDirPodatak("(" + reg +")");
            regex regIndPodatak("\\[(" + reg +")\\]");
            regex regIndPomPocetakPodatak("\\[(" + reg +")");
            regex detektovanjeSimbolaPodatak("(\\$|\\%)?("+simbolStr+")");

            //to znaci ldr
            string ispis;
            if(word == "ldr"){
                ispis  = "a0";
            }
            if(word == "str"){
                ispis  = "b0";
            }
            locationCounter++;
            if(locationCounter % 10 == 0) ispis += "\n";
            else ispis += " ";
            //regD
            ispis += convertDecimalToHex(brojRegistra);

            bool usao = false;


            if(regex_match(operand, detektovanjeLiteralaPodatak)) {
                //regS UP
                usao =true;
                ispis += "0";
                locationCounter++;
                if(locationCounter % 10 == 0) ispis += "\n";
                else ispis += " ";
                ispis +=  "0";

                //nacin adresiranja
                if(operand[0] == '$'){
                    operand.erase(operand.begin());
                    ispis += "0";
                }else {
                    ispis += "4";
                }
                locationCounter++;
                if(locationCounter % 10 == 0) ispis += "\n";
                else ispis += " ";
                string broj;
                if(regex_match(operand, brojReg)){
                    int br = stoi(operand);

                    // cout << br << "DASDA" << endl;
                    if(br > 65535 || br < -32768) {
                        detektovanaGreska = true;
                        cout<< "Greska na liniji " << brojLinije << " word je velicine 2B" << endl;
                    }else {
                        // cout<<"VREDNOST "<< convertDecimalToHex(br) <<endl;
                        broj = convertDecimalToHex(br);
                    }
                    
                }

                if(regex_match(operand, heksaBrojreg)) {
                    if(operand[0] == '-'){
                        string proveri = "";
                        proveri += operand[3];
                        if(operand.length() > 7 || regex_match(proveri, proveraZaWordReg)) {
                            if(operand != "-0x8000"){
                                detektovanaGreska = true;
                                cout<< "Greska na liniji " << brojLinije << " word je velicine 2B" << endl;
                            }
                        }
                    }else {
                        if(operand.length() > 6) {
                            detektovanaGreska = true;
                            cout<< "Greska na liniji " << brojLinije << " word sa maksimalno 4 heksa cifre" << endl;
                        }
                    }
                    short br = convertHexToDecimal(operand);
                    // cout<< "hex to decimal  " << br << endl;
                    broj = convertDecimalToHex(br);
                    // cout<< broj<< endl;
                }

                if(broj.length() == 1) {
                    ispis+= "00";
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis +=  "0"+broj;
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                }
                if(broj.length() == 2){
                    ispis += "00";
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis += broj;
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                }
                if(broj.length() == 3){
                    // cout<<"BROJ " <<broj[0]<<endl;
                    ispis += "0";
                    ispis += broj[0];
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis += broj[1];
                    ispis += broj[2];
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    // cout<<"ispis "<<ispis<<endl;
                }
                if(broj.length() == 4){
                    ispis += broj[0];
                    ispis += broj[1];
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis += broj[2];
                    ispis += broj[3];
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                }

                // locationCounter += 5;
                izlazniFajl << ispis;



            }//zavrseno prepoznavanje literala

            if(!usao) {
                if(regex_match(operand, regDirPodatak)){
                    usao = true;
                    // operand.erase(operand.size()-1);
                    // operand.erase(operand.begin());
                    int br = dohvatiBrojRegistra(operand);
                    string broj = convertDecimalToHex(br);

                    ispis += broj;
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis += "01";
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";

                    // locationCounter += 3;
                    izlazniFajl << ispis;
                }//zavrseno registarski direktno

            }
            if(!usao){
                if(regex_match(operand, regIndPodatak)){
                    usao = true;
                    operand.erase(operand.size()-1);
                    operand.erase(operand.begin());
                    int br = dohvatiBrojRegistra(operand);
                    string broj = convertDecimalToHex(br);

                    ispis += broj;
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis += "02";
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";

                    // locationCounter += 3;
                    izlazniFajl << ispis;
                }//kraj reg indirektnog
            }

            if(!usao) {

            
                if(regex_match(operand, regIndPomPocetakPodatak)){
                    usao = true;
                    operand.erase(operand.begin());
                    int brRegistra = dohvatiBrojRegistra(operand);
                    ispis += convertDecimalToHex(brRegistra);
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";
                    ispis += "03";
                    locationCounter++;
                    if(locationCounter % 10 == 0) ispis += "\n";
                    else ispis += " ";

                    int i;
                    if(tekucaLinijaLabela) {
                        i = 5;
                    }else {
                        i = 4;
                    }

                    string sledeci = tokeniLinije->dohvati(i);
                    sledeci.erase(sledeci.size()-1);

                    string broj;
                    if(regex_match(sledeci, brojReg)){
                        int br = stoi(sledeci);

                        // cout << br << "DASDA" << endl;
                        if(br > 65535 || br < -32768) {
                            detektovanaGreska = true;
                            cout<< "Greska na liniji " << brojLinije << " pomeraj maks na 2B" << endl;
                        }else {
                            // cout<<"VREDNOST "<< convertDecimalToHex(br) <<endl;
                            broj = convertDecimalToHex(br);
                        }
                        
                    } // prepoznavanje broja kraj
                    if(regex_match(sledeci, heksaBrojreg)) {
                        if(sledeci[0] == '-'){
                            string proveri = "";
                            proveri += sledeci[3];
                            if(sledeci.length() > 7 || regex_match(proveri, proveraZaWordReg)) {
                                if(sledeci != "-0x8000"){
                                    detektovanaGreska = true;
                                    cout<< "Greska na liniji " << brojLinije << " pomeraj maks na 2B" << endl;
                                }
                            }
                        }else {
                            if(sledeci.length() > 6) {
                                detektovanaGreska = true;
                                cout<< "Greska na liniji " << brojLinije << " pomeraj sa maksimalno 4 heksa cifre" << endl;
                            }
                        }
                        short br = convertHexToDecimal(sledeci);
                        // cout<< "hex to decimal  " << br << endl;
                        broj = convertDecimalToHex(br);
                        // cout<< broj<< endl;
                    }
                    if(regex_match(sledeci, simbolReg)){
                        if(tabelaSimbola->postojiSimbol(sledeci)){
                            Simbol *s = tabelaSimbola->dohvatiSekciju(sledeci);
                            int vrednost;
                            //locationCounter+3 to je bilo 
                            Relocation *r = new Relocation(s->dohvatiRedniBr(), tekucaSekcija, "R_HYPO_16", locationCounter);
                            if(s->dohvatiLokal() == 'l'){
                                vrednost = s->dohvatiOfset();
                                r->postaviSimbol(s->dohvatiSekciju());
                            }else{
                                vrednost = 0;
                            }
                            if(s->dohvatiSekciju() == 1) {
                                vrednost = s->dohvatiOfset();
                                delete r;
                            }else {
                                tabelaRelokacija->dodaj(r);
                            }
                            broj = convertDecimalToHex(vrednost);
                        }else {
                            broj = "0";
                            detektovanaGreska = true;
                            cout<<"Greska na liniji " << brojLinije << " simbol nije definisan"<<endl;
                        }
                        
                    }//kraj prepoznavanja simbola


                    if(broj.length() == 1) {
                        ispis+= "00";
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        ispis +=  "0"+broj;
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                    }
                    if(broj.length() == 2){
                        ispis += "00";
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        ispis += broj;
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                    }
                    if(broj.length() == 3){
                        // cout<<"BROJ " <<broj[0]<<endl;
                        ispis += "0";
                        ispis += broj[0];
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        ispis += broj[1];
                        ispis += broj[2];
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        // cout<<"ispis "<<ispis<<endl;
                    }
                    if(broj.length() == 4){
                        ispis += broj[0];
                        ispis += broj[1];
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        ispis += broj[2];
                        ispis += broj[3];
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                    }

                    // locationCounter += 5;
                    izlazniFajl<< ispis;
                
                }//kraj reg ind pom

            }
            if(!usao) {

            
                if(regex_match(operand, detektovanjeSimbolaPodatak)) {
                    usao = true;
                    string broj;
                    if(operand[0] == '$'){
                        operand.erase(operand.begin());
                        if(tabelaSimbola->postojiSimbol(operand)){

                            ispis += "0";
                            locationCounter++;
                            if(locationCounter % 10 == 0) ispis += "\n";
                            else ispis += " ";
                            ispis += "00";
                            locationCounter++;
                            if(locationCounter % 10 == 0) ispis += "\n";
                            else ispis += " ";
                            Simbol *s = tabelaSimbola->dohvatiSekciju(operand);
                            //locationCounter+3 to je bilo 
                            Relocation *r = new Relocation(s->dohvatiRedniBr(), tekucaSekcija, "R_HYPO_16", locationCounter);
                            int vrednost;
                            if(s->dohvatiLokal() == 'l'){
                                vrednost = s->dohvatiOfset();
                                r->postaviSimbol(s->dohvatiSekciju());
                            }else {
                                vrednost = 0;
                            }
                            if(s->dohvatiSekciju() == 1) {
                                vrednost = s->dohvatiOfset();
                                delete r;
                            }else {
                                tabelaRelokacija->dodaj(r);
                            }
                            broj = convertDecimalToHex(vrednost);

                        }else {
                            broj = "0";
                            detektovanaGreska = true;
                            cout<<"Greska na liniji " << brojLinije << " simbol nije definisan"<<endl;
                        }



                    }else {
                        if(operand[0] == '%'){
                            operand.erase(operand.begin());
                            if(tabelaSimbola->postojiSimbol(operand)) {
                                ispis += "7";
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                                ispis +=  "03";
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                                Simbol *s = tabelaSimbola->dohvatiSekciju(operand);
                                //locationCounter+3 to je bilo 
                                Relocation *r = new Relocation(s->dohvatiRedniBr(), tekucaSekcija, "R_HYPO_PC16", locationCounter);
                                int vrednost;
                                if(s->dohvatiSekciju() != 1){
                                    if(s->dohvatiLokal() == 'l'){
                                        if(s->dohvatiSekciju() == tekucaSekcija) {
                                            vrednost = s->dohvatiOfset() - (locationCounter /*+ 3*/) - 2;
                                        }else{
                                            vrednost = s->dohvatiOfset() - 2;
                                            r->postaviSimbol(s->dohvatiSekciju());
                                            tabelaRelokacija->dodaj(r);
                                        }
                                        
                                    }else {//globalni
                                        if(s->dohvatiSekciju() == tekucaSekcija) {
                                            vrednost = s->dohvatiOfset() - (locationCounter /*+ 3*/) - 2;
                                        }else{
                                            vrednost = -2;
                                            tabelaRelokacija->dodaj(r);
                                            
                                        }
                                        
                                    }
                                }else {//znaci da je dodat sa equ
                                    vrednost = s->dohvatiOfset() - 2;
                                    r->postaviTipRelokacije("R_HYPO_PC_ABS_16");
                                    tabelaRelokacija->dodaj(r);
                                }
                                
                                broj = convertDecimalToHex(vrednost);

                            }else {
                                broj = "0";
                                detektovanaGreska = true;
                                cout<<"Greska na liniji " << brojLinije << " simbol nije definisan"<<endl;
                            }

                        }else { // ovde memorijsko simbol
                            if(tabelaSimbola->postojiSimbol(operand)) {

                                ispis += "0";
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                                ispis +=  "04";
                                locationCounter++;
                                if(locationCounter % 10 == 0) ispis += "\n";
                                else ispis += " ";
                                Simbol *s = tabelaSimbola->dohvatiSekciju(operand);
                                //locationCounter+3 to je bilo 
                                Relocation *r = new Relocation(s->dohvatiRedniBr(), tekucaSekcija, "R_HYPO_16", locationCounter);
                                int vrednost;
                                if(s->dohvatiLokal() == 'l'){
                                    vrednost = s->dohvatiOfset();
                                    r->postaviSimbol(s->dohvatiSekciju());
                                }else {
                                    vrednost = 0;
                                }
                                if(s->dohvatiSekciju() == 1) {
                                    vrednost = s->dohvatiOfset();
                                    delete r;
                                }else {
                                    tabelaRelokacija->dodaj(r);
                                }
                                broj = convertDecimalToHex(vrednost);

                            }else {
                                broj = "0";
                                detektovanaGreska = true;
                                cout<<"Greska na liniji " << brojLinije << " simbol nije definisan"<<endl;
                            }

                        }
                    }

                    if(broj.length() == 1) {
                        ispis+= "00";
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        ispis +=  "0"+broj;
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                    }
                    if(broj.length() == 2){
                        ispis += "00";
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        ispis += broj;
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                    }
                    if(broj.length() == 3){
                        // cout<<"BROJ " <<broj[0]<<endl;
                        ispis += "0";
                        ispis += broj[0];
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        ispis += broj[1];
                        ispis += broj[2];
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        // cout<<"ispis "<<ispis<<endl;
                    }
                    if(broj.length() == 4){
                        ispis += broj[0];
                        ispis += broj[1];
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                        ispis += broj[2];
                        ispis += broj[3];
                        locationCounter++;
                        if(locationCounter % 10 == 0) ispis += "\n";
                        else ispis += " ";
                    }

                    // locationCounter += 5;
                    izlazniFajl<< ispis;

                }//kraj detektovanja simbola
            }



        }//zavrseno ldr i str


        if(word == "push" || word == "pop") {
            int i;
            if(tekucaLinijaLabela) {
                i = 2;
            }else {
                i = 1;
            }

            string regDest = tokeniLinije->dohvati(i);
            int brojRegDest = dohvatiBrojRegistra(regDest);
            string hexBroj = convertDecimalToHex(brojRegDest);
            string ispis;
            if(word == "push"){
                ispis = "b0";
            }
            if(word == "pop"){
                ispis = "a0";
            }
            locationCounter++;
            if(locationCounter % 10 == 0) ispis += "\n";
            else ispis += " ";
            ispis += hexBroj;
            ispis += "6"; //soruce registar, sp
            locationCounter++;
            if(locationCounter % 10 == 0) ispis += "\n";
            else ispis += " ";
            if(word == "push"){
                ispis += "12"; 
            }
            if(word == "pop"){
                ispis += "42";
            }
            locationCounter++;
            if(locationCounter % 10 == 0) ispis += "\n";
            else ispis += " ";
            // locationCounter += 3;
            izlazniFajl << ispis;


        }
        

        




        //kraj komentara je na kraju reda
        komentar = false;
        //brisemo listu jer krecemo u obradu novog reda
        delete tokeniLinije;
        tokeniLinije = new Lista();
        brojLinije++;
    }
    // if(!detektovanaGreska){
    //     prikazTabeleRelokacija(tabelaRelokacija);
    // }
    
    //zatvaramo sam ulazni fajl
    ulazniFajl1.close();
    izlazniFajl.close();
    // cout << imeIzlaznogFajla << ":" << imeUlaznogFajla << endl;

    return 1;
}




