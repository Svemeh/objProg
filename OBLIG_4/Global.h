
#ifndef __GLOBAL_H
#define __GLOBAL_H

#include <vector>   // vector

void skrivMeny();
int hvaErDatoen();

struct Kommando {
    bool erInt;
    char c;
    int i;
};

std::vector<Kommando> lesKommando();



#endif  // __GLOBAL_H