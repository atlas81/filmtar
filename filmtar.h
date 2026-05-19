#ifndef FILMTAR_H
#define FILMTAR_H

#include "film.h"
#include "array.hpp"

class Filmtar {
    public:
    Array<Film*> adatok;

    Filmtar(size_t n);
    ~Filmtar();

    void hozzaad(Film* f);

    void torol(String cim);

    void listaz(std::ostream& os = std::cout) const;

    void rendez(bool evSzerint);

    int particional(int bal, int jobb, bool evSzerint);

    Film* keres(String kulcsszo) const;

    Film* keres(int ev) const;

    void ment(const char* path) const;

    void betolt(const char* path);

    private:
    void rendezSegito(int bal, int jobb, bool evSzerint);
};

#endif