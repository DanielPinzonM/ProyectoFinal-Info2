#ifndef AVION_H
#define AVION_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QTimer>

class avion : public QWidget
{
    Q_OBJECT

private:
    short int Vida;
    QGraphicsPixmapItem* Imagen;
    QTimer* TiempoMover;
    int PosicionLanzamiento;
    bool BombaLanzada;
    bool DireccionPositiva;

public:
    avion(int ExtremoDerecho, int ExtremoIzquierdo);

    short int GetVida();
    QGraphicsPixmapItem* GetImagen();

public slots:
    void Mover();

signals:
    void Lanzamiento();
};

#endif // AVION_H