#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "filmtar.h"
#include "film.h"
#include "_string.h"
#include "array.hpp"

/*

Forditásnál a main.cpp-t kell erre a fájlra cserélni es hozzaadni a -DRUN_TESTS flaget, ha a teszteket akarjuk látni

g++ -Wall -Werror -Wpedantic -std=c++11 -DMEMTRACE -DRUN_TESTS _string.cpp film.cpp filmtar.cpp memtrace.cpp test.cpp -o test
*/

// ===== SEGÉDFÜGGVÉNYEK =====

int sikeres_tesztek = 0;
int sikertelen_tesztek = 0;

void teszt_eredmeny(const char* teszt_neve, bool eredmeny) {
    if (eredmeny) {
        std::cout << "[OK] " << teszt_neve << std::endl;
        sikeres_tesztek++;
    } else {
        std::cout << "[HIBA] " << teszt_neve << std::endl;
        sikertelen_tesztek++;
    }
}

// ===== STRING TESZTEK  =====

void string_konstruktor_ures() {
    // Üres konstruktor teszt
    String szoveg;
    teszt_eredmeny("String_ures_konstruktor", szoveg.size() == 0);
}

void string_konstruktor_char() {
    // Karakterbol konstruktor
    String szoveg('a');
    teszt_eredmeny("String_char_konstruktor", szoveg.size() == 1 && szoveg[0] == 'a');
}

void string_konstruktor_cstring() {
    String szoveg("hello");
    teszt_eredmeny("String_cstring_konstruktor", szoveg.size() == 5 && szoveg[0] == 'h');
}

void string_konstruktor_masolas() {
    String s1("test");
    String s2(s1);
    teszt_eredmeny("String_masolas_konstruktor", s2.size() == 4 && s2 == s1);
}

void string_egyenloseg_igaz() {
    String s1("abc");
    String s2("abc");
    teszt_eredmeny("String_egyenloseg_igaz", s1 == s2);
}

void string_egyenloseg_hamis() {
    String s1("abc");
    String s2("abd");
    teszt_eredmeny("String_egyenloseg_hamis", !(s1 == s2));
}

void string_kisebb_igaz() {
    String s1("abc");
    String s2("abd");
    teszt_eredmeny("String_kisebb_igaz", s1 < s2);
}

void string_kisebb_hamis() {
    String s1("abd");
    String s2("abc");
    teszt_eredmeny("String_kisebb_hamis", !(s1 < s2));
}

void string_kisebb_azonos() {
    String s1("abc");
    String s2("abc");
    teszt_eredmeny("String_kisebb_azonos", !(s1 < s2));
}

void string_kisebb_hossz() {
    String s1("ab");
    String s2("abc");
    teszt_eredmeny("String_kisebb_hossz", s1 < s2);
}

void string_plus_char() {
    String s = String("abc") + '!';
    teszt_eredmeny("String_plus_char", s.size() == 4 && s[3] == '!');
}

void string_plus_string() {
    String s = String("hello") + String(" world");
    teszt_eredmeny("String_plus_string", s.size() == 11);
}

void string_index_eleres() {
    String s("test");
    teszt_eredmeny("String_index_eleres", s[0] == 't' && s[3] == 't');
}

void string_egy_karakter() {
    String s("a");
    teszt_eredmeny("String_egy_karakter", s.size() == 1);
}

void string_hosszu() {
    String s("12345678901234567890");
    teszt_eredmeny("String_hosszu", s.size() == 20);
}

void string_szokozzel() {
    String s("hello world");
    teszt_eredmeny("String_szokozzel", s.size() == 11);
}

void string_pontosvesszovel() {
    String s("test;data");
    teszt_eredmeny("String_pontosvesszovel", s.size() == 9);
}

// ===== FILM TESZTEK =====

