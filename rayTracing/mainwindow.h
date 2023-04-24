#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "raytracer.h"
#include "scena.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/**
 * @brief Definiuje ekran wyjściowy programu.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    const int CW = 800, CH = 800;
    QImage* canvas;
    Raytracer* rt;

    int wybranaScena = 1;
    QVector<Scena*> tablicaScen;

    void paintEvent(QPaintEvent *e);
    void zbudujScene();
    QColor tlo(Punkt P, Bryla* sfera);

private slots:
    void slotWybierzScene();
    void slotWybierzSceneCd();
    void slotResetujScene();
    void slotNamalujScene();
};

#endif // MAINWINDOW_H
