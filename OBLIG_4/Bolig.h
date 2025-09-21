// Bolig.h
#ifndef BOLIG_H
#define BOLIG_H
#include "Enum.h"
#include <fstream>

class Bolig {
    boligtype  boligType;
    int boligNr,
        dato,
        byggår,
        bruttoAreal,
        soverom,
        pris;
    std::string saksBehandler,
                eier,
                gateAdresse,
                postAdresse,
                beskrivelse;
public:
    Bolig(std::ifstream & inn, enum boligtype);
    Bolig(int onr, enum boligtype);

    static Bolig* lesInnBoligFraFil(std::ifstream & inn);
    static Bolig* lesInnBoligFraBruker(int onr);

    void skrivBoligTilFil(std::ofstream & ut);
    void skrivTilFinFil(std::ofstream & ut, enum boligtype type);
    void skrivTilSkjerm();

    Bolig* hentBolig(int onr);

    virtual ~Bolig();

};

#endif // BOLIG_H
