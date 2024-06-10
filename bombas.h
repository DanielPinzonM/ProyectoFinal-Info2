#ifndef BOMBAS_H
#define BOMBAS_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QRandomGenerator>

class bombas:public QObject
{
    Q_OBJECT
private:

    QTimer *tiempomover;
    int danio = 20;
    QGraphicsPixmapItem *Imagen;

public:

    bombas();
    int getdanio();
    QGraphicsPixmapItem* GetImagen();
    ~bombas();

public slots:
    void mover();
};

#endif // BOMBAS_H
