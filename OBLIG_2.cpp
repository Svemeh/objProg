/**
 * Et program for å registrere bok/film utlån, programmet bruker classes i et
 * arvehierarkiet som består av f.eks: Utlaan -> Film -> Dokumentar
 * Programmet skal også kunne skrive ut alle registrerte Utlån
 * og til slutt skal programmet slette all data
 * 
 * @file OBLIG_2.cpp
 * @author Sverre Mæhlum
 */

 #include <iostream>                //  cout, cin
 #include <vector>                  //  vector
 using namespace std;

class Utlaan {
        string navn;
    public:
        Utlaan() {lesData();}
        Utlaan(string navn) : navn(navn) {}

        void lesData() {cout << "\tNavn:\t"; getline(cin, navn);}

        void skrivData() {cout << "\tNavn:\t" << navn << endl;}
};

class Bok : public Utlaan {
        int ISBN;
    public:
        Bok() {lesData();}
        Bok(string navn) : Utlaan(navn) { lesData(); }

        void lesData() {cout << "\tISBN:\t"; cin >> ISBN; cin.ignore();}

        void skrivData() {
            Utlaan::skrivData();
            cout << "\tISBN:\t" << ISBN << endl;
        }
};

class Skjonnlitteratur : public Bok {
        string sjanger;
    public:
        Skjonnlitteratur() {lesData();}

        void lesData() {cout << "\tSjanger:\t"; getline(cin, sjanger);}

        void skrivData() {
            Bok::skrivData();
            cout << "\tSjanger:\t" << sjanger << endl;
        }
};

class Fagtekst : public Bok {
        string fagFelt;
    public:
        Fagtekst() {lesData();}
        Fagtekst(string navn) : Bok(navn) {lesData();}

        void lesData() {cout << "\tFagFelt:\t"; getline(cin, fagFelt);}

        void skrivData() {
            Bok::skrivData();
            cout << "\tFagFelt:\t" << fagFelt << endl;
        }
};

class Film : public Utlaan {
        int spilletid;
    public:
        Film() {   lesData();  }

        void lesData() {
            cout << "\tSpilletid:\t"; cin >> spilletid; 
            cin.ignore();
        }

        void skrivData() {
            Utlaan::skrivData();
            cout << "\tSpilletid:\t" << spilletid << endl;
        }
};

class Spillefilm : public Film {
        string regissor;
    public:
        Spillefilm() {lesData();}

        void lesData() {cout << "\tRegissør:\t"; getline(cin, regissor);}

        void skrivData() {
            Film::skrivData();
            cout << "\tRegissør:\t" << regissor << endl;
        }
};

class Dokumentar : public Film {
        string tema;
    public:
        Dokumentar() {lesData();}

        void lesData() {cout << "\tTema:\t"; getline(cin, tema);}

        void skrivData() {
            Film::skrivData();
            cout << "\tTema:\t" << tema << endl;
        }
};

vector <Skjonnlitteratur*> gSkjonnlitteratur;
vector <Fagtekst*> gFagtekst;
vector <Spillefilm*> gSpillefilm;
vector <Dokumentar*> gDokumentar;

void skrivUtAlt();
void skrivMeny();
void slettAlt();
void lagFagtekst();


/**
 *  Hovedprogrammet
 *  @see lagFagtekst();
 *  @see skrivUtAlt();
 *  @see slettAlt();
 * 
 */
int main() {
    char valg;

    do {
        skrivMeny();
        cin >> valg; cin.ignore();
        valg = toupper(valg);

        switch(valg) {
            case 'A':gSkjonnlitteratur.push_back(new Skjonnlitteratur()); break;
            case 'B':lagFagtekst();                                       break;
            case 'C':gSpillefilm.push_back(new Spillefilm());             break;
            case 'D':gDokumentar.push_back(new Dokumentar());             break;
            case 'E':skrivUtAlt();                                        break;
            case 'Q':                                                     break;
            default: cout << "\n\tUgyldig kommando!\n";
        }
    } while (valg != 'Q');

    slettAlt();

    return 0;
}


/**
 * Funksjon som velger mellom de to ulike metodene for å registrere en fagtekst
 */
void lagFagtekst() {
    cout << "\nSkriv inn navn på fagteksten (trykk ENTER for tomt navn): ";
    string navn;
    getline(cin, navn);
    if (navn.empty())
        gFagtekst.push_back(new Fagtekst());
    else
        gFagtekst.push_back(new Fagtekst(navn));
}


/**
 * Funksjon som skriver ut alle registrerte utlån
 */
void skrivUtAlt() {
    cout << "\nSkjønnlitteratur:\n";
    for (auto i : gSkjonnlitteratur) i->skrivData();

    cout << "\nFagtekster:\n";
    for (auto i : gFagtekst) i->skrivData();

    cout << "\nSpillefilmer:\n";
    for (auto i : gSpillefilm) i->skrivData();

    cout << "\nDokumentarer:\n";
    for (auto i : gDokumentar) i->skrivData();
}


/**
 * Funksjon som sletter alle Vektorer
 */
void slettAlt() {
    for (auto i : gSkjonnlitteratur) delete i;
    for (auto i : gFagtekst) delete i;
    for (auto i : gSpillefilm) delete i;
    for (auto i : gDokumentar) delete i;

    gSkjonnlitteratur.clear();
    gFagtekst.clear();
    gSpillefilm.clear();
    gDokumentar.clear();
}


/**
 *  Skriver programmets menyvalg/muligheter på skjermen.
 */
void skrivMeny() {
    cout << "\nFølgende kommandoer er tilgjengelig:\n"
         << "\tA - Ny Skjønnlitteratur\n"
         << "\tB - Ny Fagtekst\n"
         << "\tC - Ny Spillefilm\n"
         << "\tD - Ny Dokumentar\n"
         << "\tE - Skriv ut alt\n"
         << "\tQ - Avslutt og slett data\n"
         << "\t\tKommando:";
}