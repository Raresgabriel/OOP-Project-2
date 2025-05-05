#ifndef MANAGER_H
#define MANAGER_H

#include "angajat.h"
#include <iostream>

class Manager : public Angajat {
    int echipa;

public:
    Manager(const std::string& nume, int varsta, double salariu, int echipa)
        : Angajat(nume, varsta, salariu), echipa(echipa) {}

    void afiseazaInformatii() const override {
        std::cout << "Manager: " << nume << ", Varsta: " << varsta
                  << ", Salariu: " << salariu << ", Echipa condusa: " << echipa << "\n";
    }

    std::shared_ptr<Angajat> cloneaza() const override {
        return std::make_shared<Manager>(*this);
    }
};

#endif
