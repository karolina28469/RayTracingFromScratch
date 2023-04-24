#ifndef WEKTOR_H
#define WEKTOR_H

#include "punkt.h"


/**
 * @brief Klasa pomocnicza. Definiuje niezbędne operacje na wektorach.
 * @param x, y, z długość składowych wektora w każdym kierunku dla trójwymiarowego układu współrzędnych.
 */
class Wektor
{
public:
    double x;
    double y;
    double z;

    Wektor() : x(0), y(0), z(0) {}
    Wektor(double x, double y, double z) : x(x), y(y), z(z) {}
    Wektor(Punkt a, Punkt b) : x(b.x - a.x), y(b.y - a.y), z(b.z - a.z) {}

    Wektor normalizuj();
    Wektor przeciwny();
    Wektor razyLiczba(double liczba);
    Wektor dodaj(Wektor B);
    double dlugosc();
    static double iloczynSkalarny(Wektor a, Wektor b);
    static Wektor iloczynWektorowy(Wektor a, Wektor b);
};

#endif // WEKTOR_H
