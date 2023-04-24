#ifndef SWIATLO_H
#define SWIATLO_H

#include "punkt.h"
#include "wektor.h"


/**
 * @brief Klasa umożliwiająca zdefiniowanie światła w scenie.
 * @param typ rodzaj światła: dookólne, kierunkowe, punktowe
 * @param intensywnosc intensywność światła; zazwyczaj wartości 0 - 1
 * @param zrodlo źródło światła punktowego
 * @param kierunek kierunek padania światła kierunkowego
 */
class Swiatlo
{
public:
    enum Typ { DOOKOLNE, KIERUNKOWE, PUNKTOWE };
    Typ typ;
    double intensywnosc;
    Punkt zrodlo;
    Wektor kierunek;

    Swiatlo() {}
    Swiatlo(double i) : typ(DOOKOLNE), intensywnosc(i) {}
    Swiatlo(double i, Wektor k) : typ(KIERUNKOWE), intensywnosc(i), kierunek(k) {}
    Swiatlo(double i, Punkt p) : typ(PUNKTOWE), intensywnosc(i), zrodlo(p) {}
};

#endif // SWIATLO_H
