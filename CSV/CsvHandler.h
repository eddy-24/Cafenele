#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <string>
#include <vector>

using namespace std;

class CsvHandler {
public:
    // Funcție pentru citirea unui fișier CSV și returnarea unui vector de vectori de string-uri
    static vector<vector<string>> citire(const string& nume_fisier);

    // Funcție pentru scrierea datelor într-un fișier CSV
    static void scriere(const string& nume_fisier, const vector<vector<string>>& date);
};

#endif // CSVHANDLER_H