#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "../CSV/CsvHandler.h"

using namespace std;

class Angajat {
protected:
    string nume;
    string functie;
    int ora_inceput;
    int ora_sfarsit;

public:
    Angajat(const string& nume, const string& functie, int ora_inceput, int ora_sfarsit);
    virtual ~Angajat();

    // Getters
    string getNume() const;
    string getFunctie() const;
    int getOraInceput() const;
    int getOraSfarsit() const;

    // Metodă virtuală pură
    virtual double calculeazaSalariu() const = 0;

    // Funcții statice modificate pentru a lucra cu unique_ptr
    static vector<unique_ptr<Angajat>> citireAngajati(const string& fisier_angajati);
    static void afisareAngajati(const vector<unique_ptr<Angajat>>& angajati);
    static void adaugareAngajat(const string& fisier_angajati, const string& nume, const string& functie, int ora_inceput, int ora_sfarsit);
    static void stergereAngajat(const string& fisier_angajati, const string& nume);
    static void modificareTura(const string& fisier_angajati, const string& nume, int ora_inceput, int ora_sfarsit);
    static void reparaCSV(const string& fisier_angajati);
    static void generareSalarii(const string& fisier_salarii, const string& fisier_angajati);
    static void afisareSalarii(const string& fisier_salarii);
};

// Clase derivate
class Barista : public Angajat {
public:
    Barista(const string& nume, int ora_inceput, int ora_sfarsit);
    double calculeazaSalariu() const override;
};

class Manager : public Angajat {
public:
    Manager(const string& nume, int ora_inceput, int ora_sfarsit);
    double calculeazaSalariu() const override;
};

class Ospatar : public Angajat {
public:
    Ospatar(const string& nume, int ora_inceput, int ora_sfarsit);
    double calculeazaSalariu() const override;
};

#endif // ANGAJAT_H