// Kunder.cpp
#include "Kunder.h"    // Header for Kunder
#include <fstream>     // filestream
#include <iostream>    // cin, cout

#include "Global.h"    // vector<kommandoer>
#include "Consts.h"    // KUNDER_FIL

using namespace std;


/**
 * void endreEnKunde(...)
 *
 * Funksjon lar bruker endre hvilke soner en kunde er interessert i
 * @param knr   // kunde nummer til kunden som skal endres
 * @see hentKunde(...)
 * @see Kunde::endreKunde()
 */
void Kunder::endreEnKunde(int knr) {
    Kunde* valgtKunde = hentKunde(knr);
    if (valgtKunde) {
        valgtKunde->endreKunde();
    }
}


/**
 * void enKundeSkrivTilFil(...)
 *
 * funksjonen skal skrive en detaljert beskrivelse av kunden
 * og hvilke soner / boliger som kan potensielt være interessante for kunden
 * @param knr // kunde nummer
 * @see hentKunde(...)
 * @see Kunde::skrivTilFinFil(...)
 */
void Kunder::enKundeSkrivTilFil(int knr) {
    Kunde* valgtKunde = hentKunde(knr);
    if (valgtKunde) {

        string filNavn;

        // bygger navn på fila
        filNavn = "K";
        filNavn.append(to_string(knr));
        filNavn.append(".dta");

        // lager/åpner fil med korrekt navn til utskriving
        ofstream utfil(filNavn);

        if (utfil) {
            utfil << "Kunde nummer: " << knr << endl;

            valgtKunde->skrivTilFinFil(utfil);

            cout << "\tSkrevet ut fil med navn: " << filNavn << endl;
        }else {
            cerr << "klarte ikke åpne fil Kxxxx.dta til skriving" << endl;
        }
    }
}


/**
 * void handling(...)
 *
 * funksjoner håndterer alle "underkommandoene" i kunde menyen
 *
 * @param kommandoer // vector som inneholder alle kommandoene brukeren tastet 
 * @see hentKunde(...)
 * @see Kunde::skrivAltOmKundeTilSkjerm()
 * @see nyKunde()
 * @see skrivAlleKunderTilSkjerm()
 * @see endreEnKunde(...)
 * @see slettKunde()
 * @see enKundeSkrivTilFil(...)
 */
void Kunder::handling(vector<Kommando> kommandoer) {
    if (kommandoer[1].erInt == true && kommandoer[1].i == 1 
            && kommandoer[2].erInt == true) {
        Kunde* valgtKunde = hentKunde(kommandoer[2].i);
        if (valgtKunde) {
            valgtKunde->skrivAltOmKundeTilSkjerm();
        }
    }else{
        switch (kommandoer[1].c) {
            case 'N': nyKunde(); break;
            case 'A': skrivAlleKunderTilSkjerm(); break;
            case 'E':
                if (kommandoer[2].erInt) {
                    endreEnKunde(kommandoer[2].i);
                }else{cerr << "Uglyldig kommando: <knr> må være int" << endl;}
                    break;
            case 'S': slettKunde(kommandoer[2].i); break;
            case 'O':
                if (kommandoer[2].erInt) {
                    enKundeSkrivTilFil(kommandoer[2].i);
                }else{cerr << "Uglyldig kommando: <knr> må være int" << endl;}
                break;
            default: cerr << "Ugyldig kommando" << endl;
        }
    }
}


/**
 * void lesFraFil()
 *
 * leser inn all data fra "Kunder.dta" fil
 * @see Kunde::lesFraFil(...)
 */
void Kunder::lesFraFil() {

    ifstream innfil(KUNDER_FIL);

    if (innfil) {   // hvis filen ble åpnet
        innfil >> sisteKundeNr; // leser inn sisteKundeNr
        innfil.ignore(numeric_limits<streamsize>::max(), '\n'); // dropper linje

        int nr;
        while (innfil >> nr) {
            Kunde* nyKunde = new Kunde(innfil, nr);
            gKunder.push_back(nyKunde);
            cout << "Ny kunde opprettet og lagt inn med nr " << nr << endl;
        }
        // Lukker fil
        innfil.close();
    } else {    // hvis filen ikke ble åpnet
        cerr << "klarte ikke åpne" << KUNDER_FIL << endl;

    }
}


/**
 * void nyKunde()
 *
 * funksjon legger til en ny kunde
 * @see Kunde::lesFraBruker()
 */
void Kunder::nyKunde() {
    cout << "Registrering av ny kunde:" << endl;
    Kunde* nyKunde = new Kunde(++sisteKundeNr);
    gKunder.push_back(nyKunde);

    hentKunde(sisteKundeNr)->skrivAltOmKundeTilSkjerm();
    cout << "Ny kunde opprettet og lagt inn som nr." << sisteKundeNr << endl 
         << endl;
}


/**
 * void skrivAlleKunderTilSkjerm()
 *
 * skriver en oppsumering av alle kunder til skjermen
 * oppsumering inneholder kunde nummer, navn, boligtype og soner
 * @see Kunde::skrivLittOmKundeTilSkjerm()
 */
void Kunder::skrivAlleKunderTilSkjerm() {
    int i = 0;
    for (auto kunde : gKunder) {
        i++;
        kunde->skrivLittOmKundeTilSkjerm();
        if (i >= ANTALLKUNDEUTSKRIFT) {  // venter på Enter
            cout << "trykk Enter for å fortsette";
            getchar();
            i = 0;
        }
    }
}


/**
 * void skrivTilFil()
 *
 * skriver all kunde data til "Kunder.dta"
 * @see Kunde::skrivTilFIl(...)
 */
void Kunder::skrivTilFil() {

    // åpner fil for skriving
    ofstream utfil(KUNDER_FIL);

    // skriver sisteKundeNr øverst på fila
    utfil << sisteKundeNr;

    // skriver alle kunder som ligger i gKunder listen
    for (Kunde* kunde : gKunder) {
        utfil << endl;
        kunde->skrivTilFil(utfil);
    }

    // luker filen igjen
    utfil.close();
}


/**
 * void slettKunde()
 *
 * funksjonen skal slette kunden med kundenummer knr
 *
 * @see hentKunde(...)
 * @param knr kunden som skal slettes
 */
void Kunder::slettKunde(int knr) {
    bool funnet = false;
    for (auto it = gKunder.begin(); it != gKunder.end(); ) {
        if ((*it)->hentKunde(knr)) {
            delete *it;
            it = gKunder.erase(it);
            cout << "Kunde med nr " << knr << " slettet" << endl;
            funnet = true;
            break; // eller return hvis du bare vil slette én kunde
        } else {
            ++it;
        }
    }
    if (!funnet) {
        cout << "Fant ingen kunde med nr " << knr << endl;
    }
}


/**
 * hentKunde(...)
 *
 * @param knr kunde nummer til kunden vi ser etter
 * @return kunden med riktig kundeNr
 */
Kunde* Kunder::hentKunde(int knr) {
    for (auto kunde : gKunder) {
        Kunde* valgtKunde = kunde->hentKunde(knr);
        if (valgtKunde) {
            return valgtKunde;
        }
    }
    cout << "Fant ingen kunde med nr " << knr << endl;
    return nullptr;
}


/**
 * ~KundeR()
 *
 * deconstructor for "Kunder" objekt, 
 * sletter alle registrerte kunder fra programmets minne
 */
Kunder::~Kunder() {
    for (auto kunde : gKunder) {delete kunde;}
    gKunder.clear();
}

