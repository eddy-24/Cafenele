#include "Produs.h"
#include <iomanip>
#include <sstream>

Produs::Produs(const string& nume, const string& tip, double pret, int cantitate)
    : nume(nume), tip(tip), pret(pret), cantitate(cantitate) {}

Produs::~Produs() {}

void Produs::afisareDetalii() const {
    cout << left << setw(20) << nume 
         << setw(15) << tip 
         << setw(10) << fixed << setprecision(2) << pret 
         << setw(10) << cantitate << "\n";
}

// Getters
string Produs::getNume() const { return nume; }
string Produs::getTip() const { return tip; }
double Produs::getPret() const { return pret; }
int Produs::getCantitate() const { return cantitate; }

// Setters
void Produs::setCantitate(int cantitate) { this->cantitate = cantitate; }

// Citire produse din CSV
vector<Produs> Produs::citireProduse(const string& fisier_produse) {
    auto date_produse = CsvHandler::citire(fisier_produse);
    vector<Produs> produse;

    cout << "\n=== Produse Disponibile ===\n";
    cout << left << setw(20) << "Nume" 
         << setw(15) << "Tip" 
         << setw(10) << "Pret" 
         << setw(10) << "Cantitate" << "\n";
    cout << string(55, '-') << "\n";

    for (const auto& rand : date_produse) {
        try {
            if (rand.size() != 4) {
                cerr << "Linie invalidă (număr greșit de coloane): ";
                for (const auto& celula : rand) cerr << celula << " ";
                cerr << "\n";
                continue;
            }

            string nume = rand[0];
            string tip = rand[1];
            double pret = stod(rand[2]);
            int cantitate = stoi(rand[3]);

            produse.emplace_back(nume, tip, pret, cantitate);
            produse.back().afisareDetalii(); // Afișăm produsul curent
        } catch (const exception& e) {
            cerr << "Eroare la citirea produsului: " << e.what() << "\n";
        }
    }

    return produse;
}

// Afișare produse
void Produs::afisareProduse(const vector<Produs>& produse) {
    cout << "\n=== Lista Produse ===\n";
    cout << left << setw(20) << "Nume" 
         << setw(15) << "Tip" 
         << setw(10) << "Pret" 
         << setw(10) << "Cantitate" << "\n";
    cout << string(55, '-') << "\n";

    for (const auto& produs : produse) {
        produs.afisareDetalii();
    }
}

// Adăugare produs în CSV
void Produs::adaugareProdus(const string& fisier_produse, const string& nume, const string& tip, double pret, int cantitate) {
    vector<vector<string>> produse = CsvHandler::citire(fisier_produse);

    stringstream pret_formatat;
    pret_formatat << fixed << setprecision(2) << pret;

    produse.push_back({nume, tip, pret_formatat.str(), to_string(cantitate)});
    CsvHandler::scriere(fisier_produse, produse);

    cout << "Produsul " << nume << " a fost adăugat cu succes.\n";
}

// Ștergere produs din CSV
void Produs::stergereProdus(const string& fisier_produse, const string& nume) {
    auto produse = CsvHandler::citire(fisier_produse);
    vector<vector<string>> produse_actualizate;

    for (const auto& rand : produse) {
        if (rand[0] != nume) {
            produse_actualizate.push_back(rand);
        }
    }

    CsvHandler::scriere(fisier_produse, produse_actualizate);
    cout << "Produsul " << nume << " a fost șters cu succes.\n";
}

// Modificare stoc produs
void Produs::modificareStoc(const string& fisier_produse, const string& nume, int cantitate) {
    auto produse = CsvHandler::citire(fisier_produse);
    for (auto& rand : produse) {
        if (rand[0] == nume) {
            rand[3] = to_string(cantitate);
            break;
        }
    }

    CsvHandler::scriere(fisier_produse, produse);
    cout << "Stocul produsului " << nume << " a fost modificat cu succes.\n";
}

// Reparare fișier CSV
void Produs::reparaCSV(const string& fisier_produse) {
    auto produse = CsvHandler::citire(fisier_produse);
    vector<vector<string>> produse_corecte;

    for (const auto& rand : produse) {
        if (rand.size() == 4 && !rand[2].empty() && !rand[3].empty()) {
            try {
                stod(rand[2]); // Validăm prețul
                stoi(rand[3]); // Validăm cantitatea
                produse_corecte.push_back(rand);
            } catch (...) {
                cerr << "Rând invalid eliminat: ";
                for (const auto& celula : rand) cerr << celula << " ";
                cerr << "\n";
            }
        } else {
            cerr << "Rând invalid eliminat: ";
            for (const auto& celula : rand) cerr << celula << " ";
            cerr << "\n";
        }
    }

    // Scriem doar rândurile valide în fișier
    CsvHandler::scriere(fisier_produse, produse_corecte);
    cout << "Fișierul produse a fost reparat.\n";
}