#include "jugador.h"

jugador::jugador()
{
    Imagen = new QGraphicsPixmapItem;
    Imagen->setPixmap(QPixmap("Recursos/Soldado.png"));
    Imagen->setScale(1);

    MueveDerecha = false;
    MueveIzquierda = false;

    TiempoAnimar = new QTimer();
    connect(TiempoAnimar, SIGNAL(timeout()), this, SLOT(Animar()));
    TiempoAnimar->start(80);
}

bool jugador::GetMueveDerecha()
{
    return MueveDerecha;
}

bool jugador::GetMueveIzquierda()
{
    return MueveIzquierda;
}

void jugador::SeMueveDerecha()
{
    if(!(TiempoAnimar->isActive()))
    {
        TiempoAnimar->start(80);
    }

    Imagen->setTransform(QTransform().scale(1, 1), false);

    MueveIzquierda = false;
    MueveDerecha = true;
}

void jugador::SeMueveIzquierda()
{
    if(!(TiempoAnimar->isActive()))
    {
        TiempoAnimar->start(80);
    }

    Imagen->setTransform(QTransform().translate(60, 0).scale(-1, 1), false);

    MueveDerecha = false;
    MueveIzquierda = true;
}

void jugador::NoMover()
{
    TiempoAnimar->stop();
    Imagen->setPixmap(QPixmap("Recursos/Soldado.png"));
    MueveDerecha = false;
    MueveIzquierda = false;
}

void jugador::Disparar()
{
    Imagen->setPixmap(QPixmap("Recursos/SoldadoDisparar.png"));
    Imagen->setTransform(QTransform().translate(-30, 0).scale(1, 1), false);
}

void jugador::Animar()
{
    if(MueveDerecha == true || MueveIzquierda == true)
    {
        if(Imagen->pixmap().toImage() == QPixmap("Recursos/Soldado.png").toImage() || Imagen->pixmap().toImage() == QPixmap("Recursos/SoldadoDisparar.png").toImage())
        {
            Imagen->setPixmap(QPixmap("Recursos/Soldado1.png"));
        }
        else if(Imagen->pixmap().toImage() == QPixmap("Recursos/Soldado1.png").toImage())
        {
            Imagen->setPixmap(QPixmap("Recursos/Soldado2.png"));
        }
        else if(Imagen->pixmap().toImage() == QPixmap("Recursos/Soldado2.png").toImage())
        {
            Imagen->setPixmap(QPixmap("Recursos/Soldado3.png"));
        }
        else if(Imagen->pixmap().toImage() == QPixmap("Recursos/Soldado3.png").toImage())
        {
            Imagen->setPixmap(QPixmap("Recursos/Soldado4.png"));
        }
        else if(Imagen->pixmap().toImage() == QPixmap("Recursos/Soldado4.png").toImage())
        {
            Imagen->setPixmap(QPixmap("Recursos/Soldado1.png"));
        }
    }
}