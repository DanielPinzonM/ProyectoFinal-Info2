#include "bomba.h"

bomba::bomba(int x, int y, bool DPositiva)
{
    Imagen = new QGraphicsPixmapItem(QPixmap("Recursos/Bomba.png"));
    Imagen->setScale(1);
    Imagen->setPos(x,y);

    VelocidadY = 0;

    DireccionPositiva = DPositiva;

    TiempoMover = new QTimer();
    connect(TiempoMover, SIGNAL(timeout()), this, SLOT(Mover()));
    TiempoMover->start(16);
}

QGraphicsPixmapItem* bomba::GetImagen()
{
    return Imagen;
}

void bomba::Mover()
{
    if(DireccionPositiva == true)
    {
        Imagen->setPos(Imagen->pos().x()+3, Imagen->pos().y()+VelocidadY);
    }
    else
    {
        Imagen->setPos(Imagen->pos().x()-3, Imagen->pos().y()+VelocidadY);
    }

    VelocidadY += 0.08;
}

bomba::~bomba()
{
    TiempoMover->stop();
    TiempoMover->disconnect(TiempoMover, SIGNAL(timeout()), this, SLOT(Mover()));
    TiempoMover->deleteLater();
    this->deleteLater();
}