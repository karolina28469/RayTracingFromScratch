#ifndef KOLOR_H
#define KOLOR_H

#include <QColor>

/**
 * @brief Umożliwia zmianę parametrów koloru w danym punkcie
 */
class Kolor
{
public:
    static QColor przyciemnij(double procent, QColor kolor);
    static QColor rozjasnij(double procent, QColor kolor);
    static QColor zmieszajKolory(double procent, QColor kolor1, QColor kolor2);
};

#endif // KOLOR_H
