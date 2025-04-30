#ifndef DEPARTAMENT_H
#define DEPARTAMENT_H

#include "angajat.h"
#include "exceptii.h"
#include <vector>
#include <memory>
#include <iostream>

class DepartamentResurseUmane {
    std::vector<std::shared_ptr<Angajat>> angajati;

public:
    void adaugaAngajat(const std::shared_ptr<Angajat>& angajat) {
        for (const auto& a : angajati) {
            if (a->getNume() == angajat->getNume()) {
                throw AngajatDuplicat();
            }
        }
        angajati.push_back(angajat->cloneaza());
    }

    void afiseazaAngajati() const {
        for (const auto& a : angajati) {
            a->afiseazaInformatii();
        }
    }
};

#endif // DEPARTAMENT_H
