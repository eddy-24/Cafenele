#include "CsvHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm> // Pentru curățarea spațiilor

using namespace std;

// Funcție pentru curățarea spațiilor sau caracterelor inutile
string curataSpatii(const string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

vector<vector<string>> CsvHandler::citire(const string& nume_fisier) {
    vector<vector<string>> date;
    ifstream fisier(nume_fisier);

    if (!fisier.is_open()) {
        cerr << "Eroare la deschiderea fișierului: " << nume_fisier << endl;
        return date;
    }

    string linie;
    int linie_curenta = 1;
    while (getline(fisier, linie)) {
        if (linie.empty()) {
            cerr << "Linie goală ignorată la rândul " << linie_curenta << ".\n";
            linie_curenta++;
            continue;
        }

        vector<string> rand;
        stringstream ss(linie);
        string celula;

        while (getline(ss, celula, ',')) {
            rand.push_back(curataSpatii(celula)); // Curățăm spațiile
        }

        if (!rand.empty()) {
            date.push_back(rand);
        } else {
            cerr << "Rând invalid ignorat la rândul " << linie_curenta << ": " << linie << "\n";
        }
        linie_curenta++;
    }

    fisier.close();
    return date;
}

void CsvHandler::scriere(const string& nume_fisier, const vector<vector<string>>& date) {
    ofstream fisier(nume_fisier);

    if (!fisier.is_open()) {
        cerr << "Eroare la deschiderea fișierului: " << nume_fisier << endl;
        return;
    }

    for (const auto& rand : date) {
        for (size_t i = 0; i < rand.size(); ++i) {
            fisier << rand[i];
            if (i < rand.size() - 1) fisier << ","; // Adaugăm separatorul între celule
        }
        fisier << "\n"; // Trecem la rândul următor
    }

    fisier.close();
}