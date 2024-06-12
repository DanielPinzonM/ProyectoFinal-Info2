#include "enemigo.h"

enemigo::enemigo(short int x, short int y1, short int y2)
{
    Imagen = new QGraphicsPixmapItem;
    Imagen->setPixmap(QPixmap("Recursos/Enemigo1.png"));
    Imagen->setScale(1);

    Imagen->setPos(x, QRandomGenerator::global()->bounded(y1,y2));

    DisparosRealizados = 0;

    Velocidad = 4;

    TiempoAnimar = new QTimer();
    connect(TiempoAnimar, SIGNAL(timeout()), this, SLOT(Animar()));
    TiempoAnimar->start(200);

    TiempoMover = new QTimer();
    connect(TiempoMover, SIGNAL(timeout()), this, SLOT(Mover()));
    TiempoMover->start(16);

    TiempoEntreDisparos = new QTimer();
    connect(TiempoEntreDisparos, SIGNAL(timeout()), this, SLOT(Disparar()));
    TiempoEntreDisparos->start(1000);
}

short int enemigo::GetVelocidad()
{
    return Velocidad;
}

void enemigo::SetVelocidad(short int v)
{
    Velocidad = v;
}

void enemigo::Mover()
{
    Imagen->setPos(Imagen->pos().x()+Velocidad, Imagen->pos().y());
}

void enemigo::Animar()
{
    if(Imagen->pixmap().toImage() == QPixmap("Recursos/Enemigo1.png").toImage() || Imagen->pixmap().toImage() == QPixmap("Recursos/SoldadoDisparar.png").toImage())
    {
        Imagen->setPixmap(QPixmap("Recursos/Enemigo2.png"));
    }
    else if(Imagen->pixmap().toImage() == QPixmap("Recursos/Enemigo2.png").toImage())
    {
        Imagen->setPixmap(QPixmap("Recursos/Enemigo1.png"));
    }
}

void enemigo::Disparar()
{
    if(DisparosRealizados < 3)
    {
        TiempoEntreDisparos->stop();
        TiempoEntreDisparos->start(100);

        emit Disparando(Imagen->pos().x()+40, Imagen->pos().y()+40);

        DisparosRealizados++;
    }
    else
    {
        TiempoEntreDisparos->stop();
        TiempoEntreDisparos->start(3000);
        DisparosRealizados = 0;
    }
}

enemigo::~enemigo()
{
    TiempoAnimar->stop();
    TiempoAnimar->disconnect(TiempoAnimar, SIGNAL(timeout()), this, SLOT(Animar()));
    TiempoAnimar->deleteLater();

    TiempoMover->stop();
    TiempoMover->disconnect(TiempoMover, SIGNAL(timeout()), this, SLOT(Mover()));
    TiempoMover->deleteLater();

    TiempoEntreDisparos->stop();
    TiempoEntreDisparos->disconnect(TiempoEntreDisparos, SIGNAL(timeout()), this, SLOT(Disparar()));
    TiempoEntreDisparos->deleteLater();

    this->deleteLater();
}