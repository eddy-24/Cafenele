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

    unordered_map<string, unordered_map<string, pair<int, double>>> comenzi_map;

    for (const auto& rand : date_comenzi) {
        try {


            if (rand.size() != 4) {
                throw invalid_argument("Număr incorect de coloane");
            }

            string nume_client = rand[0];
            string produs_comandat = rand[1];

            // Validare pentru cantitate
            if (!all_of(rand[2].begin(), rand[2].end(), ::isdigit)) {
                throw invalid_argument("Cantitate invalidă: " + rand[2]);
            }
            int cantitate = stoi(rand[2]);

            // Validare pentru preț total
            double pret_total;
            try {
                pret_total = stod(rand[3]);
            } catch (const invalid_argument& e) {
                throw invalid_argument("Preț total invalid: " + rand[3]);
            } catch (const out_of_range& e) {
                throw invalid_argument("Preț total prea mare: " + rand[3]);
            }

            comenzi_map[nume_client][produs_comandat].first += cantitate;
            comenzi_map[nume_client][produs_comandat].second += pret_total;
        } catch (const exception& e) {
            cerr << "Eroare la citirea comenzii: " << e.what() << "\n";
        }
    }

    for (const auto& client : comenzi_map) {
        for (const auto& produs : client.second) {
            comenzi.emplace_back(client.first, produs.first, produs.second.first, produs.second.second);
            comenzi.back().afisareDetalii(); // Afișăm comanda curentă
        }
    }

    return comenzi;
}

void Comanda::adaugareComanda(const string& fisier_comenzi, const string& nume_client, const vector<pair<string, int>>& produse_comandate, const string& fisier_produse) {
    vector<vector<string>> comenzi = CsvHandler::citire(fisier_comenzi);
    auto produse_disponibile = Produs::citireProduse(fisier_produse);

    for (const auto& produs_comandat : produse_comandate) {
        double pret_total = 0.0;
        bool produs_gasit = false;

        for (const auto& produs : produse_disponibile) {
            if (produs_comandat.first == produs.getNume()) {
                pret_total = produs.getPret() * produs_comandat.second;
                produs_gasit = true;
                break;
            }
        }

        if (!produs_gasit) {
            cerr << "Produsul \"" << produs_comandat.first << "\" nu există în lista produselor disponibile.\n";
            continue;
        }

        comenzi.push_back({nume_client, produs_comandat.first, to_string(produs_comandat.second), to_string(pret_total)});
    }

    CsvHandler::scriere(fisier_comenzi, comenzi);
    cout << "Comanda a fost adăugată cu succes.\n";
}