#ifndef PLASZCZYZNA_H
#define PLASZCZYZNA_H

#include "bryla.h"
#include "pierwiastki.h"
#include "punkt.h"
#include "wektor.h"

/**
 * @brief Klasa pochodna klasy Bryla
 * @param a, b, c trzy punkty niewspółliniowe pozwalające jednoznacznie zdefiniować płaszczyznę
 */
class Plaszczyzna : public Bryla
{
private:
    Punkt a, b, c;

public:
    Plaszczyzna();
    Plaszczyzna(Punkt a, Punkt b, Punkt c) : a(a), b(b), c(c) {}
    Plaszczyzna(Punkt a, Punkt b, Punkt c, QColor kolor, double polyskliwosc, double lustro) :
        Bryla(kolor, polyskliwosc, lustro), a(a), b(b), c(c) {}

    Pierwiastki znajdzPunktyPrzeciecia(Punkt O, Wektor D);
    Wektor wyznaczNormalna(Punkt P);
};

#endif // PLASZCZYZNA_H
