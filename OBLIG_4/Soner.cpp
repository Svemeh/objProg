// Soner.cpp
#include "Soner.h"    // Header for Soner
#include <fstream>     // filestream
#include <iostream>

#include "Sone.h"
#include "Consts.h"    // SONER_FIL
#include "LesData3.h"

using namespace std;


/**
 * handling(...)
 *
 * funksjon tar seg av alle menyvalgene brukeren kan velge mellom ,
 *  som følger av S x x eller O x x
 * @param kommandoer en vector som inneholder kommandoene brukere ntastet inn
 * @see skrivAltOmEnSoneTilSkjerm(...)
 * @see nySone(...)
 * @see skrivAlleSonerTilSkjerm()
 * @see skrivAltOmEttOppdragTilSkjerm(...)
 * @see nyttOppdrag(...)
 * @see slettOppdrag(...)
 */
void Soner::handling(vector<Kommando> kommandoer) {
    if (kommandoer[0].c == 'S') {
        // kommandoer: S x x
        if (kommandoer[2].erInt) {
            if (kommandoer[1].erInt && kommandoer[1].i == 1) {
                skrivAltOmEnSoneTilSkjerm(kommandoer[2].i); // S 1 <snr>
            }else if (!kommandoer[1].erInt && kommandoer[1].c == 'N') {
                nySone(kommandoer[2].i);    // S N <snr>
            }
        }else if (!kommandoer[1].erInt && kommandoer[1].c == 'A') {
            skrivAlleSonerTilSkjerm();  // S A
        }else {
            cout << "Ugyldig kommando" << endl;
        }
    }else {
        // kommandoer: O x x
        if (kommandoer[2].erInt) {
            if (kommandoer[1].erInt && kommandoer[1].i == 1) {
                skrivAltOmEttOppdragTilSkjerm(kommandoer[2].i); // O 1 <onr>
            }else if (!kommandoer[1].erInt && kommandoer[1].c == 'N') {
                nyttOppdrag(kommandoer[2].i);    // O N <onr>
            }else if (!kommandoer[1].erInt && kommandoer[1].c == 'S') {
                slettOppdrag(kommandoer[2].i);    // O S <onr>
            }
        }else {
            cout << "Ugyldig kommando" << endl;
        }
    }
}


/**
 * void lesFraFil()
 *
 * leser inn all data fra "Soner.dta" fil
 * @see Sone::Sone(ifstream)
 */
void Soner::lesFraFil() {
    ifstream innfil(SONER_FIL);

    if (innfil) {
        // henter inn siste oppdrags nummer øverst i fila
        innfil >> sisteOppdragsNr;
        innfil.ignore(numeric_limits<streamsize>::max(), '\n'); // dropper linje

        int temp;
        // leser inn sone nummer
        while (innfil >> temp) {
            innfil.ignore(1);   // hopper over mellomrom i .dta
            // lager sone objektet og lagrer pointer i gSoner map
            Sone* nySone = new Sone(innfil);
            gSoner.insert({temp, nySone});
        }

        // lukker fil
        innfil.close();
    }else{
        cerr << "Klarte ikke åpne " << SONER_FIL << endl;
    }
}


/**
 * nySone(...)
 *
 * funksjon sjekker først om det finnes sone med snr, 
 * hvis ikke lager den ny sone med snr
 * ellers feil melding til bruker om at sone med snr allerede eksisterer
 * @param snr sone nummeret bruker forsøker å lage sone med
 */
void Soner::nySone(int snr) {
    if (gSoner.find(snr) != gSoner.end()) {
        cout << "\tFant allerede en sone med nr " << snr << endl;
    }else{
        Sone* nySone = new Sone();
        gSoner.insert({snr, nySone});
        cout << "\tNy sone opprettet og lagt inn som nr " << snr << endl;
    }
}


/**
 * nyttOpdragg(...)
 *
 * funksjonen lager et nytt oppdrag i sonen med snr
 * @param snr sone nummert brukeren vil lage nytt oppdrag i
 * @see Sone::nyBolig(...)
 */
void Soner::nyttOppdrag(int snr) {
    if (gSoner.find(snr) != gSoner.end()) {
        gSoner.find(snr)->second->nyBolig(++sisteOppdragsNr);
        cout << "\tNytt oppdrag opprettet og lagt inn som nr "
             << sisteOppdragsNr << endl;
    }else {
        cout << "\tIngen sone med dette nummeret." << endl;
    }
}


/**
 * sjekkOmSoneEksisterer
 *
 * funksjonen sjekker om en sone med snr eksisterer
 *  og returerern enten true eller false
 * @param snr sonene bruker leter etter
 * @return boolean
 */
bool Soner::sjekkOmSoneEksisterer(int snr) {
    if (gSoner.find(snr) != gSoner.end()) {
        return true;
    }else{
        return false;
    }
}


/**
 * slettOppdrag
 *
 * funksjonen finner et oppdrag og skriver det ut til bruker
 * så bruker kan dobbelt sjekke at dette er oppdraget han vil slette
 * @param onr oppdraget bruker vil slette
 * @see hentOppdrag(...) - brukes for å finne oppdraget som skal slettes
 * @see Bolig::skrivTilSkjerm()
 * @see Sone::slettBolig(...) - funksjonen som faktisk sletter oppdraget
 */
