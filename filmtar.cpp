#include "filmtar.h"
#include <iostream>
#include <fstream>

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


void Filmtar::ment(const char* path) const {
    std::ofstream save_file;
    save_file.open(path, std::ios::app);

    for (size_t i = 0; i < adatok.size(); ++i) {
        save_file << adatok[i]->getCim().c_str() << ";" << adatok[i]->getEv() << ";" << adatok[i]->getHossz() << "|\n";
    }

    save_file.close();
}