void film_alapkonstruktor() {
    Film film(String("Terminator"), 107, 1991);
    teszt_eredmeny("Film_alapkonstruktor", 
        film.getCim() == String("Terminator") && 
        film.getHossz() == 107 && 
        film.getEv() == 1991);
}

void film_gettipus() {
    Film film(String("Test"), 100, 2000);
    teszt_eredmeny("Film_getTipus", film.getTipus() == 'T');
}

void film_kiir() {
    Film film(String("Matrix"), 136, 1999);
    std::stringstream ss;
    film.kiir(ss);
    std::string kimenet = ss.str();
    teszt_eredmeny("Film_kiir", !kimenet.empty());
}

void csaladi_film_alapkonstruktor() {
    CsaladiFilm cf(String("Shrek"), 90, 2001, 6);
    teszt_eredmeny("CsaladiFilm_alapkonstruktor",
        cf.getCim() == String("Shrek") &&
        cf.getHossz() == 90 &&
        cf.getEv() == 2001);
}

void csaladi_film_gettipus() {
    CsaladiFilm cf(String("Toy Story"), 81, 1995, 3);
    teszt_eredmeny("CsaladiFilm_getTipus", cf.getTipus() == 'C');
}

void csaladi_film_kiir() {
    CsaladiFilm cf(String("Frozen"), 102, 2013, 6);
    std::stringstream ss;
    cf.kiir(ss);
    std::string kimenet = ss.str();
    teszt_eredmeny("CsaladiFilm_kiir_tartalmaz", kimenet.find("6") != std::string::npos);
}

void dokumentum_film_alapkonstruktor() {
    Dokumentumfilm df(String("Planet Earth"), 60, 2016, String("Nature"));
    teszt_eredmeny("DokumentumFilm_alapkonstruktor",
        df.getCim() == String("Planet Earth") &&
        df.getHossz() == 60);
}

void dokumentum_film_gettipus() {
    Dokumentumfilm df(String("Blue Planet"), 50, 2001, String("Ocean"));
    teszt_eredmeny("DokumentumFilm_getTipus", df.getTipus() == 'D');
}

// ===== FILMTÁR TESZTEK =====

void filmtar_hozzaad() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("Avatar"), 162, 2009));
    tar.hozzaad(new Film(String("Inception"), 148, 2010));
    teszt_eredmeny("Filmtar_hozzaadas", tar.getSize() == 2);
}

void filmtar_keres_cim() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("Avatar"), 162, 2009));
    Film* talalt = tar.keres(String("Avatar"));
    teszt_eredmeny("Filmtar_keres_cim",
        talalt != nullptr &&
        talalt->getCim() == String("Avatar"));
}

void filmtar_keres_ev() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("Inception"), 148, 2010));
    Array<int> talalat(1);
    Film* talalt = tar.keres(2010, talalat);
    teszt_eredmeny("Filmtar_keres_ev",
        talalt != nullptr &&
        talalt->getEv() == 2010);
}

void filmtar_keres_nem_talalt_cim() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("Titanic"), 194, 1997));
    Film* nemTalalt = tar.keres(String("NonExistent"));
    teszt_eredmeny("Filmtar_keres_nem_talalt_cim", nemTalalt == nullptr);
}

void filmtar_keres_nem_talalt_ev() {
    Filmtar tar(10);
    Array<int> talalat(1);
    tar.hozzaad(new Film(String("Test"), 100, 2000));
    Film* nemTalalt = tar.keres(1900, talalat);
    teszt_eredmeny("Filmtar_keres_nem_talalt_ev", nemTalalt == nullptr);
}

void filmtar_torol() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("Test1"), 100, 2000));
    tar.hozzaad(new Film(String("Test2"), 110, 2001));
    
    bool korabbi = tar.getSize() == 2;
    tar.torol(String("Test1"));
    bool utana = tar.getSize() == 1;
    
    Film* torlott = tar.keres(String("Test1"));
    teszt_eredmeny("Filmtar_torles", korabbi && utana && torlott == nullptr);
}

