#include "filmtar.h"
#include <iostream>
#include <fstream>
#include "_string.h"

Filmtar::Filmtar(size_t n) : adatok(Array<Film*>(n)) {}

Filmtar::~Filmtar() {}


void Filmtar::hozzaad(Film* f) {
    adatok.push_back(f);
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
    return nullptr;
}


Film* Filmtar::keres(int ev) const {
    for (size_t i = 0; i < adatok.size(); ++i) {
        if (adatok[i]->getEv() == ev) return adatok[i];
    }
    return nullptr;
}


void Filmtar::listaz(std::ostream& os) const {
    for (size_t i = 0; i < adatok.size(); ++i) {
        adatok[i]->kiir();
        os << std::endl;
    }
}


void Filmtar::ment(const char* path) const {
    std::ofstream save_file;
    save_file.open(path, std::ios::out);
    save_file.close();

    for (size_t i = 0; i < adatok.size(); ++i) {
        adatok[i]->mentes(path);
    }
}


void Filmtar::betolt(const char* path) {
    std::ifstream save_file;
    save_file.open(path, std::ios::in);

    if (!save_file.is_open()) throw "Filmtar::betolt fajl nincs megnyitva";

    char sor[1024];

    while(save_file.getline(sor, sizeof(sor))) {
        if (sor[0] == '\0') continue;
        
        char tipus = sor[0];
        
        int elso_valaszto = -1, masodik_valaszto = -1, harmadik_valaszto = -1, negyedik_valaszto = -1, pipe = -1;
        
        for (int i = 1; sor[i] != '\0'; ++i) {
            if (sor[i] == ';') {
                if (elso_valaszto == -1) {
                    elso_valaszto = i;
                } else if (masodik_valaszto == -1) {
                    masodik_valaszto = i;
                } else if (harmadik_valaszto == -1) {
                    harmadik_valaszto = i;
                } else if (negyedik_valaszto == -1) {
                    negyedik_valaszto = i;
                }
            } else if (sor[i] == '|') {
                pipe = i;
                break;
            }
        }
        
        if (elso_valaszto == -1 || masodik_valaszto == -1 || harmadik_valaszto == -1 || pipe == -1) continue;
        
        char cim_puffer[1024];
        int cim_hossz = 0;
        for (int i = elso_valaszto + 1; i < masodik_valaszto; ++i) {
            cim_puffer[cim_hossz++] = sor[i];
        }
        cim_puffer[cim_hossz] = '\0';
        String cim(cim_puffer);

        if(keres(cim) != nullptr) continue;
        
        char hossz_puffer[256];
        int hossz_hossz = 0;
        for (int i = masodik_valaszto + 1; i < harmadik_valaszto; ++i) {
            hossz_puffer[hossz_hossz++] = sor[i];
        }
        hossz_puffer[hossz_hossz] = '\0';
        
        int hossz = 0;
        for (int i = 0; hossz_puffer[i] != '\0'; ++i) {
            hossz = hossz * 10 + (hossz_puffer[i] - '0');
        }
        
        char ev_puffer[256];
        int ev_hossz = 0;
        int ev_vege = (negyedik_valaszto != -1) ? negyedik_valaszto : pipe;
        for (int i = harmadik_valaszto + 1; i < ev_vege; ++i) {
            ev_puffer[ev_hossz++] = sor[i];
        }
        ev_puffer[ev_hossz] = '\0';
        
        int ev = 0;
        for (int i = 0; ev_puffer[i] != '\0'; ++i) {
            ev = ev * 10 + (ev_puffer[i] - '0');
        }
        
        if (tipus == 'T') {
            Film* f = new Film(cim, hossz, ev);
            hozzaad(f);
        } else if (tipus == 'C') {
            char korhatar_puffer[256];
            int korhatar_hossz = 0;
            for (int i = negyedik_valaszto + 1; i < pipe; ++i) {
                korhatar_puffer[korhatar_hossz++] = sor[i];
            }
            korhatar_puffer[korhatar_hossz] = '\0';
            
            int korhatar = 0;
            for (int i = 0; korhatar_puffer[i] != '\0'; ++i) {
                korhatar = korhatar * 10 + (korhatar_puffer[i] - '0');
            }
            CsaladiFilm* f = new CsaladiFilm(cim, hossz, ev, korhatar);
            hozzaad(f);
        } else if (tipus == 'D') {
            char leiras_puffer[1024];
            int leiras_hossz = 0;
            for (int i = negyedik_valaszto + 1; i < pipe; ++i) {
                leiras_puffer[leiras_hossz++] = sor[i];
            }
            leiras_puffer[leiras_hossz] = '\0';
            String leiras(leiras_puffer);
            Dokumentumfilm* f = new Dokumentumfilm(cim, hossz, ev, leiras);
            hozzaad(f);
        }
    }

    save_file.close();
}


void Filmtar::rendez(bool evSzerint) {
    if (adatok.size() <= 1) return;
    
    rendezSegito(0, adatok.size() - 1, evSzerint);
}


void Filmtar::rendezSegito(int bal, int jobb, bool evSzerint) {
    if (bal < jobb) {
        int osztando = particional(bal, jobb, evSzerint);
        rendezSegito(bal, osztando - 1, evSzerint);
        rendezSegito(osztando + 1, jobb, evSzerint);
    }
}


int Filmtar::particional(int bal, int jobb, bool evSzerint) {
    Film* osszhasonlito = adatok[jobb];
    int i = bal - 1;
    
    for (int j = bal; j < jobb; ++j) {
        bool kisebb_e = false;
        
        if (evSzerint) {
            // Ev alapjan rendezunk
            if (adatok[j]->getEv() < osszhasonlito->getEv()) {
                kisebb_e = true;
            }
        } else {
            // Cim alapjan rendezunk
            if (adatok[j]->getCim() < osszhasonlito->getCim()) {
                kisebb_e = true;
            }
        }
        
        if (kisebb_e) {
            ++i;
            // Csere
            Film* temp = adatok[i];
            adatok[i] = adatok[j];
            adatok[j] = temp;
        }
    }
    
    // Pivot csere
    Film* temp = adatok[i + 1];
    adatok[i + 1] = adatok[jobb];
    adatok[jobb] = temp;
    
    return i + 1;
}