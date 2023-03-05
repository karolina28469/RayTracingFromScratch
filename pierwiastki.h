#ifndef PIERWIASTKI_H
#define PIERWIASTKI_H

/**
 * @brief Grupuje informacje dotyczące punktu przecięcia promienia świetlnego i bryły
 */
class Pierwiastki
{
public:
    double t1;
    double t2;
    double delta;

    Pierwiastki() {}
    Pierwiastki(double t1, double t2, double d) : t1(t1), t2(t2), delta(d) {}
};

#endif // PIERWIASTKI_H
