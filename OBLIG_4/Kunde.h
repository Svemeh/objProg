// Kunder.h
#ifndef KUNDE_H
#define KUNDE_H
#include <string>
#include <vector>

#include "Enum.h"   // Bolig type

/**
 * Kunde klasse
 */
class Kunde {
    boligtype boligType;
    std::vector<int> soner;
    std::string navn,
                gateAddresse,
                postAddresse,
                Email;
    int kundeNr,
        tlf;
public:
    Kunde(std::ifstream & inn, int knr);
    Kunde(int knr);

    void endreKunde();
    bool erSoneRegistrert(int snr);
    void skrivAltOmKundeTilSkjerm();
    void skrivLittOmKundeTilSkjerm();
    void const skrivTilFil(std::ofstream & ut);
    void skrivTilFinFil(std::ofstream & ut);


    Kunde* hentKunde(int knr);

    ~Kunde();
};

#endif // KUNDE_H
