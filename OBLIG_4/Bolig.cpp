#include "Bolig.h"
#include <fstream>
#include <string>
#include <iostream>

#include "Consts.h"
#include "Enebolig.h"
#include "LesData3.h"
#include"Global.h"


using namespace std;


/**
 * Bolig(...)
 *
 * Construcotr for Bolig objekt da de leses inn fra fil
 * @param inn filen data blir lest fra
 * @param type boligtypen som skal opprettes
 */
Bolig::Bolig(ifstream & inn, enum boligtype type) : boligType(type) {

    // leser inn alle intene til boligen
    inn >> boligNr >> dato >> byggår >> bruttoAreal >> soverom >> pris;
    inn.ignore(numeric_limits<streamsize>::max(), '\n'); // dropper linje

    // leser inn alle strings til boligen
    getline(inn, saksBehandler);
    getline(inn, eier);
    getline(inn, gateAdresse);
    getline(inn, postAdresse);
    getline(inn, beskrivelse);
}


/**
 * Bolig(...)
 *
 * Constructor for Bolig objekt da bolig registreres av bruker
 * bruker taster inn all data til Boligen
 * @param onr bolignummerert som bolig skal bli registrert med
 * @param type type bolig som registreres
 * @see hvaErDatoen() - henter datoen automatisk
 */
Bolig::Bolig(int onr, enum boligtype type) : boligType(type) {

    boligNr = onr;

    // leser inn registrerings dato automatisk
    dato = hvaErDatoen();

    // leser inn alle intene til boligen
    byggår = lesInt("\t\tByggår: ", MINÅRSTALL, ÅRSTALL);
    bruttoAreal = lesInt("\t\tBruttoAreal: ", MINAREAL, MAXAREAL);
    soverom = lesInt("\t\tSoverom: ", MINSOVEROM, MAXSOVEROM);
    pris = lesInt("\t\tPris: ", MINPRIS, MAXPRIS);


    // leser inn alle strings til boligen
    do {
        cout << "\tsaksBehandler: ";
        getline(cin, saksBehandler);
    }while (saksBehandler.empty());
    do {
        cout << "\teier: ";
        getline(cin, eier);
    }while (eier.empty());
    do {
        cout << "\tgateAdresse: ";
        getline(cin, gateAdresse);
    }while (gateAdresse.empty());
    do {
        cout << "\tpostAdresse: ";
        getline(cin, postAdresse);
    }while (postAdresse.empty());
    do {
        cout << "\tbeskrivelse: ";
        getline(cin, beskrivelse);
    }while (beskrivelse.empty());
}


/**
 * lesInnBoligFraBruker(...)
 *
 * funksjonen leser inn boligtype fra brukeren og lager korrekt klasse objekt
 * @param onr bolig nummerert som skal registreres
 * @return Bolig*
 * @see Enebolig(int)
 * @see Bolig(int(int, enum)
 */
Bolig* Bolig::lesInnBoligFraBruker(int onr) {

    // leser inn boligtype
    char c;
    do {
        c = lesChar("\tE(nebolig) eller B(olig)");
    }while (c != 'E' && c != 'B');

    // lager korrekt boligtype
    if (c == 'E') {
        return new Enebolig(onr);
    }else{
        return new Bolig(onr, BOLIG);
    }
}


/**
 * lesInnBoligFraFil(...)
 *
 * hjelpefunksjon som lar programmet vite om den skal opprette et Bolig objekt
 * eller et Enebolig objekt som er en underobjekt til Bolig klassen
 * @param inn filen data leses fra
 * @return Bolig*
 */
Bolig* Bolig::lesInnBoligFraFil(ifstream & inn) {

    // leser inn boligtype
    string temp;
    getline(inn, temp);

    // lager korrekt boligtype
    if (temp == "ENEBOLIG") {
        return new Enebolig(inn);
    }else if (temp == "BOLIG") {
        return new Bolig(inn, BOLIG);
    }else {
        cerr << "Ugyldig boligtype" << endl;
        return nullptr;
    }
}


