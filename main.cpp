#include "filmtar.h"
#include "array.hpp"
#include "_string.h"
#include "film.h"
#include <iostream>

int szamBeolvas() {
    int ertek;
    while (!(std::cin >> ertek)) {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        std::cout << "Hibas bemenet! Kerem adjon meg egy szamot: ";
    }
    std::cin.ignore(1024, '\n');
    return ertek;
}

String szovegBeolvas() {
    char puffer[1024];
    std::cin.getline(puffer, sizeof(puffer));
    return String(puffer);
}

void filmekListazasa(Filmtar& tar) {
    std::cout << "\n=== Filmek Listazasa ===" << std::endl;
    tar.listaz(std::cout);
}

void keresescim(Filmtar& tar) {
    std::cout << "\n=== Kereses cim alapjan ===" << std::endl;
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
}

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

int main() {
    Filmtar tar(100);
    
    try {
        tar.betolt("filmek.txt");
        std::cout << "Adatok betoltve a filmek.txt fajlbol." << std::endl;
    } catch (const char* e) {
        std::cout << "Az adatfajl nem letezik vagy az olvasas sikertelen. Ures adatbazissal indulunk." << std::endl;
    }
    
    int valasztas = 0;
    
    while (valasztas != 7) {
        std::cout << "\n====== FILMTAR NYILVANTARTO RENDSZER ======" << std::endl;
        std::cout << "1. Filmek listazasa" << std::endl;
        std::cout << "2. Kereses cim alapjan" << std::endl;
        std::cout << "3. Uj film hozzaadasa" << std::endl;
        std::cout << "4. Film torlese" << std::endl;
        std::cout << "5. Filmek rendezese" << std::endl;
        std::cout << "6. Adatok mentese" << std::endl;
        std::cout << "7. Kilepes" << std::endl;
        std::cout << "Valasztasa (1-7): ";
        
        valasztas = szamBeolvas();
        
        switch (valasztas) {
            case 1:
                for (int i = 0; i < 100; ++i) std::cout << '\n';
                filmekListazasa(tar);
                break;
            case 2:
                for (int i = 0; i < 100; ++i) std::cout << '\n';
                keresescim(tar);
                break;
            case 3:
                for (int i = 0; i < 100; ++i) std::cout << '\n';
                ujFilmHozzaadasa(tar);
                break;
            case 4:
                for (int i = 0; i < 100; ++i) std::cout << '\n';
                filmTorlese(tar);
                break;
            case 5:
                for (int i = 0; i < 100; ++i) std::cout << '\n';
                filmekRendezese(tar);
                break;
            case 6:
                for (int i = 0; i < 100; ++i) std::cout << '\n';
                tar.ment("filmek.txt");
                std::cout << "Adatok elmentve." << std::endl;
                break;
            case 7:
                break;

            
            default:
                std::cout << "Hibas valasztas! Kerem valasszon 1-6 kozul." << std::endl;
        }
    }
    
    return 0;
}