void filmtar_rendez_ev() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("B"), 100, 2000));
    tar.hozzaad(new Film(String("A"), 100, 1999));
    tar.hozzaad(new Film(String("C"), 100, 2001));
    
    tar.rendez(true);
    
    teszt_eredmeny("Filmtar_rendez_ev",
        tar[tar.at_idx(0)]->getEv() == 1999 &&
        tar[tar.at_idx(1)]->getEv() == 2000 &&
        tar[tar.at_idx(2)]->getEv() == 2001);
}

void filmtar_rendez_cim() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("Zebra"), 100, 2000));
    tar.hozzaad(new Film(String("Apple"), 100, 1999));
    tar.hozzaad(new Film(String("Monkey"), 100, 2001));
    
    tar.rendez(false);
    
    teszt_eredmeny("Filmtar_rendez_cim",
        tar[tar.at_idx(0)]->getCim() == String("Apple") &&
        tar[tar.at_idx(1)]->getCim() == String("Monkey") &&
        tar[tar.at_idx(2)]->getCim() == String("Zebra"));
}

void filmtar_rendez_ures() {
    Filmtar tar(5);
    tar.rendez(true);
    teszt_eredmeny("Filmtar_rendez_ures", tar.getSize() == 0);
}

void filmtar_rendez_egy() {
    Filmtar tar(5);
    tar.hozzaad(new Film(String("Only"), 100, 2000));
    tar.rendez(false);
    teszt_eredmeny("Filmtar_rendez_egy", tar.getSize() == 1);
}

void filmtar_rendez_ketto() {
    Filmtar tar(5);
    tar.hozzaad(new Film(String("Z"), 100, 2000));
    tar.hozzaad(new Film(String("A"), 100, 1999));
    tar.rendez(false);
    teszt_eredmeny("Filmtar_rendez_ketto", tar[tar.at_idx(0)]->getCim() == String("A"));
}

void filmtar_kevert_tipusok() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("Film1"), 100, 2000));
    tar.hozzaad(new CsaladiFilm(String("Family"), 90, 2001, 6));
    tar.hozzaad(new Dokumentumfilm(String("Doc"), 50, 2002, String("leiras")));
    
    teszt_eredmeny("Filmtar_kevert_tipusok",
        tar.getSize() == 3 &&
        tar[0]->getTipus() == 'T' &&
        tar[1]->getTipus() == 'C' &&
        tar[2]->getTipus() == 'D');
}

void filmtar_kevert_rendez() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("B"), 100, 2000));
    tar.hozzaad(new CsaladiFilm(String("A"), 90, 1999, 6));
    tar.hozzaad(new Dokumentumfilm(String("C"), 50, 2001, String("d")));
    
    tar.rendez(true);
    teszt_eredmeny("Filmtar_kevert_rendez", tar[tar.at_idx(0)]->getEv() == 1999);
}

void filmtar_listaz() {
    Filmtar tar(5);
    tar.hozzaad(new Film(String("Titanic"), 194, 1997));
    tar.hozzaad(new Film(String("Avatar"), 162, 2009));
    
    std::stringstream ss;
    tar.listaz(ss);
    std::cout << std::endl;
    std::string kimenet = ss.str();
    
    teszt_eredmeny("Filmtar_listazas", !kimenet.empty());
}

// ===== TÖMB TESZTEK =====

void tomb_push_back() {
    Array<int> tomb(10);
    int a = 5;
    int b = 10;
    int c = 15;
    tomb.push_back(a);
    tomb.push_back(b);
    tomb.push_back(c);
    
    teszt_eredmeny("Tomb_push_back",
        tomb.size() == 3 &&
        tomb[0] == 5 &&
        tomb[1] == 10 &&
        tomb[2] == 15);
}

