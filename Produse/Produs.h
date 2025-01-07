#ifndef PRODUS_H
#define PRODUS_H

#include <string>
#include <vector>
#include <iostream>
#include "../CSV/CsvHandler.h"

using namespace std;

class Produs {
private:
    string nume;
    string tip;
    double pret;
    int cantitate;

public:
    // Constructori și Destructor
    Produs(const string& nume, const string& tip, double pret, int cantitate);
    ~Produs();

    // Funcții pentru afișare
    void afisareDetalii() const;

    // Getters și Setters
    string getNume() const;
    string getTip() const;
    double getPret() const;
    int getCantitate() const;

    void setCantitate(int cantitate);

    // Funcții statice pentru gestionarea produselor
    static vector<Produs> citireProduse(const string& fisier_produse);
    static void afisareProduse(const vector<Produs>& produse);
    static void adaugareProdus(const string& fisier_produse, const string& nume, const string& tip, double pret, int cantitate);
    static void stergereProdus(const string& fisier_produse, const string& nume);
    static void modificareStoc(const string& fisier_produse, const string& nume, int cantitate);
    static double calculProfitZilnic(const string& fisier_produse, const vector<pair<string, int>>& produse_vandute);
    static void reparaCSV(const string& fisier_produse);

};

#endif // PRODUS_H