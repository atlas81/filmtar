#include "filmtar.h"
#include "array.hpp"
#include "_string.h"
#include "film.h"
#include <iostream>
#include "memtrace.h"

// g++ -Wall -Werror -Wpedantic -std=c++11 -DMEMTRACE _string.cpp main.cpp film.cpp filmtar.cpp memtrace.cpp -o outp

// szám beolvasás ellenőrzéssel
int szamBeolvas() {
    int ertek;
    while (true) {
        if (std::cin >> ertek) {
            std::cin.ignore(1024, '\n');
            return ertek;
        }

        if (std::cin.eof()) {
            return 8;
        }

        std::cin.clear();
        std::cin.ignore(1024, '\n');
        std::cout << "Hibas bemenet! Kerem adjon meg egy szamot: ";
    }
}

// szöveg beolvasás (sor)
String szovegBeolvas() {
    char puffer[1024];
    std::cin.getline(puffer, sizeof(puffer));
    return String(puffer);
}

// összes film listázása
void filmekListazasa(Filmtar& tar) {
    std::cout << "\n=== Filmek Listazasa ===" << std::endl;
    tar.listaz(std::cout);
}

// keresés: cím, év vagy kategória alapján
void kereses(Filmtar& tar) {
    std::cout << "\n=== Kereses ===" << std::endl;
    std::cout << "1. Kereses cim alapjan" << std::endl;
    std::cout << "2. Kereses ev alapjan" << std::endl;
    std::cout << "3. Kereses kategoria alapjan" << std::endl;
    std::cout << "Valasztasa (1-3): ";
    
    int keresModul = szamBeolvas();
    
    if (keresModul == 1) {
        std::cout << "Kerem a keresett film cimet: ";
        String keresettCim = szovegBeolvas();
        
        Film* talalt = tar.keres(keresettCim);
        
        if (talalt != nullptr) {
            std::cout << "Megtalalt film:" << std::endl;
            talalt->kiir(std::cout);
            std::cout << std::endl;
        } else {
            std::cout << "Film nem talalhato!" << std::endl;
        }
    } else if (keresModul == 2) {
        std::cout << "Kerem az ev szamot: ";
        int keresettEv = szamBeolvas();

        Film* talalt = tar.keres(keresettEv);
        
        if (talalt != nullptr) {
            std::cout << "Megtalalt film:" << std::endl;
            talalt->kiir(std::cout);
            std::cout << std::endl;
        } else {
            std::cout << "Film nem talalhato!" << std::endl;
        }

    } else if (keresModul == 3) {
        std::cout << "1. Alap film" << std::endl;
        std::cout << "2. Csaladi film" << std::endl;
        std::cout << "3. Dokumentumfilm" << std::endl;
        std::cout << "Valasztasa (1-3): ";
        
        int kateg = szamBeolvas();
        char keresettTipus;
        
        if (kateg == 1) keresettTipus = 'T';
        else if (kateg == 2) keresettTipus = 'C';
        else if (kateg == 3) keresettTipus = 'D';
        else return;
        
        Film* talalt = tar.keres(keresettTipus);
        
        if (talalt != nullptr) {
            std::cout << "Megtalalt film:" << std::endl;
            talalt->kiir(std::cout);
            std::cout << std::endl;
        } else {
            std::cout << "Film nem talalhato!" << std::endl;
        }
    } else {
        std::cout << "Hibas valasztas!" << std::endl;
    }
}

// új film hozzáadása (típússsal)
void ujFilmHozzaadasa(Filmtar& tar) {
    std::cout << "\n=== Uj Film Hozzaadasa ===" << std::endl;
    std::cout << "Valasszon film tipust:" << std::endl;
    std::cout << "1. Alap film" << std::endl;
    std::cout << "2. Csaladi film" << std::endl;
    std::cout << "3. Dokumentumfilm" << std::endl;
    std::cout << "Valasztasa (1-3): ";
    
    int tipus = szamBeolvas();
    
    std::cout << "Cimet kerem: ";
    String cim = szovegBeolvas();
    
    std::cout << "Hosszat (percben) kerem: ";
    int hossz = szamBeolvas();
    
    if (hossz < 0) {
        std::cout << "Hibas hossz! Kerem adjon meg pozitiv erteket." << std::endl;
        return;
    }
    
    std::cout << "Evszamot kerem: ";
    int ev = szamBeolvas();
    
    if (ev < 1800 || ev > 2026) {
        std::cout << "Hibas evszam! Kerem adjon meg 1800 es 2026 kozotti erteket." << std::endl;
        return;
    }
    
    if (tipus == 1) {
        Film* ujFilm = new Film(cim, hossz, ev);
        tar.hozzaad(ujFilm);
        std::cout << "Film sikeresen hozzaadva!" << std::endl;
    } else if (tipus == 2) {
        std::cout << "Korhatart kerem: ";
        int korhatar = szamBeolvas();
        
        if (korhatar < 0 || korhatar > 18) {
            std::cout << "Hibas korhatar! Kerem adjon meg 0 es 18 kozotti erteket." << std::endl;
            return;
        }
        
        CsaladiFilm* ujFilm = new CsaladiFilm(cim, hossz, ev, korhatar);
        tar.hozzaad(ujFilm);
        std::cout << "Csaladi film sikeresen hozzaadva!" << std::endl;
    } else if (tipus == 3) {
        std::cout << "Leirast kerem: ";
        String leiras = szovegBeolvas();
        
        Dokumentumfilm* ujFilm = new Dokumentumfilm(cim, hossz, ev, leiras);
        tar.hozzaad(ujFilm);
        std::cout << "Dokumentumfilm sikeresen hozzaadva!" << std::endl;
    } else {
        std::cout << "Hibas valasztas!" << std::endl;
    }
}

