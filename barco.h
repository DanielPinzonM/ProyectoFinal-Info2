#ifndef BARCO_H
#define BARCO_H

#include <QObject>
#include <QGraphicsPixmapItem>


class Barco : public QObject {
    Q_OBJECT
private:
    int vida = 100;
    QGraphicsPixmapItem *Imagen;

public:
    Barco();
    void setVida(int nuevaVida);
    int getVida() const;
    QGraphicsPixmapItem* GetImagen();
    ~Barco();

public slots:
};

#endif // BARCO_H
