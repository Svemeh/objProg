/**
 * Oblig 1 i objektorientert programmering
 *  programet skal kunne registrere en ny oppgave 
 * Oppgaven skal ha en beskrivelse, en ansvarlig person, og en bool "ErFullført"
 * 
 * programmet skal kunne oppdatere "ErFullført" boolen, gjennom oppage nr
 * 
 * programmet skal kunne skrive ut alle registrerte oppgaver
 * 
 * programmet skal kunne slette alle oppgaver, da programmet avsluttes
 * 
 * @file OBLIG_1.cpp
 * @author Sverre Mæhlum
 */


#include <iostream>			// cout, cin
#include <iomanip>			// setw
#include <string>			// string
#include <vector>			// vector
#include "LesData2.h"		// LesData
using namespace std;

struct Oppgave {
    string beskrivelse, // Hva oppgaven er 
    ansvarlig;          // Hvem som skal gjøre den.
    bool erFulfort;          // Om oppgaven er gjort eller ei.
};

vector <Oppgave*> gOppgaver;

void fjernAlleOppgaver();
void nyOppgave();
void oppgaveEndreStatus();
void oppgaveEndreStatus(Oppgave & oppgave);
void oppgaveLesData(Oppgave & oppgave);
void oppgaveSkrivData(const Oppgave* oppgave);
void skrivAlleOppgaver();
void skrivMeny();

/**
 *  Hovedprogrammet:
 */
int main()  {
    char kommando;

    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q') {
        switch (kommando) {
           case 'N': nyOppgave();               break;
           case 'S': skrivAlleOppgaver();       break;
           case 'E': oppgaveEndreStatus();      break;
           default:  skrivMeny();               break; 
        }
        kommando = lesChar("\nKommando");
    }

    fjernAlleOppgaver();

    return 0;
}

void nyOppgave() {
    Oppgave* nyOppgave = new Oppgave;         //  Oppretter en ny Oppgave-struct.
    cout << "\nNy oppgave:\n";
    oppgaveLesData(*nyOppgave);           //  Alle dens data leses inn.
    gOppgaver.push_back(nyOppgave);     //  Legges bakerst i vectoren.
    cout << "\n\tNy oppgave innlagt har nr." << gOppgaver.size() << '\n';
}

/**
 *  Leser inn og fyller ALLE en oppgave sine datamedlemmer.
 *
 *  @param   oppgave  - Structen som f�r sine datamedlemmer innlest/fylt
 */
void oppgaveLesData(Oppgave & oppgave) {
    cout << "\tOppgave beskrivelse:     ";    getline(cin, oppgave.beskrivelse);
    cout << "\tAnsvarlig for å gjennomføre:  ";getline(cin, oppgave.ansvarlig);
    oppgave.erFulfort = false;
}

/**
 *  Skriver programmets menyvalg/muligheter p� skjermen.
 */
void skrivMeny() {
    cout << "\nFolgende kommandoer er tilgjengelig:\n"
         << "\tN - Ny oppgave\n"
         << "\tS - Skriv alle oppgavene ut på skjermen\n"
         << "\tE - Oppdater status på en oppgave til fullført\n"
         << "\tQ - Quit / avslutt\n";
}

/**
 *  Overloaded funksjon som skriver alle Oppgavene vha PEKER.
 *
 *  @see   oppgaveSkrivData(const Oppgave* oppgave)
 */
void skrivAlleOppgaver() {
    for (int i = 0;  i < gOppgaver.size();  i++) {
        cout << "\tOppgave nr." << setw(2) << i+1 << ":\n";
        oppgaveSkrivData(gOppgaver[i]);
    }
}

/**
 *  Overloaded funksjon som skriver structdata (struct-variabel som paramtr).
 *
 *  @param   oppgave  - Struct-VARIABEL hvis data utskrives p� skjermen
 */
void oppgaveSkrivData(const Oppgave* oppgave)  {
    cout << "\t\t\"" << oppgave->beskrivelse << "\" Ansvarlig: " << oppgave->ansvarlig
         << ((!oppgave->erFulfort) ? "\tIKKE " : "\t") << "Fullført\n";
 }

 /**
 *  �nsket oppgave.nr markeres som fullført.
 *
 *  @see   oppgaveEndreStatus(...)
 */
void oppgaveEndreStatus() {
    oppgaveEndreStatus(*gOppgaver[lesInt("\fullført oppgave nr", 1,
         gOppgaver.size())-1]);
}

/**
 *  Setter en oppgave som fullført.
 *
 *  @param   oppgave  - Structen som f�r 'ErFullfort' satt til 'true'
 */
void oppgaveEndreStatus(Oppgave & oppgave) {
    if (!oppgave.erFulfort) {
        cout << "\n\tOppgaven er markert/satt som 'Fullført'.\n";
        oppgave.erFulfort = true;
    }else{
        cout << "\n\tOppgaven er markert/satt som 'Ikke fullført'.\n";
        oppgave.erFulfort = false;
    }
}

/**
 *  Sletter/fjerner ALLE tilpekte structer (Bok), og alle pekerne i vectoren.
 */
void fjernAlleOppgaver() {
    //  EN m�te (av mange) � fjerne ALT i vectoren:
while (!gOppgaver.empty()) {              //  S� lenge PEKERE i vectoren:
delete gOppgaver[gOppgaver.size()-1];   //  Sletter den SISTE TILPEKTE.
gOppgaver.pop_back();                 //  Sletter/fjerner SELVE PEKEREN.
}
    cout << "\n\nvectoren er tom - antallet er: " << gOppgaver.size() << "\n\n";
}