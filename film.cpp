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
    
    save_file << "T;" << cim.c_str() << ";" << hossz << ";" << ev << "|\n";
    
    save_file.close();
}

char Film::getTipus() const {
    return 'T';
}

void Film::modosit() {
    std::cout << "Modositas - Alap Film" << std::endl;
    std::cout << "Uj cim (jelenlegi: " << cim.c_str() << "): ";
    char cim_puffer[1024];
    std::cin.getline(cim_puffer, sizeof(cim_puffer));
    if (cim_puffer[0] != '\0') {
        cim = String(cim_puffer);
    }
    
    std::cout << "Uj hossz percben (jelenlegi: " << hossz << "): ";
    int uj_hossz;
    if (std::cin >> uj_hossz && uj_hossz > 0) {
        hossz = uj_hossz;
    }
    std::cin.ignore(1024, '\n');
    
    std::cout << "Uj evszam (jelenlegi: " << ev << "): ";
    int uj_ev;
    if (std::cin >> uj_ev && uj_ev >= 1800 && uj_ev <= 2100) {
        ev = uj_ev;
    }
    std::cin.ignore(1024, '\n');
}




CsaladiFilm::CsaladiFilm(String s, int hossz, int ev, int korh) : Film(s, hossz, ev), korhatar(korh) {}


void CsaladiFilm::kiir(std::ostream& os) const {
    os << "Cim: " << cim.c_str() << ", kiadasi ev: " << ev << ", hossz(perc): " << hossz << ", korhatas: " << korhatar;
}

void CsaladiFilm::mentes(const char* path) const {
    std::ofstream save_file;
    save_file.open(path, std::ios::app);
    
    save_file << "C;" << cim.c_str() << ";" << hossz << ";" << ev << ";" << korhatar << "|\n";
    
    save_file.close();
}

char CsaladiFilm::getTipus() const {
    return 'C';
}

void CsaladiFilm::modosit() {
    std::cout << "Modositas - Csaladi Film" << std::endl;
    std::cout << "Uj cim (jelenlegi: " << cim.c_str() << "): ";
    char cim_puffer[1024];
    std::cin.getline(cim_puffer, sizeof(cim_puffer));
    if (cim_puffer[0] != '\0') {
        cim = String(cim_puffer);
    }
    
    std::cout << "Uj hossz percben (jelenlegi: " << hossz << "): ";
    int uj_hossz;
    if (std::cin >> uj_hossz && uj_hossz > 0) {
        hossz = uj_hossz;
    }
    std::cin.ignore(1024, '\n');
    
    std::cout << "Uj evszam (jelenlegi: " << ev << "): ";
    int uj_ev;
    if (std::cin >> uj_ev && uj_ev >= 1800 && uj_ev <= 2026) {
        ev = uj_ev;
    }
    std::cin.ignore(1024, '\n');
    
    std::cout << "Uj korhatar (jelenlegi: " << korhatar << "): ";
    int uj_korhatar;
    if (std::cin >> uj_korhatar && uj_korhatar >= 0 && uj_korhatar <= 18) {
        korhatar = uj_korhatar;
    }
    std::cin.ignore(1024, '\n');
}


Dokumentumfilm::Dokumentumfilm(String s, int hossz, int ev, String leir) : Film(s, hossz, ev), leiras(leir) {}

void Dokumentumfilm::kiir(std::ostream& os) const {
    os << "Cim: " << cim.c_str() << ", kiadasi ev: " << ev << ", hossz(perc): " << hossz << ", leiras: " << leiras.c_str();
}

void Dokumentumfilm::mentes(const char* path) const {
    std::ofstream save_file;
    save_file.open(path, std::ios::app);
    
    save_file << "D;" << cim.c_str() << ";" << hossz << ";" << ev << ";" << leiras.c_str() << "|\n";
    
    save_file.close();
}

char Dokumentumfilm::getTipus() const {
    return 'D';
}

void Dokumentumfilm::modosit() {
    std::cout << "Modositas - Dokumentumfilm" << std::endl;
    std::cout << "Uj cim (jelenlegi: " << cim.c_str() << "): ";
    char cim_puffer[1024];
    std::cin.getline(cim_puffer, sizeof(cim_puffer));
    if (cim_puffer[0] != '\0') {
        cim = String(cim_puffer);
    }
    
    std::cout << "Uj hossz percben (jelenlegi: " << hossz << "): ";
    int uj_hossz;
    if (std::cin >> uj_hossz && uj_hossz > 0) {
        hossz = uj_hossz;
    }
    std::cin.ignore(1024, '\n');
    
    std::cout << "Uj evszam (jelenlegi: " << ev << "): ";
    int uj_ev;
    if (std::cin >> uj_ev && uj_ev >= 1800 && uj_ev <= 2026) {
        ev = uj_ev;
    }
    std::cin.ignore(1024, '\n');
    
    std::cout << "Uj leiras (jelenlegi: " << leiras.c_str() << "): ";
    char leiras_puffer[1024];
    std::cin.getline(leiras_puffer, sizeof(leiras_puffer));
    if (leiras_puffer[0] != '\0') {
        leiras = String(leiras_puffer);
    }
}