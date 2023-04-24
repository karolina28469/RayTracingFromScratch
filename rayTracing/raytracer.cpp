#include "raytracer.h"
#include "math.h"
#include "kolor.h"


Raytracer::Raytracer(QImage* canvas) : canvas(canvas)
{
    CW = canvas->width();
    CH = canvas->height();
}

/**
 * @brief Rysuje piksel we wskazanym punkcie na canvasie
 * @param x współrzędna na osi x
 * @param y współrzędna na osi y
 * @param kolor kolor punktu
 */
void Raytracer::rysujPiksel(int x, int y, QColor kolor)
{
    x = CW / 2 + x;
    y = CH / 2 - y;
    canvas->setPixelColor(x, y, kolor);
}

/**
 * @brief Zamienia wspolrzedne canvasu na viewport
 * @param cx długość canvasu
 * @param cy wysokość canvasu
 * @return odpowiadający punkt vieportu
 */
Punkt Raytracer::zamienWspolrzedneCanvasNaViewport(int cx, int cy)
{
    double vx = 1.0 * cx * VW / CW;
    double vy = 1.0 * cy * VH / CH;
    return Punkt(vx, vy, VZ);
}

/**
 * @brief sprawdza czy badany punk znajduje się w cieniu
 * @param P badany punkt
 * @param L wektor swiatla (do punktu)
 * @param tmax INF dla swiatla kierunkowego; 1 dla swiatla punktowego
 * @return czy punkt jest zacieniony
 */
bool Raytracer::jestWCieniu(Punkt P, Wektor L, double tmax, Bryla* obiekt)
{
    bool ret = false;
    Pierwiastki tt;

    for (int i = 0; i < scena->liczbaObiektow(); i++) {
        if(obiekt == scena->dajObiekt(i)) { continue; }

        tt = scena->dajObiekt(i)->znajdzPunktyPrzeciecia(P, L.przeciwny());
        if(tt.delta >= 0) {
            if(tt.t1 < 0 || tt.t2 < 0)  // kamera wewnatrz obiektu
            {
                continue;
            }

            if((tt.t1 >= 0 && tt.t1 <= tmax) ||
                    (tt.t2 >= 0 && tt.t2 <= tmax))
            {
                ret = true;
                break;
            }
        }
    }
    return ret;
}

/**
 * Oblicza wspolczynnik intensywnosci swiatla. W obliczeniach uwzgledniamy kilka rodzajów światła:
 * światła rozproszone - światło dookólne (ambient light), swiatło kierunkowe (directional light)
 * i światło punktowe (point light) oraz światło polyskliwości - swiatło odbicia (specular light)
 * @param Punkt P punkt dla ktorego liczymy współczynnik jasności
 * @param Wektor N normalna punktu
 * @param Wektor V wektor do obserwatora (do oka kamery)
 * @param double polyskliwość wspolczynnik 'metaliczności' obiektu
 * @return double wspolczynnik jasności
 */
double Raytracer::ustalJasnoscSwiatla(Punkt P, Wektor N, Wektor V, Bryla* obiekt)
{
    Swiatlo *swiatlo;
    double ret = 0;
    Wektor L, R;
    double tmax;
    double polyskliwosc = obiekt->polyskliwosc;
    bool obiektWCieniu = false, cienPoliczony = false;

    for (int i = 0; i < scena->liczbaSwiatel(); i++) {
        swiatlo = scena->dajSwiatlo(i);

        if(swiatlo->typ == Swiatlo::DOOKOLNE) { // skladowa swiatla dookolnego
            ret += swiatlo->intensywnosc;
        }
        else
        {
            if (swiatlo->typ == Swiatlo::KIERUNKOWE) { // skladowa swiatla kierunkowego
                L = swiatlo->kierunek;
                tmax = INF;
            }
            else //if (swiatlo->typ == Swiatlo::PUNKTOWE) // skladowa swiatla punktowego
            {
                L = Wektor(swiatlo->zrodlo, P);
                tmax = 1;
            }

            double cosA = Wektor::iloczynSkalarny(N, L.przeciwny()) / sqrt(Wektor::iloczynSkalarny(L, L));
            if(cosA > 0)
            {
                if(!cienPoliczony) {
                    obiektWCieniu = jestWCieniu(P, L, tmax, obiekt);
                    cienPoliczony = true;
                }
                if(!obiektWCieniu)
                {
                    // if(polyskliwosc > 0)
                    {
                        ret += swiatlo->intensywnosc * cosA;
                    }
                }
            }

            if (polyskliwosc > 0) // skladowa metalicznosci
            {
                R = znajdzWektorOdbicia(L, N);
                double cosB = Wektor::iloczynSkalarny(R, V) / (R.dlugosc() * V.dlugosc());
                if(cosB > 0)
                {
                    if(!cienPoliczony) {
                        obiektWCieniu = jestWCieniu(P, L, tmax, obiekt);
                        cienPoliczony = true;
                    }
                    if(!obiektWCieniu)
                    {
                        double intensywnosc = swiatlo->intensywnosc;
                        ret += intensywnosc * pow(cosB, polyskliwosc);
                    }
                }
            }
        }
    }
    return ret;
}

