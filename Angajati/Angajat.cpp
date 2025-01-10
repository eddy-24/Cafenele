#include "Angajat.h"
#include "../CSV/CsvHandler.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

// Implementări pentru constructori și metode de bază
Angajat::Angajat(const string& nume, const string& functie, int ora_inceput, int ora_sfarsit)
    : nume(nume), functie(functie), ora_inceput(ora_inceput), ora_sfarsit(ora_sfarsit) {}

Angajat::~Angajat() {}

string Angajat::getNume() const { return nume; }
string Angajat::getFunctie() const { return functie; }
int Angajat::getOraInceput() const { return ora_inceput; }
int Angajat::getOraSfarsit() const { return ora_sfarsit; }

// Implementări pentru clasele derivate mostenite
Barista::Barista(const string& nume, int ora_inceput, int ora_sfarsit)
    : Angajat(nume, "Barista", ora_inceput, ora_sfarsit) {}

double Barista::calculeazaSalariu() const {
    int ore_lucrate = ora_sfarsit - ora_inceput;
    return ore_lucrate * 20.0;
}

Manager::Manager(const string& nume, int ora_inceput, int ora_sfarsit)
    : Angajat(nume, "Manager", ora_inceput, ora_sfarsit) {}

double Manager::calculeazaSalariu() const {
    int ore_lucrate = ora_sfarsit - ora_inceput;
    return ore_lucrate * 30.0;
}

Ospatar::Ospatar(const string& nume, int ora_inceput, int ora_sfarsit)
    : Angajat(nume, "Ospatar", ora_inceput, ora_sfarsit) {}

double Ospatar::calculeazaSalariu() const {
    int ore_lucrate = ora_sfarsit - ora_inceput;
    return ore_lucrate * 15.0;
}

// Polimorfism static
vector<unique_ptr<Angajat>> Angajat::citireAngajati(const string& fisier_angajati) {
    auto date_angajati = CsvHandler::citire(fisier_angajati);
    vector<unique_ptr<Angajat>> angajati;

    for (const auto& rand : date_angajati) {
        if (rand.size() == 4) {
            try {
                string nume = rand[0];
                string functie = rand[1];
                int ora_inceput = stoi(rand[2]);
                int ora_sfarsit = stoi(rand[3]);

                unique_ptr<Angajat> angajat; //Pointer polimorfic
                if (functie == "Barista") {
                    angajat = make_unique<Barista>(nume, ora_inceput, ora_sfarsit);
                } else if (functie == "Manager") {
                    angajat = make_unique<Manager>(nume, ora_inceput, ora_sfarsit);
                } else if (functie == "Ospatar") {
                    angajat = make_unique<Ospatar>(nume, ora_inceput, ora_sfarsit);
                }

                if (angajat) {
                    angajati.push_back(move(angajat));
                }
            } catch (const exception& e) {
                cerr << "Eroare la citirea angajatului: " << e.what() << "\n";
            }
        }
    }
    return angajati;
}

void Angajat::afisareAngajati(const vector<unique_ptr<Angajat>>& angajati) {
    cout << "\n=== Lista Angajați ===\n";
    for (const auto& angajat : angajati) {
        cout << angajat->getFunctie() << ": " << angajat->getNume()
             << " | Program: " << angajat->getOraInceput() << "-" << angajat->getOraSfarsit()
             << " | Salariu zilnic: " << fixed << setprecision(2) << angajat->calculeazaSalariu() << " lei\n";
    }
}

void Angajat::adaugareAngajat(const string& fisier_angajati, const string& nume, const string& functie, int ora_inceput, int ora_sfarsit) {
    auto angajati = CsvHandler::citire(fisier_angajati);
    angajati.push_back({nume, functie, to_string(ora_inceput), to_string(ora_sfarsit)});
    CsvHandler::scriere(fisier_angajati, angajati);
}

void Angajat::stergereAngajat(const string& fisier_angajati, const string& nume) {
    auto angajati = CsvHandler::citire(fisier_angajati);
    auto it = remove_if(angajati.begin(), angajati.end(),
        [&](const vector<string>& rand) { return rand[0] == nume; });
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

    for (const auto& angajat : angajati) {// **Polimorfism: Apel dinamic al metodei calculeazaSalariu**
        double salariu_zilnic = angajat->calculeazaSalariu();
        int ore_lucrate = angajat->getOraSfarsit() - angajat->getOraInceput();
        
        salarii.push_back({angajat->getFunctie(), to_string(ore_lucrate), to_string(salariu_zilnic)});
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