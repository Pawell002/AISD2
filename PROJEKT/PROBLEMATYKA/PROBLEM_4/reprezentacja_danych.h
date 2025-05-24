#ifndef REPREZENTACJA_DANYCH_H
#define REPREZENTACJA_DANYCH_H

#include <iostream>
#include <vector>
#include <string>

// Definicja Punktu (możesz przenieść ją do osobnego pliku, albo do wypukla_otoczka.h)
struct Punkt {
    double x;
    double y;
    Punkt() : x(0), y(0) {}
    Punkt(double _x, double _y) : x(_x), y(_y) {}
};

struct Pole {
    int id;
    std::vector<Punkt> punkty;      // punkty graniczne pola (wielokąt)
    double ilosc_jeczmienia;        // ilość jęczmienia na jednostkę powierzchni
};

struct Browar {
    int id;
    double x;
    double y;
    int pojemnosc;
};

struct Karczma {
    int id;
    double x;
    double y;
    int zapotrzebowanie;
};

struct Droga {
    int id;
    int zrodlo_id;
    int cel_id;
    std::string produkt;
    int przepustowosc;
    int koszt_naprawy;
};

#endif