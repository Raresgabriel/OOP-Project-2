#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <stdexcept>
#include <string>

class ExceptieGenerala : public std::exception {
protected:
    std::string mesaj;
public:
    explicit ExceptieGenerala(const std::string& mesaj) : mesaj(mesaj) {}
    const char* what() const noexcept override { return mesaj.c_str(); }
};

class VarstaInvalida : public ExceptieGenerala {
public:
    VarstaInvalida() : ExceptieGenerala("Varsta invalida!") {}
};

class SalariuNegativ : public ExceptieGenerala {
public:
    SalariuNegativ() : ExceptieGenerala("Salariul nu poate fi negativ!") {}
};

class AngajatDuplicat : public ExceptieGenerala {
public:
    AngajatDuplicat() : ExceptieGenerala("Angajat deja existent!") {}
};

#endif // EXCEPTII_H
