# Gestionare Resurse Umane
## VA FI MODIFICAT PE GITHUB PANA SAPTAMANA VIITOARE!
## Descriere proiect

Acest proiect este o aplicatie simpla in C++ care simuleaza un mic sistem de gestiune pentru un departament de resurse umane.

Aplicatia permite adaugarea si afisarea de angajati, folosind mostenire si polimorfism. Fiecare angajat poate fi de tip **Manager**, **Programator** sau **Recrutor**, iar datele sunt preluate automat dintr-un fisier text (`angajati.txt`).

## Functionalitati

- Citeste dintr-un fisier text o lista de angajati
- Creeaza obiecte corespunzatoare pentru fiecare angajat
- Afiseaza toti angajatii din departament
- Evita dublurile (nu se accepta doi angajati cu acelasi nume)
- Arunca si prinde exceptii pentru cazuri de eroare (ex: angajat duplicat)
- Foloseste pointeri smart (`shared_ptr`) si STL (`vector`)
- Toata logica este implementata in fisiere `.h` pentru simplitate

## Exemple de angajati (din `angajati.txt`)

## Observatii

Proiectul a fost realizat pentru tema 2 de POO si respecta cerintele privind:
- organizarea pe fisiere
- folosirea mostenirii si a pointerilor smart
- tratarea exceptiilor
- folosirea const si a conceptelor POO
