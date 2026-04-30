#ifndef FILM_H
#define FILM_H

#include "_string.h"
#include <iostream>

class Film {
    String cim;
    int hossz, ev, id;

    public:

    Film(String s, int hossz, int ev);
    ~Film();

    String getCim();
    int getEv();

    virtual void kiir(std::ostream& os = std::cout) const;
    virtual void mentes(const char* path) const;
};


class CsaladiFilm : public Film {
    int korhatar;
    
    public:
    CsaladiFilm(String s, int hossz, int ev, int korh);

    void kiir(std::ostream& os = std::cout) const override;
    void mentes(const char* path) const override;
};


class Dokumentumfilm : public Film {
    String leiras;

    public:
    Dokumentumfilm(String s, int hossz, int ev, String leir);
    
    void kiir(std::ostream& os = std::cout) const override;
    void mentes(const char* path) const override;
};

#endif