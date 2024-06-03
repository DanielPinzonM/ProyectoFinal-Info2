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