void tomb_remove() {
    Array<int> tomb(10);
    int x = 1;
    int y = 2;
    int z = 3;
    tomb.push_back(x);
    tomb.push_back(y);
    tomb.push_back(z);
    
    tomb.remove(y);
    
    teszt_eredmeny("Tomb_remove",
        tomb.size() == 2 &&
        tomb[0] == 1 &&
        tomb[1] == 3);
}

// ===== FILE I/O TESZTEK =====

void fajl_ment() {
    Filmtar tar(5);
    tar.hozzaad(new Film(String("Test"), 100, 2000));
    tar.hozzaad(new CsaladiFilm(String("Family"), 90, 2001, 6));
    
    tar.ment("test_io.txt");
    
    std::ifstream fajl("test_io.txt");
    bool letezik = fajl.good();
    fajl.close();
    
    remove("test_io.txt");
    teszt_eredmeny("Fajl_ment", letezik);
}

void fajl_betolt_nem_letezik() {
    Filmtar tar(5);
    
    bool kivetel_lepett_fel = false;
    try {
        tar.betolt("nonexistent_xyz.txt");
    } catch (const std::runtime_error& e) {
        kivetel_lepett_fel = true;
    }
    
    teszt_eredmeny("Fajl_betolt_nem_letezik", kivetel_lepett_fel);
}

// ===== VALIDÁCIÓ TESZTEK =====

void validacio_evtartomany() {
    Film f1(String("Test"), 100, 1800);
    Film f2(String("Test"), 100, 2026);
    
    teszt_eredmeny("Validacio_evtartomany",
        f1.getEv() == 1800 &&
        f2.getEv() == 2026);
}

void validacio_hossz() {
    Film f1(String("Test"), 1, 2000);
    Film f2(String("Test"), 1000, 2000);
    
    teszt_eredmeny("Validacio_hossz",
        f1.getHossz() == 1 &&
        f2.getHossz() == 1000);
}

void validacio_korhatar() {
    CsaladiFilm f1(String("Test"), 100, 2000, 0);
    CsaladiFilm f2(String("Test"), 100, 2000, 18);
    
    teszt_eredmeny("Validacio_korhatar",
        f1.getEv() == 2000 &&
        f2.getEv() == 2000);
}

// ===== PEREMFELTÉTEL TESZTEK =====

void perem_ures_cim() {
    String ures("");
    Film f(ures, 100, 2000);
    
    teszt_eredmeny("Perem_ures_cim", f.getCim().size() == 0);
}

void perem_specialis_karakterek() {
    String s1("Test;String;With;Semicolons");
    String s2("Test|String|With|Pipes");
    
    teszt_eredmeny("Perem_specialis_karakterek",
        s1.size() == 27 &&
        s2.size() == 22);
}

void perem_duplikalt_keres() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("Duplicate"), 100, 2000));
    tar.hozzaad(new Film(String("Duplicate"), 110, 2001));
    tar.hozzaad(new Film(String("Other"), 120, 2002));
    
    Film* talalt = tar.keres(String("Duplicate"));
    teszt_eredmeny("Perem_duplikalt_keres",
        talalt != nullptr &&
        talalt->getHossz() == 100);
}

void film_modositas_test() {
    // Film::modosit olvassa a stdin-t; ideiglenesen atiranyitjuk cin-t
    Film f(String("Regi Cim"), 100, 2000);
    std::streambuf* cin_buf = std::cin.rdbuf();
    std::istringstream input("Uj Cim\n120\n2010\n");
    std::cin.rdbuf(input.rdbuf());
    f.modosit();
    std::cout << std::endl;
    std::cin.rdbuf(cin_buf);

    teszt_eredmeny("Film_modositas", f.getCim() == String("Uj Cim") && f.getHossz() == 120 && f.getEv() == 2010);
}

