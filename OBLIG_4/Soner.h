// soner.h
#ifndef SONER_H
#define SONER_H
#include <map>

#include "Sone.h"
#include "Global.h"

/**
 *
 */
class Soner {
    int sisteOppdragsNr;
    std::map <int, Sone*> gSoner;    ///<  Datastrukturen med alle "sone" objektene.
public:
    void handling(std::vector<Kommando>);
    void lesFraFil();
    void nySone(int snr);
    void nyttOppdrag(int onr);
    bool sjekkOmSoneEksisterer(int snr);
    void slettOppdrag(int onr);
    void skrivAlleSonerTilSkjerm();
    void skrivAltOmEnSoneTilSkjerm(int snr);
    void skrivAltOmEttOppdragTilSkjerm(int onr);
    void skrivRelevanteBoligerTilFil(std::ofstream & ut, int snr, enum boligtype type);
    void skrivTilFil();

    Bolig* hentOppdrag(int onr);

    ~Soner();

};

#endif // SONER_H

