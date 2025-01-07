#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <string>
#include <vector>
#include <iostream>
#include "../CSV/CsvHandler.h"

using namespace std;

class Angajat {
private:
    string nume;
    string functie;
    int ora_inceput;
    int ora_sfarsit;

public:
    Angajat(const string& nume, const string& functie, int ora_inceput, int ora_sfarsit);
    ~Angajat();

    // Getters
    string getFunctie() const;
    int getOraInceput() const;
    int getOraSfarsit() const;

    // Funcții statice
    static vector<Angajat> citireAngajati(const string& fisier_angajati);
    static void afisareAngajati(const vector<Angajat>& angajati);
    static void adaugareAngajat(const string& fisier_angajati, const string& nume, const string& functie, int ora_inceput, int ora_sfarsit);
    static void stergereAngajat(const string& fisier_angajati, const string& nume);
    static void modificareTura(const string& fisier_angajati, const string& nume, int ora_inceput, int ora_sfarsit);
    static void reparaCSV(const string& fisier_angajati);

    static void generareSalarii(const string& fisier_salarii, const string& fisier_angajati);
    static void afisareSalarii(const string& fisier_salarii);
};

#endif // ANGAJAT_H