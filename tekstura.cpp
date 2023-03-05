#include "tekstura.h"
#include "math.h"
#include "kolor.h"

Tekstura::~Tekstura() {}

/**
 * Tlo w postaci kratki - szachownicy
 * @brief Tekstura::kolorPunktu
 * @param P badany punkt
 * @param kolorP kolor obiektu w badanym punkcie
 * @return kolor punktu
 */
QColor Tekstura::kolorPunktu(Punkt P, QColor kolorP)
{
    QColor kolor = kolor1;
    int w = int(std::floor(P.x / szerokosc));
    int k = int(std::floor(P.y / szerokosc));
    if((w + k) % 2) {
        kolor = kolorP;
    }
    return kolor;
}

/**
 * @brief Tekstura::ustalKolor
 * @param kolorT kolor tekstury
 * @param kolorP kolor punktu
 * @return kolor wynikowy
 */
QColor Tekstura::miksujKolory(QColor kolorT, QColor kolorP)
{
    QColor kolor = kolorP;
    double szary = 0.3 * kolorT.red() + 0.6 * kolorT.green() + 0.1 * kolorT.blue();
    double procent = (szary - 128) / 128;
    if(procent > 0) {
        kolor = Kolor::rozjasnij(procent, kolorP);
    }
    else if(procent < 0) {
        kolor = Kolor::przyciemnij(-procent, kolorP);
    }
    return kolor;
}