// film törlése
void filmTorlese(Filmtar& tar) {
    std::cout << "\n=== Film Torlese ===" << std::endl;
    std::cout << "Kerem a torlendo film cimet: ";
    String cim = szovegBeolvas();
    
    Film* talalt = tar.keres(cim);
    
    if (talalt != nullptr) {
        tar.torol(cim);
        std::cout << "Film sikeresen torolve!" << std::endl;
    } else {
        std::cout << "Film nem talalhato!" << std::endl;
    }
}

// film módosítása
void filmModositasa(Filmtar& tar) {
    std::cout << "\n=== Film Modositasa ===" << std::endl;
    std::cout << "Kerem a modositando film cimet: ";
    String cim = szovegBeolvas();
    
    Film* talalt = tar.keres(cim);
    
    if (talalt != nullptr) {
        talalt->modosit();
        std::cout << "Film sikeresen modositva!" << std::endl;
    } else {
        std::cout << "Film nem talalhato!" << std::endl;
    }
}

// filmek rendezése (év vagy cím szerint)
void filmekRendezese(Filmtar& tar) {
    std::cout << "\n=== Filmek Rendezese ===" << std::endl;
    std::cout << "Rendezesi mod:" << std::endl;
    std::cout << "1. Evszam szerint" << std::endl;
    std::cout << "2. Cim szerint" << std::endl;
    std::cout << "Valasztasa (1-2): ";
    
    int mod = szamBeolvas();
    
    if (mod == 1) {
        tar.rendez(true);
        std::cout << "Rendezve evszam szerint!" << std::endl;
    } else if (mod == 2) {
        tar.rendez(false);
        std::cout << "Rendezve cim szerint!" << std::endl;
    } else {
        std::cout << "Hibas valasztas!" << std::endl;
    }
}

// fő menu
#ifndef CPORTA
int main() {
    Filmtar tar(100);
    
    try {
        tar.betolt("filmek.txt");
        std::cout << "Adatok betoltve a filmek.txt fajlbol." << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Az filmek.txt fajl nem letezik vagy olvasasa sikertelen. Ures adatbazissal indulunk." << std::endl;
    }
    
    int valasztas = 0;
    
    while (valasztas != 8) {
        std::cout << "\n====== FILMTAR ======" << std::endl;
        std::cout << "1. Filmek listazasa" << std::endl;
        std::cout << "2. Kereses" << std::endl;
        std::cout << "3. Uj film hozzaadasa" << std::endl;
        std::cout << "4. Film torlese" << std::endl;
        std::cout << "5. Film modositasa" << std::endl;
        std::cout << "6. Filmek rendezese" << std::endl;
        std::cout << "7. Adatok mentese" << std::endl;
        std::cout << "8. Kilepes" << std::endl;
        std::cout << "Valasztasa (1-8): ";
        
        valasztas = szamBeolvas();
        
        switch (valasztas) {
            case 1:
                filmekListazasa(tar);
                break;
            case 2:
                kereses(tar);
                break;
            case 3:
                ujFilmHozzaadasa(tar);
                break;
            case 4:
                filmTorlese(tar);
                break;
            case 5:
                filmModositasa(tar);
                break;
            case 6:
                filmekRendezese(tar);
                break;
            case 7:
                tar.ment("filmek.txt");
                std::cout << "Adatok elmentve!" << std::endl;
                break;
            case 8:
                break;
            default:
                std::cout << "Hibas valasztas! Kerem valasszon 1-8 kozul." << std::endl;
        }
    }
    
    return 0;
}
#endif