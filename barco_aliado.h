#ifndef BARCO_ALIADO_H
#define BARCO_ALIADO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QTimer>


class Barco_aliado:public QObject
{
    Q_OBJECT
private:
    int danio = 2;
    QGraphicsPixmapItem *Imagen;
    QTimer *tiempomover;


public:
    Barco_aliado();
    ~Barco_aliado();
    int getdanio() const; // Getter para obtener la vida
    QGraphicsPixmapItem* GetImagen();

public slots:
    void mover();
};

#endif // BARCO_ALIADO_H

