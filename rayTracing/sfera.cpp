#include "sfera.h"
#include "math.h"


Pierwiastki Sfera::znajdzPunktyPrzeciecia(Punkt O, Wektor D)
{
    double a, b, c;
    double delta, t1 = 0, t2 = 0;

    Wektor CO(srodek, O);

    a = Wektor::iloczynSkalarny(D, D);
    b = 2 * Wektor::iloczynSkalarny(CO, D);
    c = Wektor::iloczynSkalarny(CO, CO) - promien * promien;

    delta = b * b - 4 * a * c;
    if(delta > 0)
    {
        t1 = (-b + sqrt(delta)) / (2 * a);
        t2 = (-b - sqrt(delta)) / (2 * a);
    }
    else if (delta == 0.0) {
        t1 = -b / (2 * a);
        t2 = t1;
    }
    return Pierwiastki(t1, t2, delta);
}

/**
 * Wylicza normalna w punkcie P w kierunku na zewnatrz sfery
 * @brief Sfera::wyznaczNormalna
 * @param Punkt P
 * @return Wektor wektor normalny
 */
Wektor Sfera::wyznaczNormalna(Punkt P)
{
    Wektor N = Wektor(srodek, P);
    return N.normalizuj();
}


