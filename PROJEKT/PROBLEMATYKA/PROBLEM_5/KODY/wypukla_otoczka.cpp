#include "wypukla_otoczka.h"
#include <algorithm>
#include <cmath>

Punkt::Punkt() : x(0), y(0) {}
Punkt::Punkt(double _x, double _y) : x(_x), y(_y) {}

static double cross(const Punkt &O, const Punkt &A, const Punkt &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

std::vector<Punkt> wypuklaOtoczka(std::vector<Punkt> &punkty) {
    int n = punkty.size();
    if (n <= 1) return punkty;

    std::sort(punkty.begin(), punkty.end(), [](const Punkt &a, const Punkt &b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    std::vector<Punkt> dolna, gorna;

    for (const auto &p : punkty) {
        while (dolna.size() >= 2 && cross(dolna[dolna.size()-2], dolna[dolna.size()-1], p) <= 0)
            dolna.pop_back();
        dolna.push_back(p);
    }

    for (int i = n - 1; i >= 0; i--) {
        while (gorna.size() >= 2 && cross(gorna[gorna.size()-2], gorna[gorna.size()-1], punkty[i]) <= 0)
            gorna.pop_back();
        gorna.push_back(punkty[i]);
    }

    dolna.pop_back();
    gorna.pop_back();
    dolna.insert(dolna.end(), gorna.begin(), gorna.end());

    return dolna;
}

double poleWielokata(const std::vector<Punkt> &wielokat) {
    double pole = 0;
    int n = wielokat.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        pole += wielokat[i].x * wielokat[j].y - wielokat[j].x * wielokat[i].y;
    }
    return std::abs(pole) / 2.0;
}
