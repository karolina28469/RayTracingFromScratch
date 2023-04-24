#ifndef BRYLA_H
#define BRYLA_H

#include "pierwiastki.h"
#include "tekstura.h"
#include "wektor.h"

#include <QColor>

/**
 * @brief Klasa bazowa dla wszystkich renderowanych obiektów
 * @param tło tekstura obiektu
 * @param kolor kolor obiektu
 * @param polyskliwosc warość połyskliwości materiału; -1: powierzchnia matowa; 100 - 300: powierzchnia połyskliwa
 * @param lustro współczynnik odbicia lustrzanego materiału; wartości 0 - 1
 */
class Bryla
{
public:
    Tekstura* tlo = nullptr;
    QColor kolor;
    double polyskliwosc;
    double lustro;

    Bryla() {}
    Bryla(QColor kolor, double polyskliwosc, double lustro) :
        kolor(kolor), polyskliwosc(polyskliwosc), lustro(lustro) {}
    virtual ~Bryla();

    /**
     * @brief Znajduje punkty przecięcia promienia świetlnego z bryłą.
     * Zwraca obiekt klasy Pierwiastki zawierający wartość parametru t dla punktów przecięcia oraz deltę.
     * Delta jest równa -1 jeżeli nie ma punktów przecięcia; 0 jeżeli jeżeli jest jeden punkt przecięcia;
     * Wartość 1 jeżeli są dwa punkty przecięcia.
     * @param O współrzędne oka kamery
     * @param D wektor kierunkowy promienia świetlnego
     * @return punkty przecięcia promienia z bryłą
     */
    virtual Pierwiastki znajdzPunktyPrzeciecia(Punkt O, Wektor D) = 0;

    /**
     * @brief Wyznacza wektor normalny do danego punktu obiektu.
     * @param P punkt dla którego wyznaczana jest normalna
     * @return wektor normalnej do punktu P
     */
    virtual Wektor wyznaczNormalna(Punkt P) = 0;

    /**
     * @brief umożliwia nałożenie tekstury na obiekt
     * @param tlo obiekt klasy Tekstura. Zawiera informacje dotyczące tekstury
     */
    void dodajTeksture(Tekstura* tlo);
};

#endif // BRYLA_H
