#include <iostream>
#include <iomanip>
#include "Angajati/Angajat.h"
#include "Produse/Produs.h"
#include "Comenzi/Comanda.h"
#include "Evenimente/Eveniment.h"
#include "Raport/Raport.h"

using namespace std;

void afisareMeniuPrincipal() {
    cout << "\n=== Meniu Principal ===\n";
    cout << "1. Gestionare Angajați\n";
    cout << "2. Gestionare Produse\n";
    cout << "3. Secțiune Client\n";
    cout << "4. Gestionare Evenimente\n";
    cout << "5. Gestionare Raport Zilnic\n";
    cout << "6. Gestionare Salarii\n";
    cout << "7. Ieșire\n";
    cout << "Alegeți o opțiune: ";
}

void afisareMeniuAngajati() {
    cout << "\n=== Gestionare Angajați ===\n";
    cout << "1. Vizualizare lista de angajați\n";
    cout << "2. Adăugare angajat\n";
    cout << "3. Ștergere angajat\n";
    cout << "4. Modificare tura angajat\n";
    cout << "5. Înapoi la Meniul Principal\n";
    cout << "Alegeți o opțiune: ";
}

void afisareMeniuProduse() {
    cout << "\n=== Gestionare Produse ===\n";
    cout << "1. Vizualizare lista de produse\n";
    cout << "2. Adăugare produs\n";
    cout << "3. Ștergere produs\n";
    cout << "4. Modificare stoc produs\n";
    cout << "5. Înapoi la Meniul Principal\n";
    cout << "Alegeți o opțiune: ";
}

void afisareMeniuEvenimente() {
    cout << "\n=== Gestionare Evenimente ===\n";
    cout << "1. Vizualizare lista de evenimente\n";
    cout << "2. Adăugare eveniment\n";
    cout << "3. Ștergere eveniment\n";
    cout << "4. Calculare cost total\n";
    cout << "5. Înapoi la Meniul Principal\n";
    cout << "Alegeți o opțiune: ";
}

void afisareMeniuRaport() {
    cout << "\n=== Gestionare Raport Zilnic ===\n";
    cout << "1. Generare raport zilnic\n";
    cout << "2. Înapoi la Meniul Principal\n";
    cout << "Alegeți o opțiune: ";
}

void afisareMeniuSalarii() {
    cout << "\n=== Gestionare Salarii ===\n";
    cout << "1. Generare salarii\n";
    cout << "2. Afișare salarii\n";
    cout << "3. Înapoi la Meniul Principal\n";
    cout << "Alegeți o opțiune: ";
}

void sectiuneClient(const string& fisier_produse, const string& fisier_comenzi) {
    cout << "\n=== Secțiune Client ===\n";

    string nume_client;
    cout << "Introduceți numele dumneavoastră: ";
    cin.ignore();
    getline(cin, nume_client);

    vector<pair<string, int>> produse_comandate;
    auto produse_disponibile = Produs::citireProduse(fisier_produse);

    int nr_produse;
    cout << "Introduceți numărul de produse pe care doriți să le comandați: ";
    cin >> nr_produse;

    for (int i = 0; i < nr_produse; ++i) {
        string nume_produs;
        int cantitate;

        cout << "Introduceți numele produsului #" << (i + 1) << ": ";
        cin.ignore();
        getline(cin, nume_produs);

        cout << "Introduceți cantitatea: ";
        cin >> cantitate;

        bool produs_gasit = false;
        for (const auto& produs : produse_disponibile) {
            if (produs.getNume() == nume_produs) {
                produse_comandate.emplace_back(nume_produs, cantitate);
                produs_gasit = true;
                break;
            }
        }

        if (!produs_gasit) {
            cout << "Produsul " << nume_produs << " nu este disponibil. Încercați din nou.\n";
            --i; // Reîncercăm introducerea acestui produs
        }
    }

    // Adăugăm comanda și calculăm totalul
    Comanda::adaugareComanda(fisier_comenzi, nume_client, produse_comandate, fisier_produse);
}

