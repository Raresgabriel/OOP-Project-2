#include "manager.h"
#include "programator.h"
#include "recrutor.h"
#include "departament.h"
#include "exceptii.h"
#include "candidati.h"
#include <iostream>
#include <fstream>
#include <sstream>

void citesteAngajatiDinFisier(const std::string& numeFisier, std::vector<std::shared_ptr<Angajat>>& angajati)
{
    std::ifstream fisier(numeFisier);
    if (!fisier.is_open())
    {
        std::cerr << "Nu s-a putut deschide fisierul!" << std::endl;
        return;
    }

    std::string linie;
    while (std::getline(fisier, linie))
    {
        std::stringstream ss(linie);
        std::string functie, nume, limbajProgramare;
        int varsta, performantaSauEchipa;
        double salariu;

        std::getline(ss, functie, ',');
        std::getline(ss, nume, ',');
        ss >> varsta;
        ss.ignore();
        ss >> salariu;
        ss.ignore();

        if (functie == "Manager")
        {
            ss >> performantaSauEchipa;  /// echipa
            angajati.push_back(std::make_shared<Manager>(nume, varsta, salariu, performantaSauEchipa));
        }
        else if (functie == "Programator")
        {
            std::getline(ss, limbajProgramare);
            angajati.push_back(std::make_shared<Programator>(nume, varsta, salariu, limbajProgramare));
        }
        else if (functie == "Recrutor")
        {
            ss >> performantaSauEchipa;  /// nr candidati
            angajati.push_back(std::make_shared<Recrutor>(nume, varsta, salariu, performantaSauEchipa));
        }
    }

    fisier.close();
}
int main()
{
    DepartamentResurseUmane departament;

    /// citim din fisier
    departament.citesteAngajatiDinFisier("angajati.txt");

    /// afisam angajatii + informatii despre ei
    departament.afiseazaAngajati();
    std::cout <<"\n";

    departament.adaugaConcediu("Ion Popescu", "01.07.2025 - 14.07.2025", "Vacanta in familie");
    departament.adaugaConcediu("Ion Popescu", "20.08.2025 - 25.08.2025", "Concediu medical");
    departament.adaugaConcediu("Ana Ionescu", "05.08.2025 - 20.08.2025", "Recuperare medicala");
    departament.adaugaConcediu("Mihai Georgescu", "10.06.2025 - 25.06.2025", "Concediu paternal");
    departament.adaugaConcediu("Andreea Radu", "15.07.2025 - 30.07.2025", "Calatorie in strainatate");
    departament.adaugaConcediu("Vlad Ene", "01.09.2025 - 10.09.2025", "Participare la conferinta");
    departament.adaugaConcediu("Diana Lupu", "20.06.2025 - 05.07.2025", "Oboseala acumulata");
    departament.adaugaConcediu("Robert Marinescu", "12.08.2025 - 22.08.2025", "Nunta fratelui");
    departament.adaugaConcediu("Sorin Neagu", "01.07.2025 - 15.07.2025", "Timp cu familia");
    departament.adaugaConcediu("Alina Nistor", "03.08.2025 - 18.08.2025", "Probleme personale");
    departament.adaugaConcediu("Laura Voicu", "17.06.2025 - 30.06.2025", "Excursie cu prietenii");

    departament.esteInConcediu("Ion Popescu", "16.06.2025 - 17.06.2025");
    std::cout <<"\n";
    std::cout << "===== Lista completa a concediilor =====\n";
    departament.afiseazaConcedii();
    std::cout <<"\n";
    departament.afiseazaConcediiPentru("Ion Popescu");

    IncepeProgramulDeRecrutare();
    return 0;
}
