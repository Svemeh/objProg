// Kunder.h
#ifndef KUNDER_H
#define KUNDER_H

#include <list>

#include "Kunde.h"
#include "Global.h"

/**
 *  Kunder
 */
class Kunder {
    int sisteKundeNr;
    std::list <Kunde*> gKunder;
public:
    void endreEnKunde(int knr);
    void enKundeSkrivTilFil(int knr);
    void handling(std::vector<Kommando> kommandoer);
    void lesFraFil();
    void nyKunde();
    void skrivAlleKunderTilSkjerm();
    void skrivTilFil();
    void slettKunde(int knr);

    Kunde* hentKunde(int pos);

    ~Kunder();
};

#endif // KUNDER_H
