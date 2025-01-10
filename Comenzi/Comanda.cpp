#include "Comanda.h"
#include "../CSV/CsvHandler.h"
#include "../Produse/Produs.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>

Comanda::Comanda(const string& nume_client, const string& produs_comandat, int cantitate, double pret_total)
    : nume_client(nume_client), produs_comandat(produs_comandat), cantitate(cantitate), pret_total(pret_total) {}

string Comanda::getNumeClient() const {
    return nume_client;
}

string Comanda::getProdusComandat() const {
    return produs_comandat;
}

int Comanda::getCantitate() const {
    return cantitate;
}

double Comanda::getPretTotal() const {
    return pret_total;
}

void Comanda::afisareDetalii() const {
    cout << left << setw(20) << nume_client
         << setw(20) << produs_comandat
         << setw(10) << cantitate
         << setw(10) << fixed << setprecision(2) << pret_total << " lei\n";
}

vector<Comanda> Comanda::citireComenzi(const string& fisier_comenzi) {
    auto date_comenzi = CsvHandler::citire(fisier_comenzi);
    vector<Comanda> comenzi;

    cout << "\n=== Lista Comenzi ===\n";
    cout << left << setw(20) << "Client"
         << setw(20) << "Produs"
         << setw(10) << "Cantitate"
         << setw(10) << "Total" << "\n";
    cout << string(60, '-') << "\n";

    for (const auto& rand : date_comenzi) {
        try {
            if (rand.size() != 4) {
                throw invalid_argument("Număr incorect de coloane");
            }

            string nume_client = rand[0];
            string produs_comandat = rand[1];
            
            // Validare cantitate
            if (!all_of(rand[2].begin(), rand[2].end(), ::isdigit)) {
                throw invalid_argument("Cantitate invalidă: " + rand[2]);
            }
            int cantitate = stoi(rand[2]);

            // Validare preț total
            double pret_total = stod(rand[3]);

            // Adaugăm comanda în vector
            comenzi.emplace_back(nume_client, produs_comandat, cantitate, pret_total);

            // Afișăm direct comanda citită
            comenzi.back().afisareDetalii();
        } catch (const exception& e) {
            cerr << "Eroare la citirea comenzii: " << e.what() << "\n";
        }
    }

    return comenzi;
}


void Comanda::adaugareComanda(const string& fisier_comenzi, const string& nume_client, const vector<pair<string, int>>& produse_comandate, const string& fisier_produse) {
    vector<vector<string>> comenzi = CsvHandler::citire(fisier_comenzi);
    auto produse_disponibile = Produs::citireProduse(fisier_produse);

    vector<vector<string>> produse_actualizate = CsvHandler::citire(fisier_produse);

    double pret_total = 0.0;

    for (const auto& produs_comandat : produse_comandate) {
        bool produs_gasit = false;

        for (auto& rand : produse_actualizate) {
            if (rand[0] == produs_comandat.first) { // Găsim produsul în CSV
                int cantitate_disponibila = stoi(rand[3]); // Coloana 4 = Cantitate
                if (cantitate_disponibila >= produs_comandat.second) {
                    cantitate_disponibila -= produs_comandat.second; // Scădem cantitatea
                    rand[3] = to_string(cantitate_disponibila); // Actualizăm cantitatea în CSV

                    // Calculăm prețul total
                    double pret_unitar = stod(rand[2]); // Coloana 3 = Preț
                    pret_total += pret_unitar * produs_comandat.second;

                    // Adăugăm rândul comenzii în format corect
                    comenzi.push_back({nume_client, produs_comandat.first, to_string(produs_comandat.second), to_string(pret_unitar * produs_comandat.second)});
                    produs_gasit = true;
                    break;
                } else {
                    cerr << "Produsul \"" << produs_comandat.first << "\" nu are stoc suficient. Disponibil: " << cantitate_disponibila << "\n";
                    return; // Oprire dacă stocul este insuficient
                }
            }
        }

        if (!produs_gasit) {
            cerr << "Produsul \"" << produs_comandat.first << "\" nu există în inventar.\n";
            return;
        }
    }

    // Actualizăm inventarul în CSV
    CsvHandler::scriere(fisier_produse, produse_actualizate);

    // Scriem comenzile actualizate în CSV
    CsvHandler::scriere(fisier_comenzi, comenzi);

    cout << "Comanda a fost adăugată cu succes.\n";
}
