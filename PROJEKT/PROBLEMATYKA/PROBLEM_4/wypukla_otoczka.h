#ifndef WYPUKLA_OTOCZKA_H
#define WYPUKLA_OTOCZKA_H

#include <vector>
#include <algorithm>
#include <cmath>

struct Punkt {
    double x, y;
    Punkt() : x(0), y(0) {}
    Punkt(double _x, double _y) : x(_x), y(_y) {}
};

// Iloczyn wektorowy OA x OB (orientacja trójki punktów)
double cross(const Punkt &O, const Punkt &A, const Punkt &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Funkcja wyznacza wypukłą otoczkę (convex hull) algorytmem Andrew
// zwraca punkty w kolejności przeciwnokretnej (CCW)
std::vector<Punkt> wypuklaOtoczka(std::vector<Punkt> &punkty) {
    int n = (int)punkty.size();
    if (n <= 1) return punkty;

    // Sortujemy punkty po x, a potem po y rosnąco
    std::sort(punkty.begin(), punkty.end(), [](const Punkt &a, const Punkt &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    std::vector<Punkt> dolna, gorna;

    // Budujemy dolną część otoczki
    for (const auto &p : punkty) {
        while ((int)dolna.size() >= 2 && cross(dolna[dolna.size()-2], dolna[dolna.size()-1], p) <= 0)
            dolna.pop_back();
        dolna.push_back(p);
    }

    // Budujemy górną część otoczki
    for (int i = n - 1; i >= 0; i--) {
        while ((int)gorna.size() >= 2 && cross(gorna[gorna.size()-2], gorna[gorna.size()-1], punkty[i]) <= 0)
            gorna.pop_back();
        gorna.push_back(punkty[i]);
    }

    // Usuwamy ostatnie punkty obu łańcuchów aby nie powtarzać punktów na styku
    dolna.pop_back();
    gorna.pop_back();

    // Sklejamy dolną i górną część w jeden wielokąt wypukły
    dolna.insert(dolna.end(), gorna.begin(), gorna.end());

    return dolna;
}

// Oblicz pole wielokąta metodą Shoelace'a
double poleWielokata(const std::vector<Punkt> &wielokat) {
    double pole = 0.0;
    int n = (int)wielokat.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        pole += wielokat[i].x * wielokat[j].y - wielokat[j].x * wielokat[i].y;
    }
    return std::abs(pole) / 2.0;
}

#endif // WYPUKLA_OTOCKA_H
