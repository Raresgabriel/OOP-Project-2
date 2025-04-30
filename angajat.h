
#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <string>
#include <memory>

class Angajat {
protected:
    std::string nume;
    int varsta;
    double salariu;

public:
    Angajat(const std::string& nume, int varsta, double salariu)
        : nume(nume), varsta(varsta), salariu(salariu) {}

    virtual ~Angajat() = default;

    virtual void afiseazaInformatii() const = 0;
    virtual std::shared_ptr<Angajat> cloneaza() const = 0;

    const std::string& getNume() const { return nume; }
};

#endif // ANGAJAT_H
