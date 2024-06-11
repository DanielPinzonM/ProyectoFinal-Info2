#include "soldado.h"

soldado::soldado()
{
    Vida = 100;
}

short int soldado::GetVida()
{
    return Vida;
}

QGraphicsPixmapItem* soldado::GetImagen()
{
    return Imagen;
}

short int soldado::GetPosicionX()
{
    return Imagen->pos().x();
}

short int soldado::GetPosicionY()
{
    return Imagen->pos().y();
}

void soldado::SetVida(short int vida)
{
    Vida = vida;
}

void soldado::SetPosicion(short int x, short int y)
{
    Imagen->setPos(x, y);
}