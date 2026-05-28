#ifndef FILM_H
#define FILM_H

#include "_string.h"
#include <iostream>
#include "memtrace.h"

// Film alaposztály: cím, hossz, év tárol
class Film {
    protected:
    String cim;     // Film címe
    int hossz, ev;  // Hossz (percben), év

    public:
    Film(String s, int hossz, int ev);
    Film(Film& f);

    String getCim() const;
    int getEv() const;
    int getHossz() const;

    virtual void kiir(std::ostream& os = std::cout) const;      // Kiírás
    virtual void mentes(const char* path) const;                // Fájlba mentés
    virtual char getTipus() const;                              // Film típust adja vissza (a mentéshez kell)
    virtual void modosit();                                     // Módosítás
    virtual ~Film() {}
};

// Családi film: korhatárral
class CsaladiFilm : public Film {
    int korhatar;
    
    public:
    CsaladiFilm(String s, int hossz, int ev, int korh);

    void kiir(std::ostream& os = std::cout) const override;
    void mentes(const char* path) const override;
    char getTipus() const override;
    void modosit() override;
};

// Dokumentumfilm: leírással
class Dokumentumfilm : public Film {
    String leiras;

    public:
    Dokumentumfilm(String s, int hossz, int ev, String leir);
    
    void kiir(std::ostream& os = std::cout) const override;
    void mentes(const char* path) const override;
    char getTipus() const override;
    void modosit() override;
};

#endif