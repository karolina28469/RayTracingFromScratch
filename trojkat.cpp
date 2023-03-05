#include "plaszczyzna.h"
#include "trojkat.h"

/**
 * Znajdz punkty przeciecia promienia z punktu O w kierunku D z trojkatem.
 * Möller–Trumbore intersection algorithm
 * @brief Trojkat::znajdzPunktyPrzeciecia
 * @param O źrodlo promienia
 * @param D kierunek promienia
 * @return punkt przeciecia
 */
// zrodlo: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
Pierwiastki Trojkat::znajdzPunktyPrzeciecia(Punkt O, Wektor D)
{
    const double EPSILON = 0.0000001;
    Pierwiastki tt(0, 0, -1);

    Wektor Ov(O.x, O.y, O.z);
    Wektor Av(a.x, a.y, a.z);
    Wektor Bv(b.x, b.y, b.z);
    Wektor Cv(c.x, c.y, c.z);

    Wektor AB, AC, h, s, q;
    double e, f, u, v;

    AB = Bv.dodaj(Av.przeciwny());
    AC = Cv.dodaj(Av.przeciwny());

    h = Wektor::iloczynWektorowy(D, AC);
    e = Wektor::iloczynSkalarny(AB, h);
    if (e > -EPSILON && e < EPSILON) {
        return tt; // false - promien jest rownolegly do trojkata
    }

    f = 1.0/e;
    s = Ov.dodaj(Av.przeciwny());
    u = f * Wektor::iloczynSkalarny(s, h);
    if (u < 0.0 || u > 1.0) {
        return tt; // false
    }

    q = Wektor::iloczynWektorowy(s, AB);
    v = f * Wektor::iloczynSkalarny(D, q);
    if (v < 0.0 || u + v > 1.0) {
        return tt; // false
    }

    // wyliczenie t dla punktu przeciecia
    double t = f * Wektor::iloczynSkalarny(AC, q);
    if (t > EPSILON) {
        return Pierwiastki(t, t, 0);
    }
    else {
        return tt; // false
    }
}

Wektor Trojkat::wyznaczNormalna(Punkt)
{
    Wektor ab(a, b);
    Wektor ac(a, c);

    Wektor N = Wektor::iloczynWektorowy(ab, ac);

    return N.normalizuj().przeciwny();
}
