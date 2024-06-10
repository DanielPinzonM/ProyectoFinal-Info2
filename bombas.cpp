#include "bombas.h"

bombas::bombas()
{
    Imagen = new QGraphicsPixmapItem(QPixmap("C:\\Users\\NICOLAS\\Pictures\\mina.png"));
    Imagen->setScale(1); // Reducir la escala de la imagen
    Imagen->setPos(qreal(QRandomGenerator::global()->bounded(0, 1200)),-100);
    tiempomover= new QTimer();
    tiempomover->start(16);
    connect(tiempomover,SIGNAL(timeout()), this, SLOT(mover()));
}

int bombas::getdanio()
{
    return danio;
}

QGraphicsPixmapItem *bombas::GetImagen()
{
    return Imagen;
}

bombas::~bombas()
{

}

void bombas::mover()
{
    Imagen->setPos(Imagen->pos().x(),Imagen->pos().y()+1);
}