void Soner::slettOppdrag(int onr) {
    bool funnet = false;
    // Går gjennom alle sonene i map-en
    for (auto& sonePair : gSoner) {
        Sone* sone = sonePair.second;
        if (sone->hentOppdrag(onr)) {  // Dersom denne sone inneholder oppdraget

            // skriver ut all data om oppdrag som vurderes å slette
            sone->hentOppdrag(onr)->skrivTilSkjerm();

            char c = 'N';

            // dobbelt sjekket at bruker vil slette oppdraget
            c = lesChar("Er du sikker på at du vil slette oppdrag? [j/N]");
            if (c == 'J') {
                sone->slettBolig(onr);
            }else {
                cout << "Oppdrag ble ikke slettet." << endl;
            }
            funnet = true;
            break;
        }
    }
    if (!funnet) {
        cout << "\tFant ingen oppdrag med nr " << onr << endl;
    }
}


/**
 * skrivAlleSonerTilSkjerm()
 *
 * funksjonen skriver en oppsumering av alle soner til skjermen
 * @see Sone::skrivLittOmSoneTilSkjerm()
 */
void Soner::skrivAlleSonerTilSkjerm() {
    for (const auto& sone : gSoner) {
        cout << "\tSone " << sone.first << ":";
        sone.second->skrivLittOmSoneTilSkjerm();
    }
}


/**
 * skrivAltOmEnSoneTilSkjerm(...)
 *
 * funksjone skriver alt som en sone til skjermen
 * @param snr sonen bruker vil skrive til skjerm
 * @se Sone::skrivAltOmSoneTilSkjerm()
 */
void Soner::skrivAltOmEnSoneTilSkjerm(int snr) {
    gSoner.find(snr);
    if (gSoner.find(snr) != gSoner.end()) {
        cout << "\tSonenummer: " << snr;
        gSoner.find(snr)->second->skrivAltOmSoneTilSkjerm();
    }else{
        cout << "Fant ingen sone med nr " << snr << endl;
    }
}


/**
 * skrivAltOmEttOppdragTilSkjemr(...)
 *
 * funksjone skrives alt om et oppdrag til skjerm
 * for å gjøre dette må funksjon først finne oppdraget
 * @param onr opdpraget bruker vil skrive til skjerm
 * @see hentOpdprag(...) - funksjonen som finner oppdraget med <onr>
 * @see Bolig::skrivTilSkjerm() - skriver boliges detaljer til skjerm
 */
void Soner::skrivAltOmEttOppdragTilSkjerm(int onr) {
    Bolig* valgtOppdrag = hentOppdrag(onr);
    if (valgtOppdrag) {
        cout << "\tOppdrag " << onr << ":";
        valgtOppdrag->skrivTilSkjerm();
    }
}


/**
 * skrivRelevanteBoligerTilFil(...)
 *
 * funksjonen skriver ut alle boliger i sone <snr> og med riktig bolig type
 * @param ut filen dataen blir skrevet til
 * @param snr sone funksjonen leter etter bolgier i
 * @param type type boliger funksjonen skrives ut
 */
void Soner::skrivRelevanteBoligerTilFil(std::ofstream & ut, int snr,
                                                 enum boligtype type) {
    if (gSoner.find(snr) != gSoner.end()) {
        gSoner.find(snr)->second->skrivTilFinFil(ut, type);
    }else{
        cerr << "Fant ingen sone med nr " << snr << endl;
    }
}


/**
 * skrivTilFil()
 *
 * funksjone som skrives all dataen om alle Soner til Soner.dta
 * @see Sone::skrivTilFil()
 */
void Soner::skrivTilFil() {

    ofstream utfil(SONER_FIL);

    if (utfil) {
        utfil << sisteOppdragsNr << endl;
        for (const auto& sone : gSoner) {
            utfil << sone.first << " ";
            sone.second->skrivTilFil(utfil);
        }
    }else {
        cerr << "Klarte ikke åpne: " << SONER_FIL << "til utskriving av data" 
             << endl;
    }
}


/**
 * hentOppdrag(...)
 *
 * hjelpefunksjon som finner og returenrer en pointer til en bolig
 * @param onr boligen brukeren er ute etter
 * @return Bolig* / Nullptr
 */
Bolig* Soner::hentOppdrag(int onr) {
    for (const auto& sone : gSoner) {
        Bolig* valgtBolig = sone.second->hentOppdrag(onr);
        if (valgtBolig) {   // hvir funksjon fant bolig
            return valgtBolig;  // returner bolig
        }
    }
    cout << "\tFant ingen oppdrag med nr " << onr << endl;
    return nullptr;
}


/**
 * ~Soner()
 *
 * Deconstructor for Soner objekt, husker å slette alle sone objekter registrert
 */
Soner::~Soner() {
    for (auto sone : gSoner) {
        delete sone.second;
    }
    gSoner.clear();
}



