#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QTimer>

class explosion : public QWidget
{
    Q_OBJECT

private:
    QGraphicsPixmapItem* Imagen;
    QTimer* Duracion;

public:
    explosion(short int x, short int y);

    QGraphicsPixmapItem* GetImagen();

public slots:
    void Apagar();

signals:
    void Disipado(explosion*);
};

#endif // EXPLOSION_H