int main() {
    string fisier_angajati = "data/angajati.csv";
    string fisier_produse = "data/produse.csv";
    string fisier_comenzi = "data/comenzi.csv";
    string fisier_evenimente = "data/evenimente.csv";
    string fisier_salarii = "data/salarii.csv";

    // Reparăm fișierele CSV înainte de citire
    Angajat::reparaCSV(fisier_angajati);
    Produs::reparaCSV(fisier_produse);

    int optiune_principala = 0;

    do {
        afisareMeniuPrincipal();
        cin >> optiune_principala;

        switch (optiune_principala) {
            case 1: { // Gestionare Angajați
                int optiune_angajati = 0;

                do {
                    afisareMeniuAngajati();
                    cin >> optiune_angajati;

                    switch (optiune_angajati) {
                        case 1: {
                            auto angajati = Angajat::citireAngajati(fisier_angajati);
                            Angajat::afisareAngajati(angajati);
                            break;
                        }
                        case 2: {
                            string nume, functie;
                            int ora_inceput, ora_sfarsit;

                            cout << "Introduceți numele angajatului: ";
                            cin.ignore();
                            getline(cin, nume);

                            cout << "Introduceți funcția (Barista, Manager, Ospatar): ";
                            cin >> functie;

                            cout << "Introduceți ora de început (0-23): ";
                            cin >> ora_inceput;

                            cout << "Introduceți ora de sfârșit (0-23): ";
                            cin >> ora_sfarsit;

                            Angajat::adaugareAngajat(fisier_angajati, nume, functie, ora_inceput, ora_sfarsit);
                            break;
                        }
                        case 3: {
                            string nume;

                            cout << "Introduceți numele angajatului pe care doriți să-l ștergeți: ";
                            cin.ignore();
                            getline(cin, nume);

                            Angajat::stergereAngajat(fisier_angajati, nume);
                            break;
                        }
                        case 4: {
                            string nume;
                            int ora_inceput, ora_sfarsit;

                            cout << "Introduceți numele angajatului: ";
                            cin.ignore();
                            getline(cin, nume);

                            cout << "Introduceți noua oră de început (0-23): ";
                            cin >> ora_inceput;

                            cout << "Introduceți noua oră de sfârșit (0-23): ";
                            cin >> ora_sfarsit;

                            Angajat::modificareTura(fisier_angajati, nume, ora_inceput, ora_sfarsit);
                            break;
                        }
                        case 5:
                            cout << "Revenire la Meniul Principal.\n";
                            break;
                        default:
                            cout << "Opțiune invalidă. Încercați din nou.\n";
                    }
                } while (optiune_angajati != 5);

                break;
            }
            case 2: { // Gestionare Produse
                int optiune_produse = 0;

                do {
                    afisareMeniuProduse();
                    cin >> optiune_produse;

                    switch (optiune_produse) {
                        case 1: {
                            auto produse = Produs::citireProduse(fisier_produse);
                            Produs::afisareProduse(produse);
                            break;
                        }
                        case 2: {
                            string nume, tip;
                            double pret;
                            int cantitate;

                            cout << "Introduceți numele produsului: ";
                            cin.ignore();
                            getline(cin, nume);

                            cout << "Introduceți tipul produsului (Cafea, Bautura, Desert): ";
                            getline(cin, tip);

                            cout << "Introduceți prețul produsului: ";
                            cin >> pret;

                            cout << "Introduceți cantitatea disponibilă: ";
                            cin >> cantitate;

                            Produs::adaugareProdus(fisier_produse, nume, tip, pret, cantitate);
                            break;
                        }
                        case 3: {
                            string nume;

                            cout << "Introduceți numele produsului pe care doriți să-l ștergeți: ";
                            cin.ignore();
                            getline(cin, nume);

                            Produs::stergereProdus(fisier_produse, nume);
                            break;
                        }
                        case 4: {
                            string nume;
                            int cantitate;

                            cout << "Introduceți numele produsului: ";
                            cin.ignore();
                            getline(cin, nume);

                            cout << "Introduceți noua cantitate: ";
                            cin >> cantitate;

                            Produs::modificareStoc(fisier_produse, nume, cantitate);
                            break;
                        }
                        case 5:
                            cout << "Revenire la Meniul Principal.\n";
                            break;
                        default:
                            cout << "Opțiune invalidă. Încercați din nou.\n";
                    }
                } while (optiune_produse != 5);

                break;
            }
            case 3: { // Secțiune Client
                sectiuneClient(fisier_produse, fisier_comenzi);
                break;
            }
            case 4: { // Gestionare Evenimente
                int optiune_evenimente = 0;

                do {
                    afisareMeniuEvenimente();
                    cin >> optiune_evenimente;

                    switch (optiune_evenimente) {
                        case 1: {
                            auto evenimente = Eveniment::citireEvenimente(fisier_evenimente);
                            Eveniment::afisareEvenimente(evenimente);
                            break;
                        }
                        case 2: {
                            string nume, data, locatie;
                            double cost;

                            cout << "Introduceți numele evenimentului: ";
                            cin.ignore();
                            getline(cin, nume);

                            cout << "Introduceți data evenimentului (format: YYYY-MM-DD): ";
                            getline(cin, data);

                            cout << "Introduceți locația: ";
                            getline(cin, locatie);

                            cout << "Introduceți costul evenimentului: ";
                            cin >> cost;

                            Eveniment::adaugareEveniment(fisier_evenimente, nume, data, locatie, cost);
                            break;
                        }
                        case 3: {
                            string nume;

                            cout << "Introduceți numele evenimentului pe care doriți să-l ștergeți: ";
                            cin.ignore();
                            getline(cin, nume);

                            Eveniment::stergereEveniment(fisier_evenimente, nume);
                            break;
                        }
                        case 4: {
                            double cost_total = Eveniment::calculareCostTotal(fisier_evenimente);
                            cout << "Costul total al evenimentelor este: " << fixed << setprecision(2) << cost_total << " lei\n";
                            break;
                        }
                        case 5:
                            cout << "Revenire la Meniul Principal.\n";
                            break;
                        default:
                            cout << "Opțiune invalidă. Încercați din nou.\n";
                    }
                } while (optiune_evenimente != 5);

                break;
            }
            case 5: { // Gestionare Raport Zilnic
                int optiune_raport = 0;

                do {
                    afisareMeniuRaport();
                    cin >> optiune_raport;

                    switch (optiune_raport) {
                        case 1: {
                            Raport::generareRaport(fisier_angajati, fisier_comenzi, fisier_produse);
                            break;
                        }
                        case 2:
                            cout << "Revenire la Meniul Principal.\n";
                            break;
                        default:
                            cout << "Opțiune invalidă. Încercați din nou.\n";
                    }
                } while (optiune_raport != 2);

                break;
            }
            case 6: { // Gestionare Salarii
                int optiune_salarii = 0;

                do {
                    afisareMeniuSalarii();
                    cin >> optiune_salarii;

                    switch (optiune_salarii) {
                        case 1: {
                            Angajat::generareSalarii(fisier_salarii, fisier_angajati);
                            break;
                        }
                        case 2: {
                            Angajat::afisareSalarii(fisier_salarii);
                            break;
                        }
                        case 3:
                            cout << "Revenire la Meniul Principal.\n";
                            break;
                        default:
                            cout << "Opțiune invalidă. Încercați din nou.\n";
                    }
                } while (optiune_salarii != 3);

                break;
            }
            case 7:
                cout << "Ieșire din program.\n";
                break;
            default:
                cout << "Opțiune invalidă. Încercați din nou.\n";
        }
    } while (optiune_principala != 7);

    return 0;
}