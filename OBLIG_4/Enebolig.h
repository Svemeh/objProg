// Enebolig.h
#ifndef ENEBOLIG_H
#define ENEBOLIG_H
#include "Bolig.h"

class Enebolig : public Bolig {
    int areal;
    bool selveid;
public:
    Enebolig(std::ifstream & inn);
    Enebolig(int onr);

    void skrivEneboligTilFil(std::ofstream & ut);
    void skrivTilFinFil(std::ofstream & ut);
    void skrivTilSkjerm();

    ~Enebolig();
};

#endif // ENEBOLIG_H
