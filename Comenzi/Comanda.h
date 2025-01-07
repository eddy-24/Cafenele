#ifndef COMANDA_H
#define COMANDA_H

#include <string>
#include <vector>
#include <utility>

using namespace std;

class Comanda {
private:
    string nume_client;
    string produs_comandat;
    int cantitate;
    double pret_total;

public:
    // Constructor
    Comanda(const string& nume_client, const string& produs_comandat, int cantitate, double pret_total);

    // Getters
    string getNumeClient() const;
    string getProdusComandat() const;
    int getCantitate() const;
    double getPretTotal() const;

    // Afișare detalii
    void afisareDetalii() const;

    // Funcții statice
    static vector<Comanda> citireComenzi(const string& fisier_comenzi);
    static void adaugareComanda(const string& fisier_comenzi, const string& nume_client, const vector<pair<string, int>>& produse_comandate, const string& fisier_produse);
};

#endif // COMANDA_H