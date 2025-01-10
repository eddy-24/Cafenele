#ifndef EVENIMENT_TPP
#define EVENIMENT_TPP

#include "Eveniment.h"

template <typename T>
vector<T> Eveniment::citireEvenimenteTemplate(const string& fisier_evenimente, T (*transformator)(const vector<string>&)) {
    auto date_evenimente = CsvHandler::citire(fisier_evenimente);
    vector<T> evenimente;

    for (const auto& rand : date_evenimente) {
        try {
            evenimente.push_back(transformator(rand));
        } catch (const exception& e) {
            cerr << "Eroare la transformarea datelor: " << e.what() << "\n";
        }
    }

    return evenimente;
}

template <typename T>
void Eveniment::scriereEvenimenteTemplate(const string& fisier_evenimente, const vector<T>& evenimente, vector<string> (*transformator)(const T&)) {
    vector<vector<string>> date_csv;

    for (const auto& eveniment : evenimente) {
        date_csv.push_back(transformator(eveniment));
    }

    CsvHandler::scriere(fisier_evenimente, date_csv);
}

#endif // EVENIMENT_TPP
