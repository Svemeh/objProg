#include "Enebolig.h"

#include <iostream>

#include "Consts.h"
#include "LesData3.h"

using namespace std;


/**
 * Enebolig(...)
 *
 * Constructor for Enebolig objekt da det leses inn fra fil
 * @param inn filen det leses fra
 * @see Bolig:Bolig(ifstream, enum)
 */
Enebolig::Enebolig(ifstream & inn) : Bolig(inn, ENEBOLIG){
    int temp;
    inn >> areal >> temp;
    inn.ignore(numeric_limits<streamsize>::max(), '\n'); // dropper linje
    if (temp == 1) {
        selveid = true;
    }else {
        selveid = false;
    }
}


/**
 * Enebolig(...)
 *
 * Constructor for Enebolig objekt da bruker registrerer enebolig manuelt
 * @param onr bolignummert enebolig blir registrert med
 */
Enebolig::Enebolig(int onr) : Bolig(onr, ENEBOLIG) {
    areal = lesInt("\t\tAreal: ", MINAREAL, MAXAREAL);

    char c;
    c = lesChar("\t\tSelveid (J/N): ");
    if (c == 'J') {
        selveid = true;
    }else {
        selveid = false;
    }
}


/**
 * skrivEneboligTilFil(...)
 *
 * funksjone som skrives Enebolig data til Soner.dta
 * @param ut filen som data blir skrevet til "Soner.dta"
 */
void Enebolig::skrivEneboligTilFil(ofstream & ut) {
    ut << areal << " " << selveid << endl;
}


/**
 * skrivTilFInFIl(...)
 *
 * funksjonen som skrives dataen om enebolig objekt til fil på en ryddig måte
 * @param ut filen data skrives til
 */
void Enebolig::skrivTilFinFil(ofstream & ut) {
    ut << (selveid ? "Selveiet" : "Festetomt") << endl
       << "Areal på tomt: " << areal << " Kvadratmeter" << endl;
}


/**
 * skrivTilSkjerm()
 *
 * skrives Enebolig variablene til skjerm
 */
void Enebolig::skrivTilSkjerm() {
    cout << "\t\t\tAreal: " << areal << " Kvadratmeter" << endl
         << "\t\t\tSelveid: " << (selveid ? "Ja" : "Nei") << endl;
}


/**
 * ~Enebolig()
 *
 * Deconstrcutor for Enebolig objekt
 */
Enebolig::~Enebolig() {}







