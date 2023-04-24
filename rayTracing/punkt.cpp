#include "punkt.h"
#include "math.h"
#include "wektor.h"


Punkt Punkt::dodajWektor(Wektor w)
{
    return Punkt(x + w.x, y + w.y, z + w.z);
}

void Punkt::obrocKamere(double katY, Punkt srodek)
{
    double tx = x - srodek.x;
    double ty = y - srodek.y;
    double tz = z - srodek.z;

    katY = katY / 180 * M_PI;
    double ox = tx * cos(katY) + tz * sin(katY);
    double oy = ty;
    double oz = -tx * sin(katY) + tz * cos(katY);

    x = ox + srodek.x;
    y = oy + srodek.y;
    z = oz + srodek.z;
}

