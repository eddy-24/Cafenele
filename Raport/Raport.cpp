#include "Raport.h"
#include "../CSV/CsvHandler.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

void Raport::generareRaport(const string& fisier_angajati, const string& fisier_comenzi, const string& fisier_produse) {
    // Citim datele necesare
    auto angajati = Angajat::citireAngajati(fisier_angajati);
    auto comenzi = Comanda::citireComenzi(fisier_comenzi);
    auto produse = Produs::citireProduse(fisier_produse);

    // Calculăm salariile angajaților pentru o zi
    double total_salarii = 0.0;
    for (const auto& angajat : angajati) {
        int ore_lucrate = angajat.getOraSfarsit() - angajat.getOraInceput();
        double salariu_orar = 20.0; // Exemplu: 20 lei/oră
        total_salarii += ore_lucrate * salariu_orar; // Salariu zilnic
    }

    // Calculăm veniturile din comenzi
    double venituri_totale = 0.0;
    for (const auto& comanda : comenzi) {
        venituri_totale += comanda.getPretTotal();
    }

    // Calculăm costurile produselor vândute
    double costuri_produse = 0.0;
    for (const auto& comanda : comenzi) {
        string produs_comandat = comanda.getProdusComandat();
        int cantitate_vanduta = comanda.getCantitate();

        for (const auto& produs : produse) {
            if (produs.getNume() == produs_comandat) {
                costuri_produse += produs.getPret() * cantitate_vanduta * 0.5; // Exemplu: cost = 50% din preț
                break;
            }
        }
    }

    // Calculăm profitul net
    double profit_net = venituri_totale - costuri_produse - total_salarii;

    // Afișăm raportul
    cout << "\n=== Raport Zilnic ===\n";
    cout << "Venituri totale: " << fixed << setprecision(2) << venituri_totale << " lei\n";
    cout << "Costuri produse: " << fixed << setprecision(2) << costuri_produse << " lei\n";
    cout << "Salarii angajați: " << fixed << setprecision(2) << total_salarii << " lei\n";
    cout << "Profit net: " << fixed << setprecision(2) << profit_net << " lei\n";

    // Scriem raportul în `rapoarte.csv`
    string fisier_rapoarte = "data/rapoarte.csv";
    ofstream raport_file(fisier_rapoarte, ios::app); // Deschidem fișierul în modul append

    if (!raport_file.is_open()) {
        cerr << "Eroare: Nu s-a putut deschide fișierul " << fisier_rapoarte << " pentru scriere.\n";
        return;
    }

    // Verificăm dacă fișierul este gol (pentru a scrie header-ul)
    raport_file.seekp(0, ios::end);
    if (raport_file.tellp() == 0) {
        raport_file << "Data,VenituriTotale,CosturiProduse,SalariiAngajati,ProfitNet\n";
    }

    // Scriem datele raportului
    raport_file << "2025-01-07" << "," // Exemplu de dată (ar trebui calculată dinamic)
                << fixed << setprecision(2) << venituri_totale << ","
                << fixed << setprecision(2) << costuri_produse << ","
                << fixed << setprecision(2) << total_salarii << ","
                << fixed << setprecision(2) << profit_net << "\n";

    raport_file.close();
    cout << "Raportul zilnic a fost salvat în " << fisier_rapoarte << ".\n";
}
