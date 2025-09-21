// Kunder.cpp
#include "Kunde.h"    // Header for Kunder 
#include <fstream>     // filestream
#include <iostream>    // cin, cout

#include "Soner.h"     // gSonebase
#include "LesData3.h"

using namespace std;
extern Soner gSonebase;


/**
 * Kunde(...)
 *
 * Constructor for Kunde objekt
 * funksjone leser inn all data om en Kunde fra Kunder.dta fil 
 * @param inn Kunder.dta fil som program leser inn data fra
 * @param knr kunde nummer allerede lest inn fra fil
 */
Kunde::Kunde(ifstream & inn, int knr) {

    kundeNr = knr;

    // leser inn telefon
    inn >> tlf;
    inn.ignore(numeric_limits<streamsize>::max(), '\n');    // dropper linjen

    // Leser inn navn
    getline(inn, navn);


    // Leser inn gateAddresse
    getline(inn, gateAddresse);

    // Leser inn postAddresse
    getline(inn, postAddresse);

    // Leser inn Email
    getline(inn, Email);

    // Leser inn bolig type
    string temp;
    inn >> temp;

    if (temp == "ENEBOLIG") {
        boligType = ENEBOLIG;
    }else if (temp == "BOLIG") {
        boligType = BOLIG;
    }else {
        cerr << "Ugyldig boligtype" << endl;
        boligType = ENEBOLIG;       // default til enebolig
    }

    // tømmer soner og leser inn soner
    soner.clear();
    int tempSone;

    //dersom neste tegn ikke er '\n' les inn tall
    while (inn.peek() != '\n' && inn >> tempSone) {
        soner.push_back(tempSone);  // legger tall til i soner vector
    }
    inn.ignore(numeric_limits<streamsize>::max(), '\n'); // dropper linjen
}


/**
 * Kunde(...)
 *
 * Construcotr for Kunde objekt
 * funksjone brukes da bruker vil manuelt legge til en ny Kunde
 * funksjone leser inn all dataen til Kunde
 * @param knr kunde nummert kunde blir registrert under
 * @see endreKunde()
 */
Kunde::Kunde(int knr) {

    // setter kundeNr
    kundeNr = knr;

    // leser inn navn på ny kunde
    do {
    cout << "\tNavn: ";
    getline(cin, navn);
    }while (navn.empty());

    // leser inn telefonnummer
    tlf = lesInt("\ttelefon", 10000000, 99999999);

    // leser inn gate addressen
    do {
        cout << "\tGateadresse: ";
        getline(cin, gateAddresse);
    }while (gateAddresse.empty());

    // leser inn post addressen
    do {
        cout << "\tPostadresse: ";
        getline(cin, postAddresse);
    }while (postAddresse.empty());

    // leser inn epost
    do {
        cout << "\tEpost: ";
        getline(cin, Email);
    }while (Email.empty());

    char c; // char brukes for å lese inn brukers input

    // leser inn boligtype
    do {
        c = lesChar("\tE(nebolig) eller B(olig)");
    }while (c != 'E' && c != 'B');
    if (c == 'E') {
        boligType = ENEBOLIG;
    }else {
        boligType = BOLIG;
    }

    // leser inn soner
    c = lesChar("Legge til soner (j/N)");
    if (c == 'J') {
        endreKunde();
    }
}


/**
 * endreKunde()
 *
 * funksjonen lar brukeren endre hvilke soner som er registrert i Kunde objekt
 * @see Kunde::skrivAltOmKundeTilSkjerm
 * @see Kunde::erSoneRegistrert(...)
 * @see Soner::sjekkOmSoneEksisterer(...)
 */
