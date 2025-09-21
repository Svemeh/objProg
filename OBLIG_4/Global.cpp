#include "Global.h" // header for Global.cpp
#include <iostream> // cin, cout, endl
#include <sstream>  // istringstream
#include <vector>   // vector
#include <string>   // string
#include <cctype>   // toupper


using namespace std;

/**
 * void skrivMeny()
 *
 * skriver ut alle menyvalgene på skjermen
 */
void skrivMeny() {
    cout << "Følgende kommandoer er tilgjengelige:" << endl
         << "\tK N              - Ny Kunde" << endl
         << "\tK 1 <knr>        - Skriv alt om en kunde" << endl 
         << "\tK A              - Skriv alle kunder" << endl
         << "\tK E <knr>        - Endre data om en kunde" << endl 
         << "\tK S <knr>        - Slett en kunde" << endl
         << "\tK O <knr>        - Oversikt over en kunde skrives til fil" <<endl 
         << "\tS N <snr>        - Ny sone" << endl
         << "\tS 1 <snr>        - Skriv alt om en sone" << endl 
         << "\tS A              - Skriv alle soner" << endl
         << "\tO N <snr>        - Nytt oppdrag i sone" << endl 
         << "\tO 1 <onr>        - Skriv alt om ett oppdrag" << endl
         << "\tO S <onr>        - Slett ett oppdrag" << endl 
         << "\tQ                - Quit/Avslutt porgrammet" << endl << endl;
}

/**
 * vector<Kommando> lesKommando()
 *
 * leser inn alle kommando "tegnene" brukeren inputter 
 * og skiller på om de er int eller char
 * ved en hjelpe- bool som i structen Kommando heter "erInt"
 * @return vector<Kommando> // en vector som inneholder alle tegnene lagrert
 */
vector<Kommando> lesKommando() {
    string line;
    cout << "Kommando:\t";
    getline(std::cin, line);

    istringstream iss(line);
    std::vector<Kommando> kommandoer;
    string kommandoStr;

    // Del opp input-linjen i tegn
    while (iss >> kommandoStr) {
        Kommando kommando;
        // Dersom tegnet er ett enkelt tegn som ikke er et siffer, tolkes char
        if (kommandoStr.size() == 1 && !std::isdigit(kommandoStr[0])) {
            kommando.erInt = false;
            kommando.c = toupper(kommandoStr[0]);
        } else {
            try {
                // Forsøker å konvertere tegnet til et int
                kommando.i = std::stoi(kommandoStr);
                kommando.erInt = true;
            } catch (const std::exception&) {
                // Ved konverteringsfeil tolkes tegnet som en char
                kommando.erInt = false;
                kommando.c = kommandoStr[0];
            }
        }
        kommandoer.push_back(kommando);
    }
    return kommandoer;
}

/**
 * int hvaErDatoen()
 *
 * henter dags datoen
 * @return datoen som int med format ÅÅÅÅMMDD
 */
int hvaErDatoen() {

    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);

    // henter årstallet
    string datoString = to_string(datetime.tm_year + 1900);

    // henter måneden
    if (datetime.tm_mon+1 <= 9) {
        datoString.append("0");
    }
    datoString.append(to_string(datetime.tm_mon+1));

    // henter dagen i måneden
    if (datetime.tm_mday <= 9) {
        datoString.append("0");
    }
    datoString.append(to_string(datetime.tm_mday));

    // konverterer string til int og returner
    return stoi(datoString);
}