void filmtar_kategoria_kereses() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("F1"), 100, 2000));
    tar.hozzaad(new CsaladiFilm(String("Family"), 90, 2001, 6));
    tar.hozzaad(new Dokumentumfilm(String("Doc"), 50, 2002, String("desc")));

    Film* t1 = tar.keres('C');
    Film* t2 = tar.keres('D');

    teszt_eredmeny("filmtar_kategoria_kereses_C", t1 != nullptr && t1->getTipus() == 'C');
    teszt_eredmeny("filmtar_kategoria_kereses_D", t2 != nullptr && t2->getTipus() == 'D');
}

void filmtar_betolt_helyes_file() {
    const char* fname = "test_load_ok.txt";
    std::ofstream of(fname);
    of << "T;Good;100;2000|\n";
    of << "C;Family;90;2001;6|\n";
    of << "D;Doc;50;2010;Desc|\n";
    of.close();

    Filmtar tar(10);
    try {
        tar.betolt(fname);
        bool ok = (tar.getSize() == 3) && (tar.keres(String("Good")) != nullptr) && (tar.keres('C') != nullptr) && (tar.keres('D') != nullptr);
        teszt_eredmeny("filmtar_betolt_helyes_file", ok);
    } catch (const std::runtime_error& e) {
        teszt_eredmeny("filmtar_betolt_helyes_file", false);
    }

    remove(fname);
}

void filmtar_ment_betolt_kompatibilis() {
    const char* fajlnev = "test_ment_betolt.txt";
    Filmtar tar1(10);
    tar1.hozzaad(new Film(String("Good"), 100, 2000));
    tar1.hozzaad(new CsaladiFilm(String("Family"), 90, 2001, 6));
    tar1.hozzaad(new Dokumentumfilm(String("Doc"), 50, 2010, String("Desc")));
    tar1.ment(fajlnev);

    Filmtar tar2(10);
    bool siker = false;
    try {
        tar2.betolt(fajlnev);
        siker = (tar2.getSize() == 3) &&
                (tar2.keres(String("Good")) != nullptr) &&
                (tar2.keres('C') != nullptr) &&
                (tar2.keres('D') != nullptr);
    } catch (const std::runtime_error& e) {
        siker = false;
    }

    remove(fajlnev);
    teszt_eredmeny("Filmtar_ment_betolt_kompatibilis", siker);
}

void filmtar_betolt_helytelen_file() {
    const char* fname = "test_load_helytelen_file.txt";
    std::ofstream of(fname);
    of << "T;Good;100;2000|\n";
    of << "X;helytelensor\n";
    of.close();

    Filmtar tar(10);
    try {
        tar.betolt(fname);
        bool ok = (tar.getSize() == 1) && (tar.keres(String("Good")) != nullptr);
        teszt_eredmeny("Filmtar_betolt_helytelen_file", ok);
    } catch (const std::runtime_error& e) {
        teszt_eredmeny("Filmtar_betolt_helytelen_file", false);
    }

    remove(fname);
}

void filmtar_torles_nev() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("D1"), 100, 2000));
    tar.hozzaad(new Film(String("D2"), 110, 2001));
    size_t before = tar.getSize();
    tar.torol(String("D1"));
    size_t after = tar.getSize();
    Film* f = tar.keres(String("D1"));
    teszt_eredmeny("filmtar_torles_nev", before == 2 && after == 1 && f == nullptr);
}

void perem_ugyanaz_cim_kulonbozo_ev() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("Dracula"), 100, 1931));
    tar.hozzaad(new Film(String("Dracula"), 120, 1992));
    
    Film* talalt = tar.keres(String("Dracula"));
    teszt_eredmeny("Perem_ugyanaz_cim_kulonbozo_ev",
        talalt != nullptr &&
        talalt->getEv() == 1931);
}

