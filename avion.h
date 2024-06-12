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
    int PosicionLanzamiento;
    QTimer* TiempoMover;
    bool BombaLanzada;
    bool DireccionPositiva;

public:
    avion(int ExtremoIzquierdo, int ExtremoDerecho);

    short int GetVida();
    QGraphicsPixmapItem* GetImagen();
    bool GetDireccionPositiva();

    void DesplazarLanzamiento(short int c);

    ~avion();

public slots:
    void Mover();

signals:
    void Lanzamiento(int, int, bool);
};

#endif // AVION_H