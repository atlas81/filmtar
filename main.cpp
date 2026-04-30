#include "filmtar.h"
#include "array.hpp"
#include "_string.h"
#include "film.h"
#include <iostream>


int main() {
    Filmtar tar;

    tar.betolt("filmek.txt");

    tar.hozzaad(new CsaladiFilm("Az oroszlánkirály", 88, 1994, 6));
    tar.hozzaad(new Dokumentumfilm("Random doku film", 120, 2000, "Random doku rovid leirasa"));

    tar.rendez(true);

    tar.listaz(std::cout);

    tar.torol("Az oroszlánkirály");

    tar.ment("filmek.txt");

    Film* keresett_film = tar.keres("Keresett film neve");

    if (keresett_film != nullptr)
        (*keresett_film).kiir(std::cout);
    
    return 0;
}