void perem_azonos_evek_rendezes() {
    Filmtar tar(10);
    tar.hozzaad(new Film(String("C"), 100, 2000));
    tar.hozzaad(new Film(String("A"), 100, 2000));
    tar.hozzaad(new Film(String("B"), 100, 2000));
    
    tar.rendez(true);
    teszt_eredmeny("Perem_azonos_evek_rendezes",
        tar.getSize() == 3 &&
        tar[0]->getEv() == 2000);
}

void perem_hosszu_cim() {
    String hosszuCim("Esetlegesen nagyon hosszu cimu film, cimenek tarolasanak helyessegenek ellenorzesere szolgalo tesztsor");
    Film f(hosszuCim, 150, 2020);
    
    teszt_eredmeny("Perem_hosszu_cim", f.getCim() == hosszuCim);
}

// A tesztfuttato main csak akkor legyen benne, ha kifejezetten teszteket fordítunk.

#ifdef CPORTA
int main() {
    std::cout << "========== TESZTEK INDITASA ==========" << std::endl << std::endl;
    
    std::cout << "--- String tesztek ---" << std::endl;
    string_konstruktor_ures();
    string_konstruktor_char();
    string_konstruktor_cstring();
    string_konstruktor_masolas();
    string_egyenloseg_igaz();
    string_egyenloseg_hamis();
    string_kisebb_igaz();
    string_kisebb_hamis();
    string_kisebb_azonos();
    string_kisebb_hossz();
    string_plus_char();
    string_plus_string();
    string_index_eleres();
    string_egy_karakter();
    string_hosszu();
    string_szokozzel();
    string_pontosvesszovel();
    std::cout << std::endl;
    
    std::cout << "--- Film tesztek ---" << std::endl;
    film_alapkonstruktor();
    film_gettipus();
    film_kiir();
    csaladi_film_alapkonstruktor();
    csaladi_film_gettipus();
    csaladi_film_kiir();
    dokumentum_film_alapkonstruktor();
    dokumentum_film_gettipus();
    std::cout << std::endl;
    
    std::cout << "--- Filmtar tesztek ---" << std::endl;
    filmtar_hozzaad();
    filmtar_keres_cim();
    filmtar_keres_ev();
    filmtar_keres_nem_talalt_cim();
    filmtar_keres_nem_talalt_ev();
    filmtar_torol();
    filmtar_rendez_ev();
    filmtar_rendez_cim();
    filmtar_rendez_ures();
    filmtar_rendez_egy();
    filmtar_rendez_ketto();
    filmtar_kevert_tipusok();
    filmtar_kevert_rendez();
    filmtar_listaz();
    std::cout << std::endl;

    film_modositas_test();
    filmtar_kategoria_kereses();
    filmtar_betolt_helyes_file();
    filmtar_betolt_helytelen_file();
    filmtar_torles_nev();
    
    std::cout << "--- Tomb tesztek ---" << std::endl;
    tomb_push_back();
    tomb_remove();
    std::cout << std::endl;
    
    std::cout << "--- Fajl I/O tesztek ---" << std::endl;
    fajl_ment();
    filmtar_ment_betolt_kompatibilis();
    fajl_betolt_nem_letezik();
    std::cout << std::endl;
    
    std::cout << "--- Validacio tesztek ---" << std::endl;
    validacio_evtartomany();
    validacio_hossz();
    validacio_korhatar();
    std::cout << std::endl;
    
    std::cout << "--- Peremfeltetel tesztek ---" << std::endl;
    perem_ures_cim();
    perem_specialis_karakterek();
    perem_duplikalt_keres();
    perem_ugyanaz_cim_kulonbozo_ev();
    perem_azonos_evek_rendezes();
    perem_hosszu_cim();
    std::cout << std::endl;
    
    std::cout << "========== TESZT OSSZEFOGLALO ==========" << std::endl;
    std::cout << "Hibas/Osszes: " << sikertelen_tesztek << "/" << (sikeres_tesztek + sikertelen_tesztek) << std::endl;
    
    return sikertelen_tesztek == 0 ? 0 : 1;
}
#endif
