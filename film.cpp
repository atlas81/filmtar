#include "film.h"


Film::Film(String s, int hossz, int ev) : cim(s), hossz(hossz), ev(ev), id(global_id++) {}

Film::Film(Film& f) : cim(f.cim), hossz(f.hossz), ev(f.ev) {}

String Film::getCim() const {return cim; }
int Film::getEv() const {return ev; }
int Film::getHossz() const { return hossz; }


void Film::kiir(std::ostream& os = std::cout) const {
    os << "Cim: " << cim.c_str() << ", kiadasi ev: " << ev << ", hossz(perc): " << hossz;
}




CsaladiFilm::CsaladiFilm(String s, int hossz, int ev, int korh) : Film(s, hossz, ev), korhatar(korh) {}


void CsaladiFilm::kiir(std::ostream& os = std::cout) const {
    os << "Cim: " << cim.c_str() << ", kiadasi ev: " << ev << ", hossz(perc): " << hossz << ", korhatas: " << korhatar;
}


Dokumentumfilm::Dokumentumfilm(String s, int hossz, int ev, String leir) : Film(s, hossz, ev), leiras(leir) {}

void Dokumentumfilm::kiir(std::ostream& os = std::cout) const {
    os << "Cim: " << cim.c_str() << ", kiadasi ev: " << ev << ", hossz(perc): " << hossz << ", leiras: " << leiras.c_str();
}