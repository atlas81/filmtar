#ifndef FILMTAR_H
#define FILMTAR_H

#include "film.h"
#include "array.hpp"
#include "memtrace.h"

// Filmtár: filmek gyűjteményét kezeli, rendez, keres, ment/betölt
class Filmtar {
    private:
    Array<Film*> adatok;
    void rendezSegito(int bal, int jobb, bool evSzerint);

    public:
    Filmtar(size_t n);  // Konstruktor
    ~Filmtar();         // Destruktor - felszabadít minden Film*-ot

    void hozzaad(Film* f);  // Film hozzáadása

    void torol(String cim);  // Film törlése cím alapján

    void listaz(std::ostream& os = std::cout) const;  // Összes film kiírása

    void rendez(bool evSzerint = false);  // Rendezés év vagy cím alapján

    int particional(int bal, int jobb, bool evSzerint);  // Quicksort partíció

    Film* keres(String kulcsszo) const;  // Keresés cím alapján

    Film* keres(int ev) const;  // Keresés év alapján

    Film* keres(char c) const;

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