#ifndef SCENA_H
#define SCENA_H

#include "bryla.h"
#include "swiatlo.h"

#include <QVector>

/**
 * @brief Pozwala na stworzenie: tablicy obiektów jednej sceny oraz tablicy źródeł świateł w scenie
 */
class Scena
{
private:
    QVector<Bryla*> obiekty;
    QVector<Swiatlo*> swiatla;
    QColor kolor = QColor(255, 255, 255);

public:
    double katA = 0;
    double promien = 10;

    Scena();
    ~Scena();

    void dodajObiekt(Bryla* obiekt);
    Bryla* dajObiekt(int i);
    int liczbaObiektow();

    void dodajSwiatlo(Swiatlo* swiatlo);
    Swiatlo* dajSwiatlo(int i);
    int liczbaSwiatel();

    void ustawKolorTla(QColor kolor);
    QColor dajKolorTla();
};

#endif // SCENA_H
