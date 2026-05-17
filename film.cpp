#include "film.h"
#include <fstream>


Film::Film(String s, int hossz, int ev) : cim(s), hossz(hossz), ev(ev) {}

Film::Film(Film& f) : cim(f.cim), hossz(f.hossz), ev(f.ev) {}

String Film::getCim() const {return cim; }
int Film::getEv() const {return ev; }
int Film::getHossz() const { return hossz; }


void Film::kiir(std::ostream& os) const {
    os << "Cim: " << cim.c_str() << ", kiadasi ev: " << ev << ", hossz(perc): " << hossz;
}

void Film::mentes(const char* path) const {
    std::ofstream save_file;
    save_file.open(path, std::ios::app);
    
    save_file << cim.c_str() << ";" << ev << ";" << hossz << "|\n";
    
    save_file.close();
}




CsaladiFilm::CsaladiFilm(String s, int hossz, int ev, int korh) : Film(s, hossz, ev), korhatar(korh) {}


void CsaladiFilm::kiir(std::ostream& os) const {
    os << "Cim: " << cim.c_str() << ", kiadasi ev: " << ev << ", hossz(perc): " << hossz << ", korhatas: " << korhatar;
}

void CsaladiFilm::mentes(const char* path) const {
    std::ofstream save_file;
    save_file.open(path, std::ios::app);
    
    save_file << cim.c_str() << ";" << ev << ";" << hossz << ";" << korhatar << "|\n";
    
    save_file.close();
}


Dokumentumfilm::Dokumentumfilm(String s, int hossz, int ev, String leir) : Film(s, hossz, ev), leiras(leir) {}

void Dokumentumfilm::kiir(std::ostream& os) const {
    os << "Cim: " << cim.c_str() << ", kiadasi ev: " << ev << ", hossz(perc): " << hossz << ", leiras: " << leiras.c_str();
}

void Dokumentumfilm::mentes(const char* path) const {
    std::ofstream save_file;
    save_file.open(path, std::ios::app);
    
    save_file << cim.c_str() << ";" << ev << ";" << hossz << ";" << leiras.c_str() << "|\n";
    
    save_file.close();
}