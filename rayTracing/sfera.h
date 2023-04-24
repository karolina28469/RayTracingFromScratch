#ifndef SFERA_H
#define SFERA_H

#include "bryla.h"
#include "pierwiastki.h"
#include "punkt.h"
#include "wektor.h"

/**
 * @brief Klasa pochodna klasy Bryla. Umożliwia storzenie obieku typu sfera.
 * @param srodek środek sfery
 * @param promień sfery; odległość od środka punktu do każdego punktu sfery
 */
class Sfera : public Bryla
{
public:
    Punkt srodek;
    double promien;

    Sfera() {}
    Sfera(Punkt srodek, double promien, QColor kolor, double polyskliwosc, double lustro) :
        Bryla(kolor, polyskliwosc, lustro), srodek(srodek), promien(promien) {}

    Pierwiastki znajdzPunktyPrzeciecia(Punkt O, Wektor D);
    Wektor wyznaczNormalna(Punkt P);
};

#endif // SFERA_H
