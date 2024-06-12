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
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include "jugador.h"
#include "enemigo.h"
#include "avion.h"
#include "bomba.h"
#include "explosion.h"
#include "proyectil.h"

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
    QTimer* EsperaEnemigos;
    QList<avion*> Aviones;
    QList<bomba*> Bombas;
    QList<explosion*> Explosiones;
    QList<QGraphicsPixmapItem*> Barricadas;
    QList<proyectil*> Proyectiles;
    QList<proyectil*> ProyectilesEnemigos;
    QList<enemigo*> Enemigos;
    short int TiempoAvion;
    QGraphicsTextItem* MarcadorVida;
    bool colision = false;
    bool Derrotado;
    bool Victorioso;
    QGraphicsPixmapItem* Aviso;

public:
    Nivel2();
    QGraphicsScene* getEscena();

    void CrearMarcador();
    void Iniciar();
    void AgregarTecla(QKeyEvent* event);
    void RemoverTecla(QKeyEvent* event);
    void EventoMouse(QMouseEvent* event);
    void LimpiarEscena();

public slots:
    void Actualizar();
    void GenerarAvion();
    void LanzarBomba(int x, int y, bool MPositivo);
    void DisiparExplosion(explosion*);
    void EliminarProyectil(proyectil*);
    void GenerarEnemigos();
    void ProyectilEnemigo(short int x, short int y);
    void Victoria();
    void Derrota();
};

#endif // NIVEL2_H