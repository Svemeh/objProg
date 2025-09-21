//
// Created by Sverre Mæhlum on 25/03/2025.
//

#ifndef CONSTS_H
#define CONSTS_H
#include <string>

/**
 * const for fil data navn
 */
const std::string KUNDER_FIL = "Kunder.dta";
const std::string SONER_FIL = "Soner.dta";

/**
 * const for bolig data
 */
int const ÅRSTALL = 2025;
int const MINÅRSTALL = 1800;
int const MAXAREAL = 10000;
int const MINAREAL = 10;
int const MAXSOVEROM = 10;
int const MINSOVEROM = 1;
int const MAXPRIS = 100000000;
int const MINPRIS = 6000;

/**
 * Data for utskrift
 */
int const ANTALLBOLIGUTSKRIFT = 5;
int const ANTALLKUNDEUTSKRIFT = 10;

#endif //CONSTS_H
