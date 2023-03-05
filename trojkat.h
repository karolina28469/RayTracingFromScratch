#ifndef TROJKAT_H
#define TROJKAT_H

#include "bryla.h"


/**
 * @brief Klasa pochodna klasy Bryla
 * @param a, b, c trzy punkty niewspółliniowe pozwalające jednoznacznie zdefiniować trójkąt
 */
class Trojkat : public Bryla
{
private:
    Punkt a, b, c;

public:
    Trojkat();
    Trojkat(Punkt a, Punkt b, Punkt c, QColor kolor, double polyskliwosc, double lustro) :
        Bryla(kolor, polyskliwosc, lustro), a(a), b(b), c(c) {}

    Pierwiastki znajdzPunktyPrzeciecia(Punkt O, Wektor D);
    Wektor wyznaczNormalna(Punkt P);
};

#endif // TROJKAT_H
