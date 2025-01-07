#ifndef RAPORT_H
#define RAPORT_H

#include <string>
#include <vector>
#include <iostream>
#include "../Angajati/Angajat.h"
#include "../Produse/Produs.h"
#include "../Comenzi/Comanda.h"

using namespace std;

class Raport {
public:
    // Generare raport zilnic
    static void generareRaport(const string& fisier_angajati, const string& fisier_comenzi, const string& fisier_produse);
};

#endif // RAPORT_H