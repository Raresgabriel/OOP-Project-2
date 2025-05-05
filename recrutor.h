#ifndef RECRUTOR_H
#define RECRUTOR_H

#include "angajat.h"
#include <iostream>

class Recrutor : public Angajat {
    int candidati;

public:
    Recrutor(const std::string& nume, int varsta, double salariu, int candidati)
        : Angajat(nume, varsta, salariu), candidati(candidati) {}

    void afiseazaInformatii() const override {
        std::cout << "Recrutor: " << nume << ", Varsta: " << varsta
                  << ", Salariu: " << salariu << ", Candidati evaluati: " << candidati << "\n";
    }

    std::shared_ptr<Angajat> cloneaza() const override {
        return std::make_shared<Recrutor>(*this);
    }
};

#endif
