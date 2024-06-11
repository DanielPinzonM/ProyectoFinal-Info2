#ifndef NIVEL2_H
#define NIVEL2_H

#include <QGraphicsScene>
#include <QWidget>
#include <QList>
#include <QSet>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QRandomGenerator>
#include "jugador.h"
#include "avion.h"
#include "bomba.h"

class Nivel2 : public QWidget
{
    Q_OBJECT

private:
    QGraphicsScene* Escena = new QGraphicsScene;
    short int ExtremoDerecho;
    short int ExtremoIzquierdo;
    QSet<int> Keys;
    jugador* Jugador;
    QTimer* Refresco;
    QTimer* EsperaAvion;
    QList<avion*> Aviones;
    QList<bomba*> Bombas;
    QList<QGraphicsPixmapItem*> Barricadas;
    short int TiempoAvion;
    bool colision = false;

public:
    Nivel2();
    QGraphicsScene* getEscena();

    void AgregarTecla(QKeyEvent* event);
    void RemoverTecla(QKeyEvent* event);

public slots:
    void Actualizar();
    void GenerarAvion();
    void LanzarBomba(int x, int y, bool MPositivo);
};

#endif // NIVEL2_H