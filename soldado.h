#ifndef SOLDADO_H
#define SOLDADO_H

#include <QWidget>
#include <QTimer>
#include <QGraphicsPixmapItem>

class soldado : public QWidget
{
    Q_OBJECT

public:
    short int Vida;
    QGraphicsPixmapItem *Imagen;
    QTimer* TiempoAnimar;

    soldado();
    short int GetVida();
    QGraphicsPixmapItem* GetImagen();
    short int GetPosicionX();
    short int GetPosicionY();

    void SetVida(short int vida);
    void SetPosicion(short int x, short int y);
};

#endif // SOLDADO_H