#ifndef AVIONES_ENEMIGOS_H
#define AVIONES_ENEMIGOS_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QRandomGenerator>

class Aviones_Enemigos:public QObject
{
    Q_OBJECT
private:
    int danio=10;
    QGraphicsPixmapItem *Imagen;
    QTimer *tiempomover;
public:
    Aviones_Enemigos();
    QGraphicsPixmapItem *GetImagen ();
    int Getdanio();
    ~Aviones_Enemigos();
public slots:
    void mover();
};

#endif // AVIONES_ENEMIGOS_H



