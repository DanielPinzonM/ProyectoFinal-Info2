#include "barco_aliado.h"

Barco_aliado::Barco_aliado()
{
    int numerobarcoimg;
    numerobarcoimg = QRandomGenerator::global()->bounded(1,5);
    Imagen = new QGraphicsPixmapItem(QPixmap("Recursos/barcoaliado" +QString(char(numerobarcoimg+48))+ ".png"));
    Imagen->setScale(1); // Reducir la escala de la imagen
    Imagen->setPos(qreal(QRandomGenerator::global()->bounded(0, 1200)),-150);
    tiempomover= new QTimer();
    tiempomover->start(16);
    connect(tiempomover,SIGNAL(timeout()), this, SLOT(mover()));
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

Barco_aliado::~Barco_aliado()
{
    tiempomover->stop();
    tiempomover->disconnect(tiempomover,SIGNAL(timeout()), this, SLOT(mover()));
    tiempomover->deleteLater();

    delete Imagen;

    this->deleteLater();
}