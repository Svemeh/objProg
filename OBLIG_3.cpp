/** 
 *   Skjelett for obligatorisk oppgave nr 3 i PROG1003 - OOP.
 *
 *   Programmet inneholder en oversikt alle kjøretøyene til en privatperson.
 *   Kjøretøyene er identifisert via sitt unike chassisnummer (åtte sifre),
 *   hvor kjøretøyene er lagret i en <map> og nummeret er key'en.
 *   Brukeren/programmet skal kunne:
 *       - se ALLE kjøretøyene som er lagret i datastrukturen (map'en)
 *       - legge inn et nytt kjøretøy
 *       - endre data om et gitt kjøretøy
 *       - skrive datastruktur til fil
 *       - lese datastruktur fra fil
 *
 *   @file    OBLIG3.TPL
 *   @author  Peter Bøhncke Nes, Kristian Jegerud & Frode Haug, NTNU
 *   
 *   løst av @author Sverre Mæhlum
 *   @file   OBLIG_3.cpp
 */


 #include <iostream>              //  cout, cin
 #include <fstream>               //  ifstream, ofstream
 #include <string>
 #include <map>
 #include "LesData2.h"            //  Verktøykasse for lesing av diverse data
 using namespace std;
 
 /**
  *  Kjøretøy (med merke).
  */
 class Kjoretoy {
   private:
       string merke;
   public:
       Kjoretoy();
       Kjoretoy(ifstream & inn);
       virtual void endreData() = 0;
       virtual void lesData();
       virtual void skrivData() const;
       virtual void skrivTilFil(ofstream & ut) const;
 };
 
 
 /**
  *  Bil (med antall seter og stasjonsvogn/ikke stasjonsvogn).
  */
 class Bil : public Kjoretoy {
   private:
       int  antallSeter;
       bool stasjonsvogn;
   public:
       Bil()  {  antallSeter = 0;  stasjonsvogn = false;  }
       Bil(ifstream & inn);
       virtual void endreData();
       virtual void lesData();
       virtual void skrivData() const;
       virtual void skrivTilFil(ofstream & ut) const;
 };
 
 
 /**
  *  Motorsykkel (med motoreffekt).
  */
 class Motorsykkel : public Kjoretoy {
   private:
       int motoreffekt;
   public:
       Motorsykkel()  { motoreffekt = 0;  }
       Motorsykkel(ifstream & inn);
       virtual void endreData();
       virtual void lesData();
       virtual void skrivData() const;
       virtual void skrivTilFil(ofstream & ut) const;
 };
 
 
 /**
  *  Lastebil (med lengde og makslast).
  */
 class Lastebil : public Kjoretoy {
   private:
       int lengde;
       int maksLast;
   public:
       Lastebil()  {  lengde = 0;  maksLast = 0;  }
       Lastebil(ifstream & inn);
       virtual void endreData();
       virtual void lesData();
       virtual void skrivData() const;
       virtual void skrivTilFil(ofstream & ut) const;
 };
 
 
 void endreEtKjoretoy();
 void lesFraFil();
 void nyttKjoretoy();
 void skrivAlleKjoretoy();
 void skrivMeny();
 void skrivTilFil();
 
 
 map <int, Kjoretoy*> gKjoretoy;    ///<  Datastrukturen med alle kjøretøyene.
 
 
 /**
  *  Hovedprogrammet:
  */
 int main(void)  {
     char kommando;
 
     lesFraFil();
     skrivMeny();
     kommando = lesChar("Kommando");
 
     while (kommando != 'Q') {
         switch (kommando) {
           case 'N':  nyttKjoretoy();           break;
           case 'A':  skrivAlleKjoretoy();      break;
           case 'E':  endreEtKjoretoy();        break;
           default:   skrivMeny();              break;
         }
         kommando = lesChar("\nKommando");
     }
     skrivTilFil();
     return 0;
 }
 
 
 // ---------------------------------------------------------------------------
 //                       DEFINISJON AV KLASSE-FUNKSJONER:
 // ---------------------------------------------------------------------------
 
 /**
  *  Leser merket på kjøretøy fra fil.
  *
  *  @param   inn  - Filobjektet egne data leses inn fra
  */
 Kjoretoy::Kjoretoy(ifstream & inn) {
     inn >> merke;
 }
 
 
 /**
  *  Leser merket på kjøretøyet fra brukeren/tastaturet.
  */
 void Kjoretoy::lesData() {
    cout << "Merke:\t";
    getline(cin, merke);
 }
 
 
 /**
  *  Skriver ut merket på kjøretøyet på skjermen. 
  */
 void Kjoretoy::skrivData() const {
    cout << "\t\tMerke:\t" << merke << endl;
 }
 
 
 /**
  *  Skriver ut merket på kjøretøyet til fil.
  *
  *  @param   ut  - Filobjektet egne data skrives ut til
  */
 void Kjoretoy::skrivTilFil(ofstream & ut) const {
    ut << merke << endl;
 }
 
 // ---------------------------------------------------------------------------
 
 /**
  *  Leser antall seter og om det er en stasjonsvogn fra fil.
  *
  *  @param   inn  - Filobjektet egne data leses inn fra
  */
 Bil::Bil(ifstream & inn) : Kjoretoy(inn) {
    inn >> antallSeter >> stasjonsvogn;
 }
 
 
 /**
  *  Gir brukeren mulighet til å endre på alle egne data.
  *
  *  @see  skrivData()
  */
 void Bil::endreData() {
    antallSeter = lesInt("antall seter:", 0, 100);

    char c;
    do { // fortsetter å be om input til bruker svarer enten ja eller nei
        c = lesChar("er det en stasjonsvogn: [j/n]");
    }while(c != 'J' && c != 'N');
    if (c == 'J') {stasjonsvogn = true;} else {stasjonsvogn = false;}
 }
 
 
 /**
  *  Leser baseklassens data og ALLE egne data.
  *
  *  @see   Kjoretoy::lesData()
  */
 void Bil::lesData() {
    Kjoretoy::lesData();
    antallSeter = lesInt("antall seter:", 0, 100);

    char c;
    do { // fortsetter å be om input til bruker svarer enten ja eller nei
        c = lesChar("er det en stasjonsvogn: [j/n]");
    }while(c != 'J' && c != 'N');
    if (c == 'J') {stasjonsvogn = true;} else {stasjonsvogn = false;}
 }
 
 
 /**
  *  Skriver baseklassens data og ALLE egne data.
  *
  *  @see  Kjoretoy::skrivData()
  */
 void Bil::skrivData() const {
    Kjoretoy::skrivData(); // skriver ut merke
    cout << "\t\tAntall seter:\t" << antallSeter << endl 
            << "\t\tStasjonsvogn:\t" << boolalpha << stasjonsvogn << endl;
 }
 
 
 /**
  *  Skriver 'B', baseklassens data og ALLE egne data til fil.
  *
  *  @param   ut  - Filobjektet egne data skrives ut til
  *  @see     Kjoretoy::skrivTilTil(...)
  */
 void Bil::skrivTilFil(ofstream & ut) const {
    ut << "B ";
    Kjoretoy::skrivTilFil(ut); // skriver merke til fil
    ut << antallSeter << " " << stasjonsvogn << endl;
 }
 
 // ---------------------------------------------------------------------------
 
 /**
  *  Leser motoreffekt fra fil. 
  *
  *  @param   inn  - Filobjektet egne data leses inn fra
  */
 Motorsykkel::Motorsykkel(ifstream & inn) : Kjoretoy(inn) {
    inn >> motoreffekt;
 }
 
 
 /**
  *  Tilbyr brukeren å endre på alle egne data.
  *
  *  @see  skrivData()
  */
 void Motorsykkel::endreData() {
    motoreffekt = lesInt("Motoreffekt:", 1, 100);
 }
 
 
 /**
  *  Leser baseklassens data og motoreffekt fra brukeren.
  *
  *  @see   Kjoretoy::lesData()
  */
 void Motorsykkel::lesData() {
    Kjoretoy::lesData();    // leser inn merke fra bruker
    motoreffekt = lesInt("motoreffekt:", 1, 100);
 }
 
 
 /**
  *  Skriver baseklassens data og motoreffekt på skjermen.
  *
  *  @see  Kjoretoy::skrivData()
  */
 void Motorsykkel::skrivData() const {
    Kjoretoy::skrivData();  // skriver ut merke
    cout << "\t\tMotoreffekt:\t" << motoreffekt << endl;
 }
 
 
 /**
  *  Skriver 'M', baseklassens data og motoreffekt på fil.
  *
  *  @param   ut  - Filobjektet egne data skrives ut til
  *  @see     Kjoretoy::skrivTilTil(...)
  */
 void Motorsykkel::skrivTilFil(ofstream & ut) const {
    ut << "M ";
    Kjoretoy::skrivTilFil(ut);  // skriver ut merke til fil
    ut << motoreffekt << endl;
 }
 
 // ---------------------------------------------------------------------------
 
 /**
  *  Leser legnde og makslast fra fil. 
  *
  *  @param   inn  - Filobjektet egne data leses inn fra
  */
 Lastebil::Lastebil(ifstream & inn) : Kjoretoy(inn) {
     inn >> lengde >> maksLast;
 }
 
 
 /**
  *  Gir brukeren mulighet til å endre på alle egne data.
  *
  *  @see  skrivData()
  */
 void Lastebil::endreData() {
    lengde = lesInt("Lengde:", 1, 100);
    maksLast = lesInt("Maks last:", 1, 100);
 }
 
 
 /**
  *  Leser baseklassens data, lengde og makslast fra brukeren.
  *
  *  @see   kjoretoy::lesData()
  */
 void Lastebil::lesData() {
    Kjoretoy::lesData();    // leser inn merke fra bruker
    lengde = lesInt("Lengde:", 1, 100);
    maksLast = lesInt("Maks last:", 1, 100);
 }
 
 
 /**
  *  Skriver baseklassens data, lengde og makslast på skjermen.
  *
  *  @see  Kjoretoy::skrivData()
  */
 void Lastebil::skrivData() const {
    Kjoretoy::skrivData();  // skriver ut merke
    cout << "\t\tLengde:\t" << lengde << endl << "\t\tMaks last:\t" << maksLast 
            << endl;
 }
 
 
 /**
  *  Skriver 'A', baseklassens data, lengde og makslast til fil.
  *
  *  @param   ut  - Filobjektet egne data skrives ut til
  *  @see     Kjoretoy::skrivTilTil(...)
  */
 void Lastebil::skrivTilFil(ofstream & ut) const {
    ut << "L ";
    Kjoretoy::skrivTilFil(ut);  // skriver ut merke til fil
    ut << lengde << " " << maksLast << endl;
 }
 
 
 // ---------------------------------------------------------------------------
 //                       DEFINISJON AV ANDRE FUNKSJONER:
 // ---------------------------------------------------------------------------
 
 /**
  *  Lar brukeren (hvis mulig) endre dataene for en subklasse.
  *
  *  @see   virtual Kjoretoy::endreData()
  */
 void endreEtKjoretoy() {
    int chassis;
    chassis = lesInt("Chassisnummer:", 10000000, 99999999);

    // Ser etter kjøretøy med gitt chassisnummer
    if (gKjoretoy.find(chassis) == gKjoretoy.end()) {
        cout << "Kjøretøy med dette chassisnummeret er ikke registrert.\n";
    }else{
        // endrer data for subklassene til kjøretøyet
        gKjoretoy[chassis]->endreData(); 
    }
 }
 
 
 /**
  *  Leser kjøretøy inn fra fil, og legger de inn i 'gKjoretoy'.
  *
  *  @see  Bil::Bil(...)
  *  @see  Lastebil::Lastebil(...)
  *  @see  Motorsykkel::Motorsykkel(...)
  */
 void lesFraFil() {
    ifstream innfil("OBLIG_3.dta"); // åpner fil for lesing
    if (!innfil) {                  // dersom fil ikke kan åpnes
        cout << "Kunne ikke åpne filen OBLIG_3.dta.";
    }else{

        int chassis;
        char type;

        while (innfil >> chassis >> type) {
            // initialiserer kjøretøyet, midlertidig uten peker
            Kjoretoy* kjoretoy = nullptr; 

            switch(type) {
                case 'B':
                    kjoretoy = new Bil(innfil);
                    break;
                case 'L':
                    kjoretoy = new Lastebil(innfil);
                    break;
                case 'M':
                    kjoretoy = new Motorsykkel(innfil);
                    break;
                default:    // skal strengt tatt aldri skje
                    cout << "Ukjent kjøretøy type:\t" << type << endl;
                    break;
            }
            if (kjoretoy) { // dersom kjøretøyet er initialisert
                // legger kjøretøyet inn i datastrukturen med chassis som "key"
                gKjoretoy[chassis] = kjoretoy;  
            }
        }
        innfil.close(); // lukker filen
    }
 }
 
 
 /**
  *  Legger inn et nytt kjøretøy hvis det er plass i datastrukturen.
  *
  *  @see  Bil::Bil()
  *  @see  Lastebil::Lastebil()
  *  @see  Motorsykkel::Motorsykkel()
  *  @see  virtual Kjoretoy::lesData()
  */
 void nyttKjoretoy() {
    int chassis;
    char type;
    
    chassis = lesInt("Chassisnummer:", 10000000, 99999999);

    // Sjekker om kjøretøyet allerede er registrert i "map-en"
    if (gKjoretoy.find(chassis) != gKjoretoy.end()) {
        cout << "Kjøretøy med dette chassisnummeret er allerede registrert.\n";
    }else{
        // initialiserer kjøretøyet, midlertidig uten peker
        Kjoretoy* kjoretoy = nullptr;

        do {    // fortsetter å be om "type" til bruker gir en gyldig "type"
            type = lesChar("Type (B, L eller M)");
        }while (type != 'B' && type != 'L' && type != 'M');

        switch(type) {
            case 'B':
                kjoretoy = new Bil();
                break;
            case 'L':
                kjoretoy = new Lastebil();
                break;
            case 'M':
                kjoretoy = new Motorsykkel();
                break;
        }

        if (kjoretoy) {            // dersom kjøretøyet er initialisert
            kjoretoy->lesData();   // Kaller den korrekte lesdata basert på type

            // legger kjøretøyet inn i datastrukturen med chasis som key
            gKjoretoy[chassis] = kjoretoy;
            cout << "Kjøretøyet er registrert.\n";
        }
    }
 }
 
 
 /**
  *  Skriver all data om alle kjøretøyene.
  *
  *  @see   virtual Kjoretoy::skrivData()
  */
 void skrivAlleKjoretoy() {
    cout << "Alle registrerte kjøretøy:\n";
    for (const auto &i : gKjoretoy) { // for alle kjøretøy i datastrukturen
        cout << "\tchassisnummer:\t" << i.first << endl;
        i.second->skrivData();  // skriver ut data fra subklassen (B, L eller M)
        cout << endl;
    }
 }
 

 /**
  *  Skriver programmets menyvalg/muligheter på skjermen.
  */
 void skrivMeny() {
     cout << "\nFølgende kommandoer er tilgjengelig:\n"
          << "\tN - Nytt kjoretøy (bil, lastebil eller motorsykkel)\n"
          << "\tA - Skriv alle kjoretoyene\n"
          << "\tE - Endre et gitt kjoretoy\n"
          << "\tQ - Quit / avslutt\n\n";
 }
 
 
 /**
  *  Skriver hele datastrukturen til fil.
  *
  *  @see   virtual Kjoretoy::skrivTilFil(...)
  */
 void skrivTilFil() {
    ofstream utfil("OBLIG_3.dta");  // åpner fil til skriving
    if (!utfil) {                   // dersom fil ikke kan åpnes
        cout << "Kunne ikke åpne filen OBLIG_3.dta.\n";
    }else{
        for (const auto &i : gKjoretoy) {   // for kjøretøy i datastrukturen
            utfil << i.first << " ";        // skriver ut chassisnummer
            i.second->skrivTilFil(utfil);   // skriver ut subklasse data
        }
    }
 }
 