#include "barco_aliado.h"

Barco_aliado::Barco_aliado()
{
    QString numerobarcoimg;
    numerobarcoimg = QRandomGenerator::global()->bounded(49,53);
    Imagen = new QGraphicsPixmapItem(QPixmap("IMAGENES/barcoaliado" + numerobarcoimg + ".png"));
    Imagen->setScale(1); // Reducir la escala de la imagen
    Imagen->setPos(qreal(QRandomGenerator::global()->bounded(0, 1200)),-150);
    tiempomover= new QTimer();
    tiempomover->start(16);
    connect(tiempomover,SIGNAL(timeout()), this, SLOT(mover()));
}

Barco_aliado::~Barco_aliado()
{
    delete Imagen;
}

int Barco_aliado::getdanio() const
{
    return danio;
}

QGraphicsPixmapItem *Barco_aliado::GetImagen()
{
    return Imagen;
}

void Barco_aliado::mover()
{

    Imagen->setPos(Imagen->pos().x(),Imagen->pos().y()+2);
}

