#ifndef GRAF_BUDOWA_H
#define GRAF_BUDOWA_H
#include <vector>
#include "reprezentacja_danych.h"

int macierz_przeplywu(
    std::vector<Pole>& pola,
    std::vector<Browar>& browary,
    std::vector<Karczma>& karczmy,
    std::vector<Droga>& drogi,
    std::vector<std::vector<int>>& macierz
);
#endif
