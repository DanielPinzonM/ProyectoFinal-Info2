#include "proyectil.h"

proyectil::proyectil(short int x, short int y, bool MP)
{
    Imagen = new QGraphicsPixmapItem(QPixmap("Recursos/Proyectil.png"));
    Imagen->setScale(1);
    Imagen->setPos(x, y);

    Imagen->setTransformOriginPoint(Imagen->boundingRect().width()/2, Imagen->boundingRect().height()/2);

    MovimientoPositivoX = MP;
    DesviacionY = 0;

    TiempoMover = new QTimer();
    connect(TiempoMover, SIGNAL(timeout()), this, SLOT(Mover()));
    TiempoMover->start(16);

    TiempoVuelo = new QTimer();
    TiempoVuelo->setSingleShot(true);
    connect(TiempoVuelo, SIGNAL(timeout()), this, SLOT(FinVuelo()));
    TiempoVuelo->start(1000);
}

QGraphicsPixmapItem* proyectil::GetImagen()
{
    return Imagen;
}

void proyectil::Rebotar()
{
    DesviacionY = QRandomGenerator::global()->bounded(-5,6);

    if(MovimientoPositivoX == true)
    {
        if(DesviacionY > 0)
        {
            Imagen->setRotation(180-(DesviacionY*5));
        }
        else
        {
            Imagen->setRotation(180-(DesviacionY*5));
        }
    }
    else
    {
        if(DesviacionY > 0)
        {
            Imagen->setRotation(360+(DesviacionY*5));
        }
        else
        {
            Imagen->setRotation(0+(DesviacionY*5));
        }
    }

    MovimientoPositivoX = !MovimientoPositivoX;
}

void proyectil::Mover()
{
    if(MovimientoPositivoX == true)
    {
        Imagen->setPos(Imagen->pos().x()+9, Imagen->pos().y()+DesviacionY);
    }
    else
    {
        Imagen->setPos(Imagen->pos().x()-9, Imagen->pos().y()+DesviacionY);
    }
}

void proyectil::FinVuelo()
{
    emit TerminarVuelo(this);
}

proyectil::~proyectil()
{
    TiempoMover->stop();
    TiempoMover->disconnect(TiempoMover, SIGNAL(timeout()), this, SLOT(Mover()));
    TiempoMover->deleteLater();

    TiempoVuelo->stop();
    TiempoVuelo->disconnect(TiempoVuelo, SIGNAL(timeout()), this, SLOT(FinVuelo()));
    TiempoVuelo->deleteLater();

    this->deleteLater();
}