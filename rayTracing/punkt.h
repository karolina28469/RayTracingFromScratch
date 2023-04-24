#ifndef PUNKT_H
#define PUNKT_H

class Wektor;

/**
 * @brief Definiuje punkt w przestrzeni trójwymiarowej
 * @param x, y, z współrzędne punkta
 */
class Punkt
{
public:
    double x;
    double y;
    double z;

    Punkt() : x(0), y(0), z(0) {}
    Punkt(double x, double y, double z) : x(x), y(y), z(z) {}

    Punkt dodajWektor(Wektor w);
    void obrocKamere(double katY, Punkt srodek = Punkt(0, 0, 0));
};

#endif // PUNKT_H