void Kunde::endreKunde() {
    skrivAltOmKundeTilSkjerm();

    int i;
    do {
        i = lesInt("Legg til / slett sone (0 avslutter)", 0, 100);
        if (i != 0) {
            if (gSonebase.sjekkOmSoneEksisterer(i)) {
                if (erSoneRegistrert(i)) { // sjekker om sonene allerde er der
                    // sletter sone
                    soner.erase(remove(soner.begin(), soner.end(), i),
                                                             soner.end());
                    cout << "Sone " << i << " slettet" << endl;
                }else {
                    // legger til sone
                    soner.push_back(i);
                    cout << "Sone " << i << " lagt til" << endl;
                }
            }else {
                cout << "Klarte ikke finne sone " << i << endl;
            }
        }else {
            // sorter vector soner
            stable_sort(soner.begin(), soner.end());
            cout << "Endringer lagret" << endl;
        }
    }while (i != 0);
}


/**
 * erSoneRegistrert(...)
 *
 * funksjoen sjekker om en sone er lagret i kunde objektet
 * @param snr sonene funksjonen ser etter
 * @return bool
 */
bool Kunde::erSoneRegistrert(int snr) {
    auto it = find(soner.begin(), soner.end(), snr);
    if (it != soner.end()) {
        return true;
    }else{
        return false;
    }
}


/**
 * skrivAltOmEnKundeTilSkjerm()
 *
 * funksjone skriver all dataen om en kunde til skjerm på en pen måte
 */
void Kunde::skrivAltOmKundeTilSkjerm() {
    cout << "\tNavn:\t\t\t" << navn << "\t\tTelefon:\t" << tlf << endl
         << "\tGateadresse:\t" << gateAddresse << endl
         << "\tPostadresse:\t" << postAddresse << endl
         << "\tEpost:\t\t\t" << Email << endl
         << "\tBoligtype:\t\t" << (boligType == ENEBOLIG ? "Enebolig":"Bolig");

    if (soner.size() != 0) {
        // skriver ut alle sonene registrert i kunde
        cout << "\t\t\t\ti sonen(e):\t";
        for (int i : soner) {
            cout << " " << i;
        }
    }else {
        cout << "\t\t\t\tIngen soner registrert.";
    }
    cout << endl << endl;;
}


/**
 * skrivLittOmKundeTilSkjerm()
 *
 * funksjonen skirver en oppsumering av kundens dataer til skjerm
 */
void Kunde::skrivLittOmKundeTilSkjerm() {
    cout << "\t" << kundeNr << " - " << navn << "\t\t" <<
        (boligType == ENEBOLIG ? "Enebolig" : "Bolig") << endl
         << "\t\tInteressert i " << soner.size() << " soner:\t";

    // skriver ut alle sonene registrert i kunde
    for (int i : soner) {
        cout << " " << i;
    }
    cout << endl << endl;
}


/**
 * skrivTilFil(...)
 *
 * funksjone skriver ut all data om en kunde til fil Soner.dta
 * @param ut filen data om kunde skrives til
 */
void const Kunde::skrivTilFil(ofstream & ut) {
    ut << kundeNr << " " << tlf  << endl
       << navn << endl
       << gateAddresse << endl
       << postAddresse << endl
       << Email << endl
       <<  (boligType == ENEBOLIG ? "ENEBOLIG" : "BOLIG");

    // skriver ut alle sonene registrert i kunde
    for (int i : soner) {
        ut << " " << i;
    }
}


/**
 * skrivTilFinFil(...)
 *
 * denne funksjone skriver ut soner kunden er interessert i
 * og boliger som er relevant for kunden
 * @param ut filen data skrives ut til
 * @see Soner::skrivRelevanteBoligerTilFil(...)
 */
void Kunde::skrivTilFinFil(ofstream & ut) {
    for (int sone : soner) {
        ut << endl << "Sone " << sone << ":" << endl
                << "========" << endl;
        gSonebase.skrivRelevanteBoligerTilFil(ut, sone, boligType);
    }
}


/**
 * hentKunde(...)
 *
 * funksjone brukes for å finne en spesfik kunde, denne funksjonen kalles
 * fra hentKunde funksjonen i Kunder klassen
 * @param knr kunde nummert vi ser etter
 * @return Kunde* / Nullptr
 */
Kunde* Kunde::hentKunde(int knr) {
    if (kundeNr == knr) {
        return this;
    }else {
        return nullptr;
    }
}


/**
 * Deconstructor for Kunde objekt
 */
Kunde::~Kunde() {
}


