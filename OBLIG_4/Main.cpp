/**
 * program som holder orden på oppdrag/boliger til salgs i ulike soner i en
 * by/et geografisk område, samt potensielle kunder/kjøpere som har interresse
 * for boliger i en eller flere av disse sonene.
 * 
 * I hovedsak skal programmet kunne:
 * - Legge inn / skrive / slette / endre - kunder/kjøpere
 * - Legge inn / skrive                  - soner    
 * - Legge inn / skrive / slette         - oppdrag/boliger 
 * - Skrive (til fil) oversikt over alle aktuelle boliger for en gitt kunde
 * - Hele datastrukturen skal kunne skrives til fil og leses fra fil
 * 
 * @file Main.cpp
 * Program: @author Sverre Mæhlum
 * main fil: @author Frode Haug, NTNU
 * 
 */

#include <iostream>
#include "Kunder.h"
#include "Soner.h"
#include "Global.h"           //"<filen med 'skrivMeny()' på>"
using namespace std;

Kunder gKundebase;         ///<  Globalt container-objekt med ALLE kundene.
Soner gSonebase;           ///<  Globalt container-objekt med ALLE sonene.
 
//  Kode som legges innledningsvis i de .cpp-filene som trenger å bruke
//  en eller begge de to globale objektene definert ovenfor:
//         extern Kunder gKundebase;
//         extern Soner gSonebase;
 
 
/**
 *  Hovedprogram.
 */
int main()  {

    // leser inn data både for kunder og soner
    gKundebase.lesFraFil();
    gSonebase.lesFraFil();

    // vector med opptil tre objekter av "Kommando"
    vector <Kommando> kommandoer;

    skrivMeny();
    do {
        kommandoer = lesKommando(); // leser inn kommando linje fra bruker
        if (kommandoer[0].erInt == false) {
            switch (kommandoer[0].c) {
                case 'K':           gKundebase.handling(kommandoer);      break;
                case 'S': case 'O': gSonebase.handling(kommandoer);       break;
                case 'Q':           cout<<"Avslutter programmet" << endl; break;
                default:            cout<<"Ukjent kommando" << endl;      break;
            }
        }else {
            cout << "Ukjent kommando" << endl;
        }
    }while (kommandoer[0].c != 'Q');

    // skriver kunde og sone data til hver sin fil
    gKundebase.skrivTilFil();
    gSonebase.skrivTilFil();

    cout << "\n\n";
    return 0;
}