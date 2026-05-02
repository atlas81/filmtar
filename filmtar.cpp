#include "filmtar.h"

Filmtar::Filmtar(size_t n) : adatok(Array<Film*>(n)) {}

Filmtar::~Filmtar() {}


void Filmtar::hozzaad(Film f) {
    Film* temp = new Film(f);
    adatok.push_back(temp);
}


void Filmtar::torol(String cim) {
    Film* torlendo = keres(cim);
    adatok.remove(torlendo);
    delete torlendo;
}


Film* Filmtar::keres(String kulcsszo) const {
    for (size_t i = 0; i < adatok.size(); ++i) {
        if (adatok[i]->getCim() == kulcsszo) return adatok[i];
    } 
}


void Filmtar::listaz(std::ostream& os = std::cout) const {
    for (size_t i = 0; i < adatok.size(); ++i) {
        adatok[i]->kiir();
        os << std::endl;
    }
}


