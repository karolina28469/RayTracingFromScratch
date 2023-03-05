#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "plaszczyzna.h"
#include "sfera.h"
#include "tekstura.h"
#include "teksturawpasy.h"
#include "trojkat.h"

#include <QPainter>
#include <QDebug>
#include <cmath>
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->kat->setTracking(false);
    connect(ui->kat, SIGNAL(valueChanged(int)), this, SLOT(slotNamalujScene()));
    ui->promien->setTracking(false);
    connect(ui->promien, SIGNAL(valueChanged(int)), this, SLOT(slotNamalujScene()));

    connect(ui->btnResetujScene, SIGNAL(clicked()), this, SLOT(slotResetujScene()));

    connect(ui->radioBtn1, SIGNAL(clicked()), this, SLOT(slotWybierzScene()));
    connect(ui->radioBtn2, SIGNAL(clicked()), this, SLOT(slotWybierzScene()));
    connect(ui->radioBtn3, SIGNAL(clicked()), this, SLOT(slotWybierzScene()));
    connect(ui->radioBtn4, SIGNAL(clicked()), this, SLOT(slotWybierzScene()));
    connect(ui->radioBtn5, SIGNAL(clicked()), this, SLOT(slotWybierzScene()));
    connect(ui->radioBtn6, SIGNAL(clicked()), this, SLOT(slotWybierzScene()));

    connect(ui->cbScena, SIGNAL(currentIndexChanged(int)), this, SLOT(slotWybierzSceneCd()));

    canvas = new QImage(CW, CH, QImage::Format_RGB32);
    canvas->fill("white");

    ui->lblKat->setText(QString::number(ui->kat->value() % 360) + "\u00B0");
    ui->lblCzekaj->setVisible(true);

    zbudujScene();

    qDebug() << "namalujScene()";

    QElapsedTimer timer;
    timer.start();

    rt = new Raytracer(canvas);

    //    ui->cbScena->setCurrentIndex(ui->cbScena->count() - 1); slotWybierzSceneCd();
    slotWybierzScene();

    qDebug() << "czas:" << timer.elapsed() << "ms (" << timer.nsecsElapsed() << "ns )";

    ui->lblCzekaj->setVisible(false);
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < tablicaScen.size(); i++) {
        delete tablicaScen[i];
    }
    delete ui;
}

void MainWindow::slotWybierzScene()
{
    wybranaScena = 1;
    if(ui->radioBtn1->isChecked()) { wybranaScena = 1; }
    if(ui->radioBtn2->isChecked()) { wybranaScena = 2; }
    if(ui->radioBtn3->isChecked()) { wybranaScena = 3; }
    if(ui->radioBtn4->isChecked()) { wybranaScena = 4; }
    if(ui->radioBtn5->isChecked()) { wybranaScena = 5; }
    if(ui->radioBtn6->isChecked()) { wybranaScena = 6; }

    ui->cbScena->blockSignals(true);
    ui->cbScena->setCurrentIndex(-1);
    ui->cbScena->blockSignals(false);
    slotResetujScene();
}

void MainWindow::slotWybierzSceneCd()
{
    wybranaScena = ui->cbScena->currentIndex() + 1 + 6; // przesuniecie o riadio
    slotResetujScene();
}

void MainWindow::slotResetujScene()
{
    ui->promien->blockSignals(true);
    ui->promien->setValue(int(tablicaScen[wybranaScena]->promien));
    ui->promien->blockSignals(false);

    ui->kat->blockSignals(true);
    ui->kat->setValue(int(tablicaScen[wybranaScena]->katA));
    ui->kat->blockSignals(false);

    slotNamalujScene();
}

