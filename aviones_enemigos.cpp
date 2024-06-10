#include "aviones_enemigos.h"

Aviones_Enemigos::Aviones_Enemigos()
{
    Imagen = new QGraphicsPixmapItem(QPixmap("C:\\Users\\NICOLAS\\Pictures\\avion.png"));
    Imagen->setScale(1); // Reducir la escala de la imagen
    Imagen->setPos(0,-100);
    tiempomover= new QTimer();
    tiempomover->start(16);
    connect(tiempomover,SIGNAL(timeout()), this, SLOT(mover()));
}


void Aviones_Enemigos::mover()
{

    Imagen->setPos(Imagen->pos().x() + 2 , Imagen->pos().y() + 2);
}



QGraphicsPixmapItem *Aviones_Enemigos::GetImagen()
{
    return Imagen;
}

int Aviones_Enemigos::Getdanio()
{
    return danio;
}


