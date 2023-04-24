#include "kolor.h"

QColor Kolor::przyciemnij(double procent, QColor kolor)
{
    int r = int(kolor.red() * procent);
    int g = int(kolor.green() * procent);
    int b = int(kolor.blue() * procent);

    return QColor(std::min(r, 255), std::min(g, 255), std::min(b, 255));
}

QColor Kolor::rozjasnij(double procent, QColor kolor)
{
    int r = kolor.red();
    int g = kolor.green();
    int b = kolor.blue();
    r = int(r + ((255 - r) * procent));
    g = int(g + ((255 - g) * procent));
    b = int(b + ((255 - b) * procent));

    return QColor(std::min(r, 255), std::min(g, 255), std::min(b, 255));
}

QColor Kolor::zmieszajKolory(double procent, QColor kolor1, QColor kolor2)
{
    int r = int(kolor1.red() * (1 - procent) + kolor2.red() * procent);
    int g = int(kolor1.green() * (1 - procent) + kolor2.green() * procent);
    int b = int(kolor1.blue() * (1 - procent) + kolor2.blue() * procent);

    return QColor(std::min(r, 255), std::min(g, 255), std::min(b, 255));
}