/**
 * @brief RayTracer::znajdzWektorOdbicia
 * @param L wektor padania; skierowany do punktu P
 * @param N normalna w punkcie P
 * @return wektor odbicia R; od punktu P
 */
Wektor Raytracer::znajdzWektorOdbicia(Wektor L, Wektor N)
{
    return N.razyLiczba(2 * Wektor::iloczynSkalarny(L.przeciwny(), N)).dodaj(L);
}

/**
 * @brief Funkcja podąża za promieniem. Bada czy na jego drodze znajdują się jakieś obiekty. Wylicza kolor dla każdego punktu.
 * @param O współrzędne oka kamery
 * @param D wektor kierunkowy promienia świetlnego
 * @param tmin dolna granica dla szukanego pierwiastka
 * @param tmax górna granica dla szukanego pierwiastka
 * @return kolor wyliczonego punktu
 */
QColor Raytracer::sledzPromien(Punkt O, Wektor D, double tmin, double tmax)
{
    double minT = tmax;
    QColor kolor = scena->dajKolorTla(), kolorR(0, 0, 0);
    Pierwiastki minTT(0, 0, -1); // inicializacja tylko dla tła
    Bryla* najblizszyObiekt = nullptr; //najblizsza bryla
    Bryla* at;
    const double epsilon = 1e-12;

    for(int i = 0; i < scena->liczbaObiektow(); i++)
    {
        at = scena->dajObiekt(i);
        Pierwiastki tt = at->znajdzPunktyPrzeciecia(O, D);

        if((tt.t1 > -epsilon && tt.t1 < epsilon) || (tt.t2 > -epsilon && tt.t2 < epsilon)) { continue; }
        if(tt.delta >= 0)
        {
            if((tt.t1 < minT && tt.t1 >= tmin) && (!(tt.t2 >= 0 && tt.t2 < 1) || !(tmin > 0)))
            {
                minT = tt.t1;
                najblizszyObiekt = at;
                minTT = tt;
            }
            if((tt.t2 < minT && tt.t2 >= tmin) && (!(tt.t1 >= 0 && tt.t1 < 1) || !(tmin > 0)))
            {
                minT = tt.t2;
                najblizszyObiekt = at;
                minTT = tt;
            }
        }
    }

    if(najblizszyObiekt != nullptr)
    {
        kolor = najblizszyObiekt->kolor;

        Punkt P = Punkt(O.x + minT * D.x, O.y + minT * D.y, O.z + minT * D.z);
        Wektor N = najblizszyObiekt->wyznaczNormalna(P);

        if(minTT.t1 < 0 || minTT.t2 < 0) // kiedy jestesmy w srodku kuli
        {
            N = N.przeciwny();
        }

        if(najblizszyObiekt->tlo) {
            kolor = najblizszyObiekt->tlo->kolorPunktu(P, kolor); // kolor z tekstura
        }

        // swiatlo
        double i = ustalJasnoscSwiatla(P, N, D.przeciwny(), najblizszyObiekt);

        if(i < 1) {
            kolor = Kolor::przyciemnij(i, kolor);
        }
        else if (i > 1) {
            i = i > 2 ? 1 : i - 1;
            kolor = Kolor::rozjasnij(i, kolor);
        }

        if(najblizszyObiekt->lustro > 0 && liczbaOdbic < MAX_LICZBA_ODBIC)
        {
            liczbaOdbic += 1;
            Wektor R = znajdzWektorOdbicia(D, N);
            kolorR = sledzPromien(P, R, 0, INF);
        }
        kolor = Kolor::zmieszajKolory(najblizszyObiekt->lustro, kolor, kolorR);
    }
    return kolor;
}

/**
 * @brief Ustala pozycję obserwatora. Bada każdy punkt canvasu, wylicza jego kolor i go maluje.
 * @param scena badana scena
 * @param katA kąt alfa obrotu względem osi Y
 * @param promien odleglość oka kamery od środka sceny
 */
void Raytracer::namalujScene(Scena* scena, double katA, double promien)
{
    this->scena = scena;
    Punkt V;
    QColor kolor;

    Punkt O(0, 0, promien);
    O.obrocKamere(katA, Punkt(0, 0, 10));

    for (int cy = CH / 2; cy > -CH / 2; cy--)
    {
        for (int cx = -CW / 2; cx < CW / 2; cx++)
        {
            V = zamienWspolrzedneCanvasNaViewport(cx, cy);
            V.obrocKamere(katA, Punkt(0, 0, 0));
            Wektor D(Punkt(0, 0, 0), V);
            liczbaOdbic = 1;
            kolor = sledzPromien(O, D, 1, INF);
            rysujPiksel(cx, cy, kolor);
        }
    }
}

