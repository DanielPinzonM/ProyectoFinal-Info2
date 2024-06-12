#ifndef NIVEL1_H
#define NIVEL1_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QList>
#include <QKeyEvent>
#include "barco.h"
#include "barco_aliado.h"
#include <QTimer>
#include <QWidget>
#include <QObject>
#include <QRandomGenerator>
#include "aviones_enemigos.h"
#include "bombas.h"
#include <QGraphicsTextItem>
#include <QMessageBox>


class Nivel1 : public QObject {

    Q_OBJECT
private:

    QGraphicsScene* Escena;
    Barco* barco;
    QList<Barco_aliado*> barcosaliados;
    QList<QGraphicsRectItem*> Paredes;
    QList<Aviones_Enemigos*> aviones;
    QList<bombas*> bombasE;
    QTimer Actualizar, tiempocreacionbarco, tiempocreacionavion, tiempocreacionbomba;
    QGraphicsSimpleTextItem *VIDA;
    QGraphicsPixmapItem *Fondo, *Fondofinal;

public:

    Nivel1();
    QGraphicsScene* GetEscena();
    void agregarlimites();
    void EventoTeclado(QKeyEvent* e);
    void crearavion();
    void crearbarco();
    void crearbomba();
    void Actualizarjuego();
    void eliminarElementosFueraDePantalla();
    void Mostrarvida();
    void manejarColisiones();
    void aumentarFrecuenciaCreacion();
    ~Nivel1();
signals:

    void juegoTerminado();

};

#endif // NIVEL1_H



