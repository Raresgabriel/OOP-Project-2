#include "manager.h"
#include "programator.h"
#include "recrutor.h"
#include "departament.h"
#include "exceptii.h"
#include <iostream>
#include <fstream>
#include <sstream>

void citesteAngajatiDinFisier(const std::string& numeFisier, DepartamentResurseUmane& dep) {
    std::ifstream fisier(numeFisier);
    if (!fisier.is_open()) {
        throw std::runtime_error("Nu s-a putut deschide fisierul: " + numeFisier);
    }

    std::string linie;
    while (std::getline(fisier, linie)) {
        std::stringstream ss(linie);
        std::string tip, nume, limbaj;
        int varsta, valoareInt;
        double salariu;

        std::getline(ss, tip, ',');
        std::getline(ss, nume, ',');
        ss >> varsta;
        ss.ignore(1);
        ss >> salariu;
        ss.ignore(1);

        if (tip == "Manager") {
            ss >> valoareInt;
            dep.adaugaAngajat(std::make_shared<Manager>(nume, varsta, salariu, valoareInt));
        } else if (tip == "Programator") {
            std::getline(ss, limbaj);
            dep.adaugaAngajat(std::make_shared<Programator>(nume, varsta, salariu, limbaj));
        } else if (tip == "Recrutor") {
            ss >> valoareInt;
            dep.adaugaAngajat(std::make_shared<Recrutor>(nume, varsta, salariu, valoareInt));
        } else {
            std::cerr << "Tip necunoscut: " << tip << "\\n";
        }
    }

    fisier.close();
}

int main() {
    DepartamentResurseUmane departament;

    try {
        citesteAngajatiDinFisier("angajati.txt", departament);
        departament.afiseazaAngajati();
    } catch (const std::exception& e) {
        std::cerr << "Eroare: " << e.what() << "\\n";
    }

    return 0;
}
