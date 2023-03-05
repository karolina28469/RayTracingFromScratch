#include "scena.h"

Scena::Scena() {}

Scena::~Scena()
{
    for(int i = 0; i < obiekty.size(); i++) {
        delete obiekty[i];
    }
    for(int i = 0; i < swiatla.size(); i++) {
        delete swiatla[i];
    }
}

void Scena::dodajObiekt(Bryla* obiekt)
{
    obiekty.push_back(obiekt);
}

Bryla* Scena::dajObiekt(int i)
{
    return obiekty.at(i);
}

int Scena::liczbaObiektow()
{
    return obiekty.size();
}

void Scena::dodajSwiatlo(Swiatlo* swiatlo)
{
    swiatla.push_back(swiatlo);
}

Swiatlo* Scena::dajSwiatlo(int i)
{
    return swiatla.at(i);
}

int Scena::liczbaSwiatel()
{
    return swiatla.size();
}

void Scena::ustawKolorTla(QColor kolor)
{
    this->kolor = kolor;
}

QColor Scena::dajKolorTla()
{
    return kolor;
}
