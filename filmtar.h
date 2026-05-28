#ifndef FILMTAR_H
#define FILMTAR_H

#include "film.h"
#include "array.hpp"
#include "memtrace.h"

// Filmtár: filmek gyűjteményét kezeli, rendez, keres, ment/betölt
class Filmtar {
    private:
    Array<Film*> adatok;
    Array<int> indexek; // az adatok rendezett indexei 
    void rendezSegito(int bal, int jobb, bool evSzerint);

    public:
    Filmtar(size_t n);  // Konstruktor
    ~Filmtar();         // Destruktor - felszabadít minden Film*-ot

    void hozzaad(Film* f);  // Film hozzáadása

    void torol(String cim);  // Film törlése cím alapján

    void listaz(std::ostream& os = std::cout) const;  // Összes film kiírása

    void rendez(bool evSzerint = false);  // Rendezés év vagy cím alapján

    int particional(int bal, int jobb, bool evSzerint);  // Quicksort partíció

    Film* keres(String kulcsszo) const; // csak 1-et ad vissza, letezes vizsgalatra hasznalando

    Film* keres(String kulcsszo, Array<int> &talalatok) const;  // Keresés cím alapján (osszes talalat)

    Film* keres(int ev, Array<int> &talalatok) const;  // Keresés év alapján (osszes talalat)

    Film* keres(char c, Array<int> &talalatok) const; // Kereses tipus alapjan (osszes talalat)

    void ment(const char* path) const;  // Mentés fájlba

    void betolt(const char* path);  // Betöltés fájlból

    Film* operator[](size_t i) {
        return adatok[i];
    }

    size_t getSize() const {
        return adatok.size();
    }
};

#endif