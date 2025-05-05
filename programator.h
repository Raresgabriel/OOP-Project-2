#ifndef PROGRAMATOR_H
#define PROGRAMATOR_H

#include "angajat.h"
#include <iostream>

class Programator : public Angajat {
    std::string limbaj;

public:
    Programator(const std::string& nume, int varsta, double salariu, const std::string& limbaj)
        : Angajat(nume, varsta, salariu), limbaj(limbaj) {}

    void afiseazaInformatii() const override {
        std::cout << "Programator: " << nume << ", Varsta: " << varsta
                  << ", Salariu: " << salariu << ", Limbaj: " << limbaj << "\n";
    }

    std::shared_ptr<Angajat> cloneaza() const override {
        return std::make_shared<Programator>(*this);
    }
};

#endif
