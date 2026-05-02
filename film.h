#ifndef FILM_H
#define FILM_H

#include "_string.h"
#include <iostream>

class Film {
    protected:
    String cim;
    int hossz, ev, id; 
    static int global_id;

    public:

    Film(String s, int hossz, int ev);
    Film(Film& f);

    String getCim() const;
    int getEv() const;
    int getHossz() const;

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