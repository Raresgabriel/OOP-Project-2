#ifndef CANDIDATI_H
#define CANDIDATI_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

enum class NivelStudii {
    LICEU = 0,
    FACULTATE,
    MASTER,
    DOCTORAT
};

inline std::string toString(NivelStudii ns) {
    switch (ns) {
        case NivelStudii::LICEU:     return "Liceu";
        case NivelStudii::FACULTATE: return "Facultate";
        case NivelStudii::MASTER:    return "Master";
        case NivelStudii::DOCTORAT:  return "Doctorat";
    }
    return "Necunoscut";
}

inline NivelStudii stringToNivel(const std::string& s) {
    if (s == "Doctorat")  return NivelStudii::DOCTORAT;
    if (s == "Master")    return NivelStudii::MASTER;
    if (s == "Facultate") return NivelStudii::FACULTATE;
    return NivelStudii::LICEU;
}

/// Structura candidat
struct Candidat {
    std::string nume;
    NivelStudii studii;
    int aniExperienta;
    std::string pozitieDorita;
    std::vector<std::string> competente;
};

/// Scor de eligibilitate
struct ScorCandidat {
    int studiiScore     = 0;
    int experientaScore = 0;
    int skillScore      = 0;
    int total() const { return studiiScore + experientaScore + skillScore; }
};

/// Evalueaza un candidat in functie de criterii
inline ScorCandidat evalueaza(const Candidat& c,
                              NivelStudii minStudii,
                              int minAniExp,
                              const std::vector<std::string>& skillsCautate)
{
    ScorCandidat s;
    if (c.studii >= minStudii)
        s.studiiScore = int(c.studii) - int(minStudii) + 1;
    if (c.aniExperienta >= minAniExp)
        s.experientaScore = c.aniExperienta - minAniExp + 1;
    for (size_t i = 0; i < skillsCautate.size(); ++i) {
        const std::string& skill = skillsCautate[i];
        for (size_t j = 0; j < c.competente.size(); ++j) {
            if (c.competente[j] == skill) {
                ++s.skillScore;
                break;
            }
        }
    }
    return s;
}

/// Filtreaza candidatii dupa criterii
inline std::vector<Candidat> filtreaza(const std::vector<Candidat>& lista,
                                       NivelStudii minStudii,
                                       int minAniExp,
                                       const std::vector<std::string>& skillsCautate,
                                       const std::string& pozitieDorita = "")
{
    std::vector<Candidat> rez;
    for (size_t i = 0; i < lista.size(); ++i) {
        const Candidat& c = lista[i];
        if (c.studii < minStudii) continue;
        if (c.aniExperienta < minAniExp) continue;
        if (!pozitieDorita.empty() && c.pozitieDorita != pozitieDorita) continue;
        bool ok = true;
        for (size_t k = 0; k < skillsCautate.size(); ++k) {
            bool found = false;
            for (size_t j = 0; j < c.competente.size(); ++j) {
                if (c.competente[j] == skillsCautate[k]) {
                    found = true;
                    break;
                }
            }
            if (!found) { ok = false; break; }
        }
        if (ok) rez.push_back(c);
    }
    return rez;
}

/// intoarce top-K candidati ordonati dupa scor descrescator
inline std::vector<std::pair<Candidat,ScorCandidat>> topK(
    const std::vector<Candidat>& lista,
    NivelStudii minStudii,
    int minAniExp,
    const std::vector<std::string>& skillsCautate,
    int k)
{
    std::vector<std::pair<Candidat,ScorCandidat>> scored;
    for (size_t i = 0; i < lista.size(); ++i) {
        const Candidat& c = lista[i];
        ScorCandidat s = evalueaza(c, minStudii, minAniExp, skillsCautate);
        if (s.total() > 0) {
            scored.push_back(std::make_pair(c, s));
        }
    }
    std::sort(scored.begin(), scored.end(),
        [](std::pair<Candidat,ScorCandidat>& a, std::pair<Candidat,ScorCandidat>& b) {
            return a.second.total() > b.second.total();
        }
    );
    if (int(scored.size()) > k) {
        scored.resize(k);
    }
    return scored;
}

/// afiseaza un candidat si scorul sau
inline void afiseazaCandidatCuScor(const Candidat& c, const ScorCandidat& s) {
    std::cout << c.nume
              << " | Studii: " << toString(c.studii)
              << " | Exp: " << c.aniExperienta << " ani"
              << " | Poz: " << c.pozitieDorita
              << " | Scor: " << s.total()
              << " (studii+" << s.studiiScore
              << " exp+" << s.experientaScore
              << " skill+" << s.skillScore << ")\n";
}

/// incarca lista de candidati dintr-un fisier CSV
/// format: nume,studii,aniExperienta,pozitie,skill1;skill2;...
inline std::vector<Candidat> citesteCandidatiDinFisier(const std::string& fileName) {
    std::vector<Candidat> rez;
    std::ifstream f(fileName.c_str());
    if (!f.is_open()) {
        std::cerr << "Nu pot deschide " << fileName << "\n";
        return rez;
    }
    std::string linie;
    while (std::getline(f, linie)) {
        std::stringstream ss(linie);
        Candidat c;
        std::string studiiStr, competStr;
        if (!std::getline(ss, c.nume, ',')) continue;
        if (!std::getline(ss, studiiStr, ',')) continue;
        c.studii = stringToNivel(studiiStr);
        ss >> c.aniExperienta; ss.ignore(1);
        if (!std::getline(ss, c.pozitieDorita, ',')) continue;
        std::getline(ss, competStr);
        std::stringstream sc(competStr);
        std::string skill;
        while (std::getline(sc, skill, ';')) {
            if (!skill.empty()) c.competente.push_back(skill);
        }
        rez.push_back(c);
    }
    return rez;
}

/// punct de intrare unic pentru recrutare
inline void IncepeProgramulDeRecrutare() {
    /// citire candidati
    std::vector<Candidat> lista = citesteCandidatiDinFisier("candidati.txt");
    if (lista.empty()) return;

    NivelStudii minStudii = NivelStudii::FACULTATE;
    int minAniExp = 3;
    std::vector<std::string> skillsReq = {"C++","OOP"};
    std::string pozReq = "Programator";
    int K = 3;
    std::vector<Candidat> filtrati = filtreaza(lista, minStudii, minAniExp, skillsReq, pozReq);
    std::cout << "== Candidati filtrati ==\n";
    for (size_t i = 0; i < filtrati.size(); ++i) {
        std::cout << "- " << filtrati[i].nume << "\n";
    }

    std::vector<std::pair<Candidat,ScorCandidat>> best = topK(lista, minStudii, minAniExp, skillsReq, K);
    std::cout << "\n== Top " << K << " candidati ==\n";
    for (size_t i = 0; i < best.size(); ++i) {
        afiseazaCandidatCuScor(best[i].first, best[i].second);
    }
}

#endif