void MainWindow::slotNamalujScene()
{
    ui->lblCzekaj->blockSignals(true);
    ui->lblCzekaj->setVisible(true);
    ui->lblCzekaj->blockSignals(false);
    repaint();

    ui->lblPromien->setText(QString::number(ui->promien->value()));
    ui->lblKat->setText(QString::number(ui->kat->value() % 360) + "\u00B0");

    rt->namalujScene(tablicaScen[wybranaScena], ui->kat->value(), 10 - ui->promien->value());

    ui->lblCzekaj->blockSignals(true);
    ui->lblCzekaj->setVisible(false);
    ui->lblCzekaj->blockSignals(false);

    qDebug() << "malowanie sceny " << wybranaScena;
    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(50, 50, *canvas);
}

void MainWindow::zbudujScene()
{
    Scena* scena;
    Tekstura* tlo;

    ui->cbScena->blockSignals(true);

    { // 0
        scena = new Scena();
        tablicaScen.push_back(scena);
    }

    { // 1 sfery nad podloga
        scena = new Scena();
        scena->promien = 6;
        scena->katA = 330;

        scena = new Scena();
        scena->promien = 18;
        scena->katA = 25;

        tlo = new Tekstura(1, QColor("white"), QColor("gray"));
        Plaszczyzna* obiekt = new Plaszczyzna(Punkt(0, 0, 20), Punkt(1, 0, 20), Punkt(0, 1, 22), QColor("grey"), 0, 0);
        obiekt->dodajTeksture(tlo);
        scena->dodajObiekt(obiekt);
        scena->dodajObiekt(new Sfera(Punkt(-2, 0, 8), 3, QColor(0xff, 0x40, 0xff), -1, 0.2));
        scena->dodajObiekt(new Sfera(Punkt(-6, 4, 18), 2, QColor(0xd0, 0xd0, 0xd0), -1, 0.95));
        scena->dodajSwiatlo(new Swiatlo(0.2));
        scena->dodajSwiatlo(new Swiatlo(0.8, Punkt(-10, 10.5, 5)));
        tablicaScen.push_back(scena);
    }

    { // 2 - pszczolka
        scena = new Scena();
        scena->promien = 18;
        scena->katA = 19;
        scena->dodajObiekt(new Trojkat(Punkt(-200, -20, 20), Punkt(200, -20, 20), Punkt(0, 200, 20), QColor("white"), 0, 0));

        tlo = new TeksturaWPasy(0.4, QColor(248, 243, 53), QColor(0, 0, 0));
        Sfera* obiekt = new Sfera(Punkt(0, 0, 15), 4, QColor("black"), 0, 0);
        obiekt->dodajTeksture(tlo);
        scena->dodajObiekt(obiekt);

        scena->dodajObiekt(new Sfera(Punkt(-2.6, 0, 14.5), 1.5, QColor("black"), -1, 0));

        scena->dodajObiekt(new Sfera(Punkt(-3, -1, 13), 0.8, QColor("black"), -1, 0));
        scena->dodajObiekt(new Sfera(Punkt(-3.2, -1, 12.6), 0.4, QColor("white"), -1, 0));
        scena->dodajObiekt(new Sfera(Punkt(-3.4, -1, 12.3), 0.1, QColor("black"), -1, 0));

        scena->dodajObiekt(new Sfera(Punkt(-3, 1, 13), 0.8, QColor("black"), -1, 0));
        scena->dodajObiekt(new Sfera(Punkt(-3.2, 1, 12.6), 0.4, QColor("white"), -1, 0));
        scena->dodajObiekt(new Sfera(Punkt(-3.4, 1, 12.3), 0.1, QColor("black"), -1, 0));

        scena->dodajObiekt(new Sfera(Punkt(3, 0, 15), 2, QColor("black"), -1, 0));


        Bryla* obiekt2;
        Punkt a(4, -1, 15), b(6, 0, 15), c(4, 1, 15), d(4, 0, 16);
        obiekt2 = new Trojkat(b, a, c, QColor("black"), 0, 0);
        scena->dodajObiekt(obiekt2);
        obiekt2 = new Trojkat(a, d, c, QColor("black"), 0, 0);
        scena->dodajObiekt(obiekt2);
        obiekt2 = new Trojkat(d, b, c, QColor("black"), 0, 0);
        scena->dodajObiekt(obiekt2);
        obiekt2 = new Trojkat(a, b, d, QColor("black"), 0, 0);
        scena->dodajObiekt(obiekt2);


        Punkt e(-2, 3, 15), f(2, 3, 15), g(0, 8, 15), h(0, 4, 16);

        obiekt2 = new Trojkat(e, f, g, QColor("skyBlue"), 0, 0);
        scena->dodajObiekt(obiekt2);
        obiekt2 = new Trojkat(e, h, g, QColor("skyBlue"), 0, 0);
        scena->dodajObiekt(obiekt2);
        obiekt2 = new Trojkat(f, h, g, QColor("skyBlue"), 0, 0);
        scena->dodajObiekt(obiekt2);
        obiekt2 = new Trojkat(e, f, h, QColor("skyBlue"), 0, 0);
        scena->dodajObiekt(obiekt2);


        Punkt i(-2, -3, 15), j(2, -3, 15), k(0, -8, 15), l(0, -4, 16);
        obiekt2 = new Trojkat(j, i, k, QColor("skyBlue"), 0, 0);
        scena->dodajObiekt(obiekt2);
        obiekt2 = new Trojkat(i, l, k, QColor("skyBlue"), 0, 0);
        scena->dodajObiekt(obiekt2);
        obiekt2 = new Trojkat(j, l, k, QColor("skyBlue"), 0, 0);
        scena->dodajObiekt(obiekt2);
        obiekt2 = new Trojkat(i, j, l, QColor("skyBlue"), 0, 0);
        scena->dodajObiekt(obiekt2);


        scena->dodajSwiatlo(new Swiatlo(0.4));
        scena->dodajSwiatlo(new Swiatlo(0.8, Punkt(-10, 10.5, -5)));
        tablicaScen.push_back(scena);
    }

    { // 3
        scena = new Scena();
        scena->katA = 330;

        tlo = new Tekstura(1, QColor("white"), QColor("gray"));
        Plaszczyzna* obiekt = new Plaszczyzna(Punkt(0, 0, 20), Punkt(1, 0, 20), Punkt(0, 1, 22), QColor("grey"), 0, 0);
        obiekt->dodajTeksture(tlo);
        scena->dodajObiekt(obiekt);
        scena->dodajObiekt(new Sfera(Punkt(-12, 2, 21), 1, QColor("cyan"), 500, 0.03));
        scena->dodajObiekt(new Sfera(Punkt(5, 1.4, 20), 1, QColor("orange"), 500, 0.03));
        scena->dodajObiekt(new Sfera(Punkt(-2, 1.4, 15), 1, QColor("green"), 500, 0.03));
        scena->dodajObiekt(new Sfera(Punkt(-2, 0, 8), 1, QColor("yellow"), 500, 0.03));
        scena->dodajObiekt(new Sfera(Punkt(2, 5, 16), 1, QColor("blue"), 500, 0.03));
        scena->dodajObiekt(new Sfera(Punkt(-4, 1, 13), 1, QColor("red"), 500, 0.03));
        scena->dodajObiekt(new Sfera(Punkt(-6, 4, 18), 2, QColor(0xd0, 0xd0, 0xd0), -1, 0.95));
        scena->dodajSwiatlo(new Swiatlo(0.2));
        scena->dodajSwiatlo(new Swiatlo(0.8, Punkt(-10, 10.5, 5)));
        tablicaScen.push_back(scena);
    }

    { // 4 kula o powierzchni lustrzanej
        scena = new Scena();
        scena->promien = 14;
        scena->katA = 95;

        tlo = new Tekstura(1, QColor("white"), QColor("gray"));
        Plaszczyzna* obiekt = new Plaszczyzna(Punkt(0, 0, 20), Punkt(1, 0, 20), Punkt(0, 1, 22), QColor("darkRed"), 0, 0);
        obiekt->dodajTeksture(tlo);
        scena->dodajObiekt(obiekt);
        scena->dodajObiekt(new Sfera(Punkt(-2, 0, 8), 3, QColor(0xff, 0x40, 0xff), -1, 0.95));
        scena->dodajObiekt(new Sfera(Punkt(-6, 4, 18), 2, QColor(0xd0, 0xd0, 0xd0), -1, 0.95));
        scena->dodajSwiatlo(new Swiatlo(0.2));
        scena->dodajSwiatlo(new Swiatlo(0.8, Punkt(-10, 10.5, 5)));
        tablicaScen.push_back(scena);
    }

    { // 5
        scena = new Scena();

        scena->dodajObiekt(new Plaszczyzna(Punkt(0, 0, 20), Punkt(1, 0, 20), Punkt(0, 1, 20), QColor(255, 215, 0), 100, 0));
        scena->dodajObiekt(new Sfera(Punkt(0, -100, 50), 102, QColor(255, 230, 95), 0, 0));
        scena->dodajObiekt(new Sfera(Punkt(0, -3, 15), 2, QColor("red"), 500, 0.1));
        scena->dodajObiekt(new Sfera(Punkt(0, 0.5, 15), 1, QColor("red"), 50, 0));
        scena->dodajObiekt(new Sfera(Punkt(0, 2.2, 15), 0.5, QColor("red"), 500, 0.1));

        scena->dodajObiekt(new Sfera(Punkt(-2.2, -1, 15), 0.5, QColor("red"), 200, 0.2));
        scena->dodajObiekt(new Sfera(Punkt(-2.2, -2, 15), 0.5, QColor("red"), 10, 0.03));
        scena->dodajObiekt(new Sfera(Punkt(-2.2, -3, 15), 0.5, QColor("red"), 500, 0));
        scena->dodajObiekt(new Sfera(Punkt(-2.2, -6, 15), 0.5, QColor("red"), -1, 1));

        scena->dodajSwiatlo(new Swiatlo(0.2));
        scena->dodajSwiatlo(new Swiatlo(0.8, Punkt(-10, 10.5, 5)));
        tablicaScen.push_back(scena);
    }

    { // 6 kule
        scena = new Scena();
        scena->promien = 11;
        scena->katA = 6;

        Tekstura* tlo = new Tekstura(1000, QColor("white"), QColor("gray"));
        Sfera* obiekt = new Sfera(Punkt(0, 0, 0), 10000, QColor(193, 168, 139), -1, 0);
        obiekt->dodajTeksture(tlo);
        scena->dodajObiekt(obiekt);

        scena->dodajObiekt(new Sfera(Punkt(0, -0.3, 5), 1, QColor(115, 2, 2), 200, 0.1));
        scena->dodajObiekt(new Sfera(Punkt(-2, -2, 7), 0.81, QColor(191, 4, 4), 100, 0));
        scena->dodajObiekt(new Sfera(Punkt(1, 2.5, 16), 4.85, QColor(217, 121, 4), 150, 0));
        scena->dodajObiekt(new Sfera(Punkt(-2, 0, 5), 0.8, QColor(242, 159, 5), -1, 0.4));
        scena->dodajObiekt(new Sfera(Punkt(1.1, -1.3, 4), 0.6, QColor(217, 181, 4), -1, 0));

        scena->dodajSwiatlo(new Swiatlo(0.2));
        scena->dodajSwiatlo(new Swiatlo(0.4, Wektor(Punkt(6, 10.5, 0), Punkt(1, 2.5, 16))));
        scena->dodajSwiatlo(new Swiatlo(0.5, Punkt(-6, 10.5, 0)));
        tablicaScen.push_back(scena);
    }

    { // 7
        ui->cbScena->addItem("nieoświetlona kula - 1. krok");
        scena = new Scena();
        scena->dodajObiekt(new Sfera(Punkt(0, 0, 15), 4, QColor("red"), -1, 0));

        scena->dodajSwiatlo(new Swiatlo(1));
        tablicaScen.push_back(scena);
    }

    { // 8
        ui->cbScena->addItem("oświetlona matowa kula - 2. krok");

        scena = new Scena();
        scena->dodajObiekt(new Sfera(Punkt(0, 0, 15), 4, QColor("green"), -1, 0));

        scena->dodajSwiatlo(new Swiatlo(0.2));
        scena->dodajSwiatlo(new Swiatlo(1, Punkt(-10, 10, 0)));
        tablicaScen.push_back(scena);
    }

    { // 9
        ui->cbScena->addItem("niebieska błyszcząca kula");

        scena = new Scena();
        scena->ustawKolorTla(QColor(0, 0, 0));
        scena->dodajObiekt(new Sfera(Punkt(0, 0, 15), 4, QColor("blue"), 200, 0));

        scena->dodajSwiatlo(new Swiatlo(0.2));
        scena->dodajSwiatlo(new Swiatlo(1, Punkt(-10, 10, 0)));
        tablicaScen.push_back(scena);
    }

    { // 10
        ui->cbScena->addItem("lustrzana sfera w sferze z teksturą");
        scena = new Scena();
        Tekstura* tlo = new Tekstura(1000, QColor("white"), QColor("black"));
        Sfera* obiekt = new Sfera(Punkt(0, 0, 0), 10000, QColor("black"), -1, 0);
        obiekt->dodajTeksture(tlo);
        scena->dodajObiekt(obiekt);
        scena->promien = 10;
        scena->katA = 24;

        scena->dodajObiekt(new Sfera(Punkt(-2, 0, 5), 1.5, QColor(222, 222, 222), 100, 0.9));
        scena->dodajSwiatlo(new Swiatlo(0.2));
        scena->dodajSwiatlo(new Swiatlo(0.5, Punkt(-10, 10.5, 5)));
        scena->dodajSwiatlo(new Swiatlo(0.5, Wektor(Punkt(15, 5, 10), Punkt(10, 3, 16))));
        tablicaScen.push_back(scena);
    }

    { // 11
        ui->cbScena->addItem("błyszcząca kula plus cień");
        scena = new Scena();
        scena->ustawKolorTla(QColor(255, 255, 255));

        scena->dodajObiekt(new Plaszczyzna(Punkt(0, -6, 0), Punkt(1, -6, 0), Punkt(1, -6, 1), QColor("white"), 0, 0));
        scena->dodajObiekt(new Sfera(Punkt(0, 0, 15), 4, QColor(255, 66, 255), 100, 0));

        scena->dodajSwiatlo(new Swiatlo(0.35));
        scena->dodajSwiatlo(new Swiatlo(0.8, Punkt(-15, 20, 0)));
        scena->dodajSwiatlo(new Swiatlo(0.3, Wektor(Punkt(-15, 20, 0), Punkt(0, 0, 15))));

        tablicaScen.push_back(scena);
    }

    { // 12
        ui->cbScena->addItem("demonstracja cieni");
        scena = new Scena();
        scena->promien = 15;
        scena->katA = 30;
        scena->ustawKolorTla(QColor(255, 255, 255));

        scena->dodajObiekt(new Plaszczyzna(Punkt(0, -6, 0), Punkt(1, -6, 0), Punkt(1, -6, 1), QColor("white"), 0, 0));
        scena->dodajObiekt(new Sfera(Punkt(-4, 4, 12), 1, QColor(113, 255, 0), 100, 0));
        scena->dodajObiekt(new Sfera(Punkt(0, 0, 15), 3.5, QColor(0, 128, 255), -1, 0));


        scena->dodajSwiatlo(new Swiatlo(0.35));
        scena->dodajSwiatlo(new Swiatlo(0.8, Punkt(-15, 20, 0)));
        scena->dodajSwiatlo(new Swiatlo(0.3, Wektor(Punkt(-15, 20, 0), Punkt(0, 0, 15))));

        tablicaScen.push_back(scena);
    }

    { // 13
        ui->cbScena->addItem("wielokrotne odbicia lustrzane");
        scena = new Scena();
        scena->promien = 14;
        scena->katA = 96;

        Tekstura* tlo = new Tekstura(5, QColor(293, 168, 139), QColor("gray")); // ciemny 293, 168, 139
        Sfera* obiekt = new Sfera(Punkt(0, -100, 50), 102, QColor(193, 168, 139), 0, 0); // bez 193, 168, 139
        obiekt->dodajTeksture(tlo);
        scena->dodajObiekt(obiekt);

        scena->dodajObiekt(new Sfera(Punkt(7, 1.3, 7), 5, QColor(113, 255, 0), 200, 0.2));
        scena->dodajObiekt(new Sfera(Punkt(0, -2, 7), 2, QColor(0, 128, 255), 50, 0.1));
        scena->dodajObiekt(new Sfera(Punkt(-2, 3, 13), 2.5, QColor(225, 0, 113), 100, 0.2));

        scena->dodajSwiatlo(new Swiatlo(0.4));
        scena->dodajSwiatlo(new Swiatlo(0.6, Punkt(-6, -1.5, 15)));
        tablicaScen.push_back(scena);
    }

    { // 14
        ui->cbScena->addItem("płaszczyzny");
        scena = new Scena();
        Plaszczyzna* obiekt;
        scena->promien = 23;
        scena->katA = 32;

        obiekt = new Plaszczyzna(Punkt(-1, -2, 19), Punkt(0, -2, 20), Punkt(0, -1, 19), QColor("red"), 0, 0);
        obiekt->dodajTeksture(new Tekstura(1, QColor("white"), QColor("gray")));
        scena->dodajObiekt(obiekt);

        obiekt = new Plaszczyzna(Punkt(0, -2, 20), Punkt(1, -2, 19), Punkt(0, -1, 19), QColor("green"), 0, 0);
        obiekt->dodajTeksture(new Tekstura(1, QColor("black"), QColor("gray")));
        scena->dodajObiekt(obiekt);

        obiekt = new Plaszczyzna(Punkt(-1, -3, 19), Punkt(1, -3, 19), Punkt(0, -2, 20), QColor("yellow"), 0, 0);
        obiekt->dodajTeksture(new Tekstura(1, QColor("darkGrey"), QColor("gray")));
        scena->dodajObiekt(obiekt);

        obiekt = new Plaszczyzna(Punkt(0, -5, 15), Punkt(1, -5, 15), Punkt(0, 5, 15), QColor("yellow"), 0, 0);
        obiekt->dodajTeksture(new Tekstura(1, QColor("blue"), QColor("cyan")));
        scena->dodajObiekt(obiekt);

        scena->dodajSwiatlo(new Swiatlo(0.8));
        scena->dodajSwiatlo(new Swiatlo(0.8, Punkt(-10, 10.5, 5)));
        scena->dodajSwiatlo(new Swiatlo(0.6, Wektor(Punkt(15, 5, 10), Punkt(10, 3, 16))));
        tablicaScen.push_back(scena);
    }

    { // 15
        ui->cbScena->addItem("czworościan");
        scena = new Scena();
        Bryla* obiekt;
        Punkt a(-1, -1, 5), b(1, 0, 5), c(0, 2, 5), d(0, 1, 4);

        obiekt = new Trojkat(b, a, c, QColor("red"), 0, 0);
        scena->dodajObiekt(obiekt);

        obiekt = new Trojkat(a, d, c, QColor("red"), 0, 0);
        scena->dodajObiekt(obiekt);

        obiekt = new Trojkat(d, b, c, QColor("red"), 0, 0);
        //        tlo = new Tekstura(0.1, QColor("white"), QColor("gray"));
        //        obiekt->dodajTeksture(tlo);
        scena->dodajObiekt(obiekt);

        obiekt = new Trojkat(a, b, d, QColor("red"), 0, 0);
        scena->dodajObiekt(obiekt);

        scena->dodajSwiatlo(new Swiatlo(0.8));
        scena->dodajSwiatlo(new Swiatlo(0.8, Punkt(-10, 10.5, 5)));
        scena->dodajSwiatlo(new Swiatlo(0.6, Wektor(Punkt(15, 5, 10), Punkt(10, 3, 16))));
        tablicaScen.push_back(scena);
    }

    { // 16
        ui->cbScena->addItem("kula w kratkę w środku obrotu");
        scena = new Scena();

        Sfera* obiekt2 = new Sfera(Punkt(0, 0, 10), 4, QColor(0, 56, 130), -1, 0.2);
        tlo = new Tekstura(0.4, QColor("white"), QColor("black"));
        obiekt2->dodajTeksture(tlo);
        scena->dodajObiekt(obiekt2);

        scena->dodajSwiatlo(new Swiatlo(0.4));
        scena->dodajSwiatlo(new Swiatlo(0.8, Punkt(-10, 10.5, -5)));
        tablicaScen.push_back(scena);
    }

    { // 17
        ui->cbScena->addItem("kula w paski");
        scena = new Scena();

        tlo = new TeksturaWPasy(0.4, QColor("white"), QColor(0, 0, 0));
        Sfera* obiekt = new Sfera(Punkt(0, 0, 15), 4, QColor("red"), 0, 0);
        obiekt->dodajTeksture(tlo);
        scena->dodajObiekt(obiekt);

        scena->dodajSwiatlo(new Swiatlo(0.4));
        scena->dodajSwiatlo(new Swiatlo(0.8, Punkt(-10, 10.5, -5)));
        tablicaScen.push_back(scena);
    }

    { // 18
        ui->cbScena->addItem("balwan - sciana lustrzana");

        scena = new Scena();
        scena->promien = 20;
        scena->katA = 27;

        scena->dodajObiekt(new Plaszczyzna(Punkt(0, 0, 20), Punkt(1, 0, 20), Punkt(0, 1, 20), QColor("cyan"), 0, 1));
        scena->dodajObiekt(new Sfera(Punkt(0, -3, 15), 2, QColor("red"), 500, 0.03));
        scena->dodajObiekt(new Sfera(Punkt(0, 0.5, 15), 1, QColor("red"), 500, 0.03));
        scena->dodajObiekt(new Sfera(Punkt(0, 2.2, 15), 0.5, QColor("red"), 500, 0.03));

        scena->dodajObiekt(new Sfera(Punkt(-2.2, -1, 15), 0.5, QColor("red"), 500, 0.03));
        scena->dodajObiekt(new Sfera(Punkt(-2.2, -2, 15), 0.5, QColor("red"), 500, 0.03));
        scena->dodajObiekt(new Sfera(Punkt(-2.2, -3, 15), 0.5, QColor("red"), 500, 0.03));
        scena->dodajObiekt(new Sfera(Punkt(-2.2, -6, 15), 0.5, QColor("red"), 500, 0.03));
        scena->dodajObiekt(new Sfera(Punkt(2.2, -1, 15), 0.5, QColor("red"), 500, 0.03));

        scena->dodajSwiatlo(new Swiatlo(0.2));
        scena->dodajSwiatlo(new Swiatlo(0.8, Punkt(-10, 10.5, 5)));
        tablicaScen.push_back(scena);
    }

    ui->cbScena->setCurrentIndex(-1);
    ui->cbScena->blockSignals(false);
}
