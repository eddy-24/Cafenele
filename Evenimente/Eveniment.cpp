#include "Eveniment.h"
#include <iomanip>
#include <sstream>

Eveniment::Eveniment(const string& nume_eveniment, const string& data_eveniment, const string& locatie, double cost)
    : nume_eveniment(nume_eveniment), data_eveniment(data_eveniment), locatie(locatie), cost(cost) {}

Eveniment::~Eveniment() {}

void Eveniment::afisareDetalii() const {
    cout << "Eveniment: " << nume_eveniment << " | Data: " << data_eveniment << " | Locație: " << locatie
         << " | Cost: " << fixed << setprecision(2) << cost << " lei\n";
}

// Citire evenimente din CSV
vector<Eveniment> Eveniment::citireEvenimente(const string& fisier_evenimente) {
    auto date_evenimente = CsvHandler::citire(fisier_evenimente);
    vector<Eveniment> evenimente;

    for (const auto& rand : date_evenimente) {
        try {
            if (rand.size() != 4) continue;

            string nume_eveniment = rand[0];
            string data_eveniment = rand[1];
            string locatie = rand[2];
            double cost = stod(rand[3]);

            evenimente.emplace_back(nume_eveniment, data_eveniment, locatie, cost);
        } catch (const exception& e) {
            cerr << "Eroare la citirea evenimentului: " << e.what() << "\n";
        }
    }

    return evenimente;
}

// Afișare evenimente
void Eveniment::afisareEvenimente(const vector<Eveniment>& evenimente) {
    cout << "=== Lista Evenimente ===\n";
    for (const auto& eveniment : evenimente) {
        eveniment.afisareDetalii();
    }
}

// Adăugare eveniment
void Eveniment::adaugareEveniment(const string& fisier_evenimente, const string& nume_eveniment, const string& data_eveniment, const string& locatie, double cost) {
    vector<vector<string>> evenimente = CsvHandler::citire(fisier_evenimente);

    stringstream cost_formatat;
    cost_formatat << fixed << setprecision(2) << cost;

    evenimente.push_back({nume_eveniment, data_eveniment, locatie, cost_formatat.str()});
    CsvHandler::scriere(fisier_evenimente, evenimente);

    cout << "Evenimentul " << nume_eveniment << " a fost adăugat cu succes.\n";
}

// Ștergere eveniment
void Eveniment::stergereEveniment(const string& fisier_evenimente, const string& nume_eveniment) {
    auto evenimente = CsvHandler::citire(fisier_evenimente);
    vector<vector<string>> evenimente_actualizate;

    for (const auto& rand : evenimente) {
        if (rand[0] != nume_eveniment) {
            evenimente_actualizate.push_back(rand);
        }
    }

    CsvHandler::scriere(fisier_evenimente, evenimente_actualizate);
    cout << "Evenimentul " << nume_eveniment << " a fost șters cu succes.\n";
}

// Calculare cost total
double Eveniment::calculareCostTotal(const string& fisier_evenimente) {
    auto evenimente = CsvHandler::citire(fisier_evenimente);
    double cost_total = 0.0;

    for (const auto& rand : evenimente) {
        try {
            if (rand.size() == 4) {
                cost_total += stod(rand[3]);
            }
        } catch (...) {
            cerr << "Eroare la calcularea costului pentru un eveniment.\n";
        }
    }

    return cost_total;
}
