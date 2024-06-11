#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QTimer>

class proyectil : public QWidget
{
    Q_OBJECT

private:
    QGraphicsPixmapItem* Imagen;
    QTimer* TiempoVuelo;
    QTimer* TiempoMover;
    short int danio;
    short int DesviacionY;
    bool MovimientoPositivoX;

public:
    proyectil(short int x, short int y, bool MP);

    QGraphicsPixmapItem* GetImagen();

    void Rebotar();

    ~proyectil();

public slots:
    void Mover();
    void FinVuelo();

signals:
    void TerminarVuelo(proyectil*);
};

#endif // PROYECTIL_H