#ifndef WYPUKLA_OTOCZKA_H
#define WYPUKLA_OTOCZKA_H

#include <vector>

struct Punkt {
    double x, y;
    Punkt() : x(0), y(0) {}
    Punkt(double _x, double _y) : x(_x), y(_y) {}
};

// Funkcje zadeklarowane – definicje są w wypukla_otoczka.cpp
std::vector<Punkt> wypuklaOtoczka(std::vector<Punkt> &punkty);
double poleWielokata(const std::vector<Punkt> &wielokat);

#endif // WYPUKLA_OTOCZKA_H

