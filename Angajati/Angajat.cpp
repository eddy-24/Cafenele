#include "Angajat.h"
#include "../CSV/CsvHandler.h"
#include <fstream>
#include <sstream>
#include <algorithm> // Pentru std::all_of
#include <iomanip>
#include <iostream>
#include <stdexcept>

using namespace std;

Angajat::Angajat(const string& nume, const string& functie, int ora_inceput, int ora_sfarsit)
    : nume(nume), functie(functie), ora_inceput(ora_inceput), ora_sfarsit(ora_sfarsit) {}

Angajat::~Angajat() {}

string Angajat::getFunctie() const {
    return functie;
}

int Angajat::getOraInceput() const {
    return ora_inceput;
}

int Angajat::getOraSfarsit() const {
    return ora_sfarsit;
}

vector<Angajat> Angajat::citireAngajati(const string& fisier_angajati) {
    auto date_angajati = CsvHandler::citire(fisier_angajati);
    vector<Angajat> angajati;

    for (const auto& rand : date_angajati) {
        if (rand.size() == 4) {
            try {
                string nume = rand[0];
                string functie = rand[1];

                if (!all_of(rand[2].begin(), rand[2].end(), ::isdigit) ||
                    !all_of(rand[3].begin(), rand[3].end(), ::isdigit)) {
                    throw invalid_argument("Ora nu este numerică.");
                }

                int ora_inceput = stoi(rand[2]);
                int ora_sfarsit = stoi(rand[3]);

                angajati.emplace_back(nume, functie, ora_inceput, ora_sfarsit);
            } catch (const exception& e) {
                cerr << "Eroare la citirea angajatului: " << e.what() << "\n";
            }
        } else {
            cerr << "Rând invalid în fișierul angajați: număr incorect de coloane.\n";
        }
    }

    return angajati;
}

void Angajat::afisareAngajati(const vector<Angajat>& angajati) {
    cout << "\n=== Lista Angajați ===\n";
    for (const auto& angajat : angajati) {
        cout << angajat.functie << ": " << angajat.nume
             << " | Program: " << angajat.ora_inceput << "-" << angajat.ora_sfarsit << "\n";
    }
}

void Angajat::adaugareAngajat(const string& fisier_angajati, const string& nume, const string& functie, int ora_inceput, int ora_sfarsit) {
    auto angajati = CsvHandler::citire(fisier_angajati);
    angajati.push_back({nume, functie, to_string(ora_inceput), to_string(ora_sfarsit)});
    CsvHandler::scriere(fisier_angajati, angajati);
}

void Angajat::stergereAngajat(const string& fisier_angajati, const string& nume) {
    auto angajati = CsvHandler::citire(fisier_angajati);
    auto it = remove_if(angajati.begin(), angajati.end(), [&](const vector<string>& rand) {
        return rand[0] == nume;
    });
    angajati.erase(it, angajati.end());
    CsvHandler::scriere(fisier_angajati, angajati);
}

void Angajat::modificareTura(const string& fisier_angajati, const string& nume, int ora_inceput, int ora_sfarsit) {
    auto angajati = CsvHandler::citire(fisier_angajati);
    for (auto& rand : angajati) {
        if (rand[0] == nume) {
            rand[2] = to_string(ora_inceput);
            rand[3] = to_string(ora_sfarsit);
        }
    }
    CsvHandler::scriere(fisier_angajati, angajati);
}

void Angajat::reparaCSV(const string& fisier_angajati) {
    ifstream file(fisier_angajati);
    if (!file.is_open()) {
        ofstream new_file(fisier_angajati);
        new_file << "Nume,Functie,OraInceput,OraSfarsit\n";
        new_file.close();
    }
}

void Angajat::generareSalarii(const string& fisier_salarii, const string& fisier_angajati) {
    auto angajati = citireAngajati(fisier_angajati);
    vector<vector<string>> salarii;

    double salariu_orar_barista = 20.0;
    double salariu_orar_manager = 30.0;
    double salariu_orar_ospatar = 15.0;

    for (const auto& angajat : angajati) {
        int ore_lucrate = angajat.getOraSfarsit() - angajat.getOraInceput();
        double salariu_zilnic = ore_lucrate * 20.0; // Exemplu: 20 lei/oră

        salarii.push_back({angajat.getFunctie(), to_string(ore_lucrate), to_string(salariu_zilnic)});
    }

    CsvHandler::scriere(fisier_salarii, salarii);
    cout << "Salariile zilnice au fost generate cu succes în fișierul " << fisier_salarii << ".\n";
}

void Angajat::afisareSalarii(const string& fisier_salarii) {
    auto salarii = CsvHandler::citire(fisier_salarii);

    cout << "\n=== Raport Salarii Zilnice ===\n";
    for (const auto& rand : salarii) {
        cout << "Funcție: " << rand[0]
             << " | Ore lucrate: " << rand[1]
             << " | Salariu Zilnic: " << rand[2] << " lei\n";
    }
}