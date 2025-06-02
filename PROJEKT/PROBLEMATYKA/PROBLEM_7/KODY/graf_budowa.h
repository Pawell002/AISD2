#ifndef GRAF_BUDOWA_H
#define GRAF_BUDOWA_H
#include <vector>
#include "reprezentacja_danych.h"

struct Krawedz {
    int do_id;
    int odwrotna;
    int pojemnosc;
    int koszt;
    int przeplyw;
};

void dodaj_krawedz(std::vector<std::vector<Krawedz>>& graf, int z,int doo, int pojemnosc, int koszt);

void zbuduj_graf(std::vector<Pole>& pola, std::vector<Browar>& browary,std::vector<Karczma>& karczmy, std::vector<Droga>& drogi,std::vector<std::vector<Krawedz>>& graf,int& start,int& koniec);

#endif

