#include "explosion.h"

explosion::explosion(short int x, short int y)
{
    Imagen = new QGraphicsPixmapItem(QPixmap("Recursos/Explosion.png"));
    Imagen->setScale(1);
    Imagen->setPos(x-40, y-80);

    Duracion = new QTimer();
    Duracion->setSingleShot(true);
    connect(Duracion, SIGNAL(timeout()), this, SLOT(Apagar()));
    Duracion->start(300);
}

QGraphicsPixmapItem* explosion::GetImagen()
{
    return Imagen;
}

void explosion::Apagar()
{
    emit Disipado(this);
}