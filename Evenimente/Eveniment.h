#ifndef EVENIMENT_H
#define EVENIMENT_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "../CSV/CsvHandler.h"

using namespace std;

class Eveniment {
private:
    string nume_eveniment;
    string data_eveniment;
    string locatie;
    double cost;

public:
    Eveniment(const string& nume_eveniment, const string& data_eveniment, const string& locatie, double cost);
    ~Eveniment();

    void afisareDetalii() const;

    // Funcții statice
    template <typename T>
    static vector<T> citireEvenimenteTemplate(const string& fisier_evenimente, T (*transformator)(const vector<string>&));

    template <typename T>
    static void scriereEvenimenteTemplate(const string& fisier_evenimente, const vector<T>& evenimente, vector<string> (*transformator)(const T&));

    static vector<Eveniment> citireEvenimente(const string& fisier_evenimente);
    static void afisareEvenimente(const vector<Eveniment>& evenimente);
    static void adaugareEveniment(const string& fisier_evenimente, const string& nume_eveniment, const string& data_eveniment, const string& locatie, double cost);
    static void stergereEveniment(const string& fisier_evenimente, const string& nume_eveniment);
    static double calculareCostTotal(const string& fisier_evenimente);
};

#include "Eveniment.tpp"

#endif // EVENIMENT_H