/**
 * skrivBoligTilFil(...)
 *
 * funksjon skrives all boligens data til Soner.dta fil for lagring
 * @param ut Soner.dta fil
 */
void Bolig::skrivBoligTilFil(ofstream & ut) {
    ut << (boligType ? "ENEBOLIG" : "BOLIG") << endl
       << boligNr << " " << dato << " " << byggår << " " << bruttoAreal 
       << " " << soverom << " " << pris << endl
       << saksBehandler << endl
       << eier << endl
       << gateAdresse << endl
       << postAdresse << endl
       << beskrivelse << endl;

    if (boligType == ENEBOLIG) {
        Enebolig* enebolig = (Enebolig*) this;
        enebolig->skrivEneboligTilFil(ut);
    }
}


/**
 * skrivTilFinFIl(...)
 *
 * funksjon skriver ut dataen om bolig på en pen og ryddig måte
 * funksjon skriver kun ut boligene som har ritkig bolig type
 * @param ut filen data skrives til
 * @param type boligtypen som blir skrevet til fil
 */
void Bolig::skrivTilFinFil(ofstream & ut, enum boligtype type) {
    if ((type == ENEBOLIG && boligType == ENEBOLIG) 
        || (type == BOLIG && boligType == BOLIG)) {

        ut << "Bolignummer: " << boligNr << "\tBoligtype: " 
           << (boligType ? "Enebolig" : "Bolig") << endl
           << "Registrerings dato: " << dato <<  "\tByggår: " << byggår << endl
           << "Bruttoareal: " << bruttoAreal<< " Kvadratmeter\tAntall soverom: "
           << soverom << endl
           << "Pris: " << pris << endl
           << "Eier: " << eier << "\tSaksbehandler: " << saksBehandler << endl
           << gateAdresse << "\t" << postAdresse << endl
           << beskrivelse << endl;

        if (boligType == ENEBOLIG) {
            Enebolig* enebolig = (Enebolig*) this;
            enebolig->skrivTilFinFil(ut);
        }
        ut << endl;
    }
}


/**
 * skrivTilSkjerm()
 *
 * funksjonen skrives ut all dataen om en bolig til skjerm
 * @see Enebolig::skrivTilSkjerm()
 */
void Bolig::skrivTilSkjerm() {
    cout << "\t\tBoligernummer: " << boligNr
         << "\tType: " << (boligType == ENEBOLIG ? "Enebolig" : "Bolig") << endl
         << "\t\t" << beskrivelse << endl
         << "\t\tEier:          " << eier << endl
         << "\t\tAdresse:       " << gateAdresse << endl
         << "\t\tPostadresse:   " << postAdresse << endl
         << "\t\tByggår:        " << byggår << endl
         << "\t\tBruttoAreal:   " << bruttoAreal << endl
         << "\t\tSoverom:       " << soverom << endl
         << "\t\tPris:          " << pris << endl
         << "\t\tSaksbehandler: " << saksBehandler << endl
         << "\t\tdato lagt til: " << dato << endl;

    if (boligType == ENEBOLIG) {
        Enebolig* enebolig = (Enebolig*) this;
        enebolig->skrivTilSkjerm();
    }
    cout << endl;
}


/**
 * hentBolig(...)
 *
 * funksjonen kalles ved Sone::hentOppdrag(...) 
 * og brukes for å finne et oppdrag / bolig kun ved opdprag nummeret deres
 * @param onr oppdrag som skal finnes
 * @return boolean
 */
Bolig* Bolig::hentBolig(int onr) {
    if (onr == boligNr) {
        return this;
    }else {
        return nullptr;
    }
}


/**
 * ~Bolig()
 *
 * Deconstrucotr for bolig
 */
Bolig::~Bolig() {}
