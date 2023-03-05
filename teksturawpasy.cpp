#include "teksturawpasy.h"
#include "math.h"


QColor TeksturaWPasy::kolorPunktu(Punkt P, QColor kolorP)
{
    int w = int(std::floor(P.x / szerokosc));
    if(w % 2) {
        return kolorP;
    }
    return kolor1;
}
