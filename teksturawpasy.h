#ifndef TEKSTURAWPASY_H
#define TEKSTURAWPASY_H

#include "tekstura.h"


/**
 * @brief Klasa pochodna klasy Tekstura. Umożliwia stworzenie pasiastej tekstury.
 * Pozwala ustalić szerokość pasów oraz ich kolor.
 */
class TeksturaWPasy : public Tekstura
{
public:
    TeksturaWPasy() {}
    TeksturaWPasy(double dlugosc) : Tekstura(dlugosc) {}
    QColor kolorPunktu(Punkt P, QColor kolorP);
    TeksturaWPasy(double dlugosc, QColor kolor1, QColor kolor2) : Tekstura(dlugosc, kolor1, kolor2) {}
};

#endif // TEKSTURAWPASY_H
