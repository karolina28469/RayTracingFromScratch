#include "wektor.h"
#include "math.h"

/**
 * @brief Wyznacza wektor normalny długości 1
 * @return wyliczony wektor normalny
 */
Wektor Wektor::normalizuj()
{
    double r = dlugosc();
    return Wektor(x / r, y / r, z / r);
}

/**
 * @brief Wyznacza wektor przeciwny badanego wektora
 * @return wyliczony wektor przeciwny
 */
Wektor Wektor::przeciwny()
{
    return Wektor(-x, -y, -z);
}

/**
 * @brief Mnoży wektor przez skalar
 * @param liczba skalar
 * @return wyliczony wektor
 */
Wektor Wektor::razyLiczba(double liczba)
{
    return Wektor(x * liczba, y * liczba, z * liczba);
}

/**
 * @brief Dodaje dwa wektory
 * @param B dodawany wektor
 * @return wyliczony wekor
 */
Wektor Wektor::dodaj(Wektor B)
{
    return Wektor(x + B.x, y + B.y, z + B.z);
}

/**
 * @brief Wylicza długość badanego wekora
 * @return długość wektora
 */
double Wektor::dlugosc()
{
    return sqrt(x * x + y * y + z * z);
}

/**
 * @brief Wylicza iloczyn skalarny dla dwóch wektorów
 * @param a pierwszy wektor
 * @param b drugi wektor
 * @return liczba - wynik iloczyny skalarnego
 */
double Wektor::iloczynSkalarny(Wektor a, Wektor b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**
 * @brief Wylicza iloczyn wektorowy dla dwóch wektoróW
 * @param a pierwszy wektor
 * @param b drugi wektor
 * @return wektor - wynik iloczynu wektorowego
 */
Wektor Wektor::iloczynWektorowy(Wektor a, Wektor b)
{
    return Wektor(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
