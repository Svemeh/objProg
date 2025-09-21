// soner.h
#ifndef SONE_H
#define SONE_H
#include <string>

#include "Kunder.h"
#include "Bolig.h"

/**
 * 
 */
class Sone {
    std::string beskrivelse;
    std::vector<Bolig*> gBoliger;
    int antallBoliger;
public:
    Sone(std::ifstream & inn);
    Sone();

    void nyBolig(int onr);
    void skrivAltOmSoneTilSkjerm();
    void skrivLittOmSoneTilSkjerm();
    void skrivTilFil(std::ofstream & ut);
    void skrivTilFinFil(std::ofstream & ut, enum boligtype type);
    void slettBolig(int onr);


    Bolig* hentOppdrag(int onr);

    ~Sone();
};

#endif // SONE_H
