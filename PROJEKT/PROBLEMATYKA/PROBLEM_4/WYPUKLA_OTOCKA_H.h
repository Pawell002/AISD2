#ifndef WYPUKLA_OTOCZKA_H
#define WYPUKLA_OTOCZKA_H

#include <vector>

struct Punkt {
    double x, y;
    Punkt();
    Punkt(double _x, double _y);
};

std::vector<Punkt> wypuklaOtoczka(std::vector<Punkt> &punkty);
double poleWielokata(const std::vector<Punkt> &wielokat);

#endif // WYPUKLA_OTOCKA_H
