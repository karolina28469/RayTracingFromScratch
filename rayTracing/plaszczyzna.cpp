#include "plaszczyzna.h"


Pierwiastki Plaszczyzna::znajdzPunktyPrzeciecia(Punkt O, Wektor D)
{
    double delta = -1, t = 0;

    Wektor ab(a, b);
    Wektor ac(a, c);

    Wektor v = Wektor::iloczynWektorowy(ab, ac);

    double dz = (v.x * D.x + v.y * D.y + v.z * D.z);
    if(dz != 0.0) {
        t = (- v.x * O.x + v.x * a.x - v.y * O.y + v.y * a.y - v.z * O.z + v.z * a.z) / dz;
        delta = 0;
    }

    return Pierwiastki(t, t, delta);
}

/**
 * Wylicza normalna w punkcie P
 * @brief Plaszczyzna::wyznaczNormalna
 * @param Punkt P
 * @return Wektor wektor normalny
 */
Wektor Plaszczyzna::wyznaczNormalna(Punkt)
{
    Wektor ab(a, b);
    Wektor ac(a, c);

    Wektor N = Wektor::iloczynWektorowy(ab, ac);

    return N.normalizuj().przeciwny();
}


