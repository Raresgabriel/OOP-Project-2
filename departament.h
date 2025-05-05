#ifndef DEPARTAMENT_H
#define DEPARTAMENT_H

#include "angajat.h"
#include "exceptii.h"
#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

/// un string de forma "dd.mm.yyyy" -> un std::tm
static std::tm stringLaData(const std::string& dataStr) {
    std::tm tmData = {};
    int zi = 0, luna = 0, an = 0;
    char sep1 = 0, sep2 = 0;
    std::istringstream ss(dataStr);
    ss >> zi >> sep1 >> luna >> sep2 >> an;
    if (!ss.fail() && sep1 == '.' && sep2 == '.') {
        tmData.tm_mday = zi;
        tmData.tm_mon  = luna - 1;
        tmData.tm_year = an - 1900;
    }
    return tmData;
}

/// Verifică dacă intervalele [inceput1, sfarsit1] și [inceput2, sfarsit2] se suprapun
static bool intervaleSeSuprapun(const std::string& inceput1,
                                const std::string& sfarsit1,
                                const std::string& inceput2,
                                const std::string& sfarsit2)
{
    std::tm t1s = stringLaData(inceput1);
    std::tm t1e = stringLaData(sfarsit1);
    std::tm t2s = stringLaData(inceput2);
    std::tm t2e = stringLaData(sfarsit2);

    std::time_t time1s = std::mktime(&t1s);
    std::time_t time1e = std::mktime(&t1e);
    std::time_t time2s = std::mktime(&t2s);
    std::time_t time2e = std::mktime(&t2e);

    /// data incepere concediu < data terminare concediu. (exceptie)
    return !(time1e < time2s || time2e < time1s);
}

class DepartamentResurseUmane {
private:
    std::vector<std::shared_ptr<Angajat>> angajati;
    /// map[nume] = vector de perechi<perioada, motiv>
    std::map<std::string, std::vector<std::pair<std::string,std::string>>> concedii;

public:
    /// citire angajati
    void citesteAngajatiDinFisier(const std::string& numeFisier) {
        std::ifstream fisier(numeFisier.c_str());
        if (!fisier.is_open()) {
            std::cerr << "Nu s-a putut deschide fisierul " << numeFisier << "\n";
            return;
        }
        std::string linie;
        while (std::getline(fisier, linie)) {
            std::stringstream ss(linie);
            std::string functie, nume, limbaj;
            int varsta = 0, echipaSauCandidati = 0;
            double salariu = 0.0;

            if (!std::getline(ss, functie, ',') ||
                !std::getline(ss, nume,   ',')) continue;
            ss >> varsta; ss.ignore(1);
            ss >> salariu; ss.ignore(1);

            if (functie == "Manager") {
                ss >> echipaSauCandidati;
                angajati.push_back(
                  std::make_shared<Manager>(nume, varsta, salariu, echipaSauCandidati)
                );
            }
            else if (functie == "Programator") {
                std::getline(ss, limbaj);
                angajati.push_back(
                  std::make_shared<Programator>(nume, varsta, salariu, limbaj)
                );
            }
            else if (functie == "Recrutor") {
                ss >> echipaSauCandidati;
                angajati.push_back(
                  std::make_shared<Recrutor>(nume, varsta, salariu, echipaSauCandidati)
                );
            }
        }
    }

    /// afisare angajati
    void afiseazaAngajati() const {
        for (size_t i = 0; i < angajati.size(); ++i) {
            angajati[i]->afiseazaInformatii();
            std::cout << "------------------------\n";
        }
    }

    /// adaugare concediu pt 1 angajat
    void adaugaConcediu(const std::string& nume,
                        const std::string& perioada,
                        const std::string& motiv)
    {
        concedii[nume].push_back(std::make_pair(perioada, motiv));
    }

    /// afiseaza concediile tuturor
    void afiseazaConcedii() const {
        for (auto it = concedii.begin(); it != concedii.end(); ++it) {
            const std::string& nume  = it->first;
            const auto& lista = it->second;
            std::cout << "Concedii pentru " << nume << ":\n";
            for (size_t j = 0; j < lista.size(); ++j) {
                std::cout << " - Perioada: " << lista[j].first
                          << " | Motiv: "  << lista[j].second << "\n";
            }
            std::cout << "\n";
        }
    }

    /// verifica daca angajatul este in concediu sau nu
    void esteInConcediu(const std::string& nume,
                        const std::string& perioadaVerificare) const
    {
        auto it = concedii.find(nume);
        if (it != concedii.end()) {
            const auto& lista = it->second;
            for (size_t k = 0; k < lista.size(); ++k) {
                const std::string& per = lista[k].first;
                const std::string& mot = lista[k].second;
                if (intervaleSeSuprapun(per, per, perioadaVerificare, perioadaVerificare)) {
                    std::cout << nume << " este in concediu in perioada "
                              << perioadaVerificare << ". Motiv: " << mot << "\n";
                    return;
                }
            }
        }
        std::cout << nume << " nu este in concediu in perioada "
                  << perioadaVerificare << "\n";
    }
    void afiseazaConcediiPentru(const std::string& nume) const {
        auto it = concedii.find(nume);
        if (it == concedii.end()) {
            std::cout << "Nu exista concedii inregistrate pentru " << nume << ".\n";
            return;
        }
        const auto& lista = it->second;
        std::cout << "Concedii pentru " << nume << ":\n";
        for (size_t i = 0; i < lista.size(); ++i) {
            std::cout << " - Perioada: " << lista[i].first
                      << " | Motiv: "    << lista[i].second << "\n";
        }
        std::cout << std::endl;
    }
};

#endif
