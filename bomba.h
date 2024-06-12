#ifndef BOMBA_H
#define BOMBA_H

#include <QWidget>
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>
#include <QTimer>

class bomba : public QWidget
{
    Q_OBJECT

private:
    QGraphicsPixmapItem* Imagen;
    float VelocidadY;
    bool DireccionPositiva;
    QTimer* TiempoMover;

public:
    bomba(int x, int y, bool DPositiva);

    QGraphicsPixmapItem* GetImagen();

    ~bomba();

public slots:
    void Mover();
};

#endif // BOMBA_H