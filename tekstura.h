#ifndef TEKSTURA_H
#define TEKSTURA_H

#include "punkt.h"
#include <QColor>


/**
 * @brief Umożliwia zdefiniowanie tekstury obieku. Jej wzoru oraz kolorów.
 */
class Tekstura
{
protected:
    double szerokosc = 1; // wielkosc kratki
    QColor kolor1 = QColor(255, 255, 255);
    QColor kolor2 = QColor(128, 128, 128);
    QColor miksujKolory(QColor kolorT, QColor kolorP);

public:
    Tekstura() {}
    virtual ~Tekstura();
    Tekstura(double dlugosc) : szerokosc(dlugosc) {}
    Tekstura(double dlugosc, QColor kolor1, QColor kolor2) :
        szerokosc(dlugosc), kolor1(kolor1), kolor2(kolor2) {}

    virtual QColor kolorPunktu(Punkt P, QColor kolor);
};

#endif // TEKSTURA_H
