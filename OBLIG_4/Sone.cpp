// Sone.cpp
#include "Sone.h"    // Header for Kunder 
#include <fstream>   // filestream
#include <iostream>

#include "Bolig.h"
#include "Consts.h"

using namespace std;

/**
 * Sone(..)
 *
 * Funksjonen leser inn all dataen til en sone fra en fil
 * @param inn ifstream fil Soner.dta
 * @see Bolig::lesInnBoligFraFil(...)
 */
Sone::Sone(ifstream & inn) {
    // leser inn sonens beskrivelse
    getline(inn, beskrivelse);

    // leser inn antall boliger i sonen
    inn >> antallBoliger;
    inn.ignore(numeric_limits<streamsize>::max(), '\n'); // dropper linje

    // leser inn riktig antall boliger
    for (int i = 0; i < antallBoliger; i++) {
        Bolig* nyBolig = Bolig::lesInnBoligFraFil(inn);
        gBoliger.push_back(nyBolig);
    }
}


/**
 * Sone()
 *
 * constructor for Sone objekt, leser inn beskrivelsen til Sone
 */
Sone::Sone() {
    cout << "\tBeskrivelse: ";
    getline(cin, beskrivelse);
}


/**
 * nyBolig(...)
 *
 * funksjonen lager et nytt bolig bojekt ved hjelp av en funksjon i Bolig klasse
 * @param onr oppdragsNummert til nye boligen
 * @see lesInnBoligFraBruker(...) hjelpe funksjon til å lage nye boliger
 */
void Sone::nyBolig(int onr) {
    Bolig* nyBolig = Bolig::lesInnBoligFraBruker(onr);
    gBoliger.push_back(nyBolig);
    antallBoliger++;
}


/**
 * skrivAltOmSoneTilSkjerm()
 *
 * funksjoen skriver all dataen om sonen til skjerm
 * @see Bolig::skrivTilSkjerm()
 */
void Sone::skrivAltOmSoneTilSkjerm() {
    cout << " - " << beskrivelse << endl;
    if (antallBoliger == 0) {
        cout << "\tIngen boliger registrert her." << endl;
    }else {
        cout << "\tBoliger:" << endl;
        int i = 0;
        for (auto const & bolig : gBoliger) {
            bolig->skrivTilSkjerm();
            i++;

            if (i >= ANTALLBOLIGUTSKRIFT) {  // venter på Enter
                cout << "trykk Enter for å fortsette";
                getchar();
                i = 0;
            }
        }
    }
}


/**
 * skrivLittOmSoneTilSkjerm()
 *
 * skriver en oppsumering av Sone til skjerm
 */
void Sone::skrivLittOmSoneTilSkjerm() {
    cout << "\tAntall boliger: " << antallBoliger << endl
         << "\t\t" << beskrivelse << endl;
}


/**
 * skrivTilFil(...)
 *
 * funksjonen som skriver sonenes data til Soner.dta
 * @param ut filen dataen blir skrevet til
 * @see Bolig::skrivBoligTilFil(...)
 */
void Sone::skrivTilFil(ofstream & ut) {
    ut << beskrivelse << endl
       << antallBoliger << endl;
    for (auto const & bolig : gBoliger) {
        bolig->skrivBoligTilFil(ut);
    }
}


/**
 * skrivTilFinFil(...)
 *
 * funksjonen skriver ut all dataen til sonen på en fin og leselig måte
 * til en fil, skriver kun boligtypen kundenn er interessert i
 * @param ut filen det blir skrevet til
 * @param type typen boliger som skal skrives til filen
 * @see Bolig::skrivTilFinFil(...)
 */
void Sone::skrivTilFinFil(ofstream & ut, enum boligtype type) {
    ut << beskrivelse << endl << endl;

    for (auto const & bolig : gBoliger) {
        bolig->skrivTilFinFil(ut, type);
    }
}


/**
 * slettBolig(...)
 *
 * Funksjon leter etter korrekt bolig med Bolignr gitt av bruker vec hjelp av
 * lambda funksjonen: [onr](Bolig* bolig) { return bolig->hentBolig(onr);}
 * @see Bolig::hentBolig(...)
 * @param onr oppdrags nummer funksjonen skal slette
 */
void Sone::slettBolig(int onr) {
    // Søker etter bolig med boligNr lik onr
    auto it = find_if(gBoliger.begin(), gBoliger.end(),
        [onr](Bolig* bolig) {
            return (bolig->hentBolig(onr) != nullptr);
    });
    if (it != gBoliger.end()) { // dersom bolig ble funnet
        delete *it;           // sletter Bolig
        gBoliger.erase(it);   // fjerner pekeren fra vectoren
        antallBoliger--;
        cout << "\toppdrag: " << onr << " slettes." << endl;
    } else {
        cout << "\tOppdrag " << onr << " ikke funnet." << endl;
    }
}


/**
 * Bolig* hentOppdrag(...)
 *
 * funksjonen finner boligen med nummer <onr> og returnerer pointer til objekt
 * @param onr nummer vi ser etter
 * @return Bolig* / nullptr
 */
Bolig* Sone::hentOppdrag(int onr) {
    for (auto const & bolig : gBoliger) {
        Bolig* valgtBolig = bolig->hentBolig(onr);
        if (valgtBolig) {
            return valgtBolig;
        }
    }
    return nullptr;
}


/**
 * ~Sone()
 *
 * destructor til Sone objekt, fjerner alle boliger lagret under sonen
 */
Sone::~Sone() {
    for (auto const & bolig : gBoliger) {delete bolig;}
    gBoliger.clear();
}




