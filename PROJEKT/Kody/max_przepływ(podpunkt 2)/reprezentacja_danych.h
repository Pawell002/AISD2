#ifndef REPREZENTACJA_DANYCH_H
#define REPREZENTACJA_DANYCH_H
#include <iostream>
#include <vector>
#include <map>

struct Pole {
    int id;
    double x;
    double y;
    double ilosc_jeczmienia;
};

struct Browar {
    int id;
    double x;
    double y;
    double pojemnosc;
};

struct Karczma {
    int id;
    double x;
    double y;
    double zapotrzebowanie;
};

struct Droga {
    int id;
    int zrodlo_id;
    int cel_id;
    std::string produkt;
    double przepustowosc;
    double koszt_naprawy;
};

#endif
