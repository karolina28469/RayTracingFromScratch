#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "scena.h"

#include <QImage>

/**
 * @brief Zajmuje się wyliczniem parametrów dla poszczególnego punktu canvasu
 */
class Raytracer
{
private:
    const double INF = 1e10;
    int CW, CH;
    const int VW = 1, VH = 1;
    const double VZ = 1.0;
    const int MAX_LICZBA_ODBIC = 3;
    int liczbaOdbic = 0;

    QImage* canvas;
    Scena* scena;

public:
    Raytracer(QImage* canvas);

    void rysujPiksel(int x, int y, QColor kolor);
    Punkt zamienWspolrzedneCanvasNaViewport(int cx, int cy);
    bool jestWCieniu(Punkt P, Wektor L, double tmax, Bryla* obiekt);
    double ustalJasnoscSwiatla(Punkt P, Wektor N, Wektor V, Bryla* obiekt);

    Wektor znajdzWektorOdbicia(Wektor L, Wektor N);
    QColor sledzPromien(Punkt O, Wektor D, double tmin, double tmax);
    void namalujScene(Scena* scena, double katA, double promien);
};

#endif // RAYTRACER_H
