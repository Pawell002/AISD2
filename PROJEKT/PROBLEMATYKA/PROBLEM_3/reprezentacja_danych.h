#ifndef REPREZENTACJA_DANYCH_H
#define REPREZENTACJA_DANYCH_H
#include <iostream>
#include <vector>
#include <map>

struct Pole {
    int id;
    double x;
    double y;
    int ilosc_jeczmienia;
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
