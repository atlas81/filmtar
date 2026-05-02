#ifndef FILMTAR_H
#define FILMTAR_H

#include "film.h"
#include "array.hpp"

class Filmtar {
    Array<Film*> adatok;

    public:

    Filmtar(size_t n);
    ~Filmtar();

    void hozzaad(Film f);

    void torol(String cim);

    void listaz(std::ostream& os = std::cout) const;

    void rendez(bool evSzerint);

    int particional(int bal, int jobb, bool evSzerint);

    Film* keres(String kulcsszo) const;

    void ment(const char* path) const;

    void betolt(const char* path);
};

#endif