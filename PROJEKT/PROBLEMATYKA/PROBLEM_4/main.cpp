#include <iostream>
#include <fstream>
#include <vector>
#include "wypukla_otoczka.h"
#include "reprezentacja_danych.h" // zawiera Pole itd.

using namespace std;

int main() {
    vector<Pole> pola;

    ifstream plik("dane3.txt");
    if (!plik.is_open()) {
        cout << "Nie mozna otworzyc pliku!" << endl;
        return 1;
    }

    int l_pola;
    plik >> l_pola;

    for (int i = 0; i < l_pola; i++) {
        Pole p;
        int liczba_punktow;
        plik >> p.id >> liczba_punktow >> p.ilosc_jeczmienia;
        
        p.punkty.clear();
        for (int j = 0; j < liczba_punktow; j++) {
            int x, y;
            plik >> x >> y;
            p.punkty.push_back(Punkt(x,y));
        }

        // Oblicz wypukłą otoczkę (na wszelki wypadek)
        p.punkty = wypuklaOtoczka(p.punkty);

        pola.push_back(p);
    }

    plik.close();

    double laczna_ilosc_jeczmienia = 0.0;
    for (const auto &p : pola) {
        double pole = poleWielokata(p.punkty);
        double ilosc = pole * p.ilosc_jeczmienia;
        cout << "Pole id=" << p.id << " ma powierzchnie " << pole 
             << " i wyprodukowalo " << ilosc << " jednostek jeczmienia." << endl;

        laczna_ilosc_jeczmienia += ilosc;
    }

    cout << "Laczna ilosc jeczmienia na wszystkich polach: " << laczna_ilosc_jeczmienia << endl;

    return 0;
}