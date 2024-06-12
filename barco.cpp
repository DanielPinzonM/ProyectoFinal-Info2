#include "barco.h"

Barco::Barco() {
    Imagen = new QGraphicsPixmapItem(QPixmap("IMAGENES/barcojugable.png"));
    Imagen->setScale(1);

}

void Barco::setVida(int nuevaVida) {
    vida = nuevaVida;
}

int Barco::getVida() const {
    return vida;
}

QGraphicsPixmapItem *Barco::GetImagen() {
    return Imagen;
}

Barco::~Barco() {
    delete Imagen;
}
