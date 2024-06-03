#ifndef SOLDADO_H
#define SOLDADO_H

#include <QWidget>
#include <QGraphicsPixmapItem>

class soldado : public QWidget
{
    Q_OBJECT

public:
    short int Vida;
    QGraphicsPixmapItem *Imagen;

    soldado();
    short int GetVida();
    QGraphicsPixmapItem* GetImagen();
};

#endif // SOLDADO_H