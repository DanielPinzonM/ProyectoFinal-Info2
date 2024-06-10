#include "Nivel2.h"
#include <QScrollArea>

Nivel2::Nivel2()
{
    Escena->setBackgroundBrush(QImage("Recursos/Fondo1.png"));
    Escena->setSceneRect(0,0,1,1);

    for(int i=350; i<7000; i+=400)
    {
        Barricadas.append(new QGraphicsPixmapItem(QPixmap("Recursos/Barricada.png")));
        Barricadas.last()->setScale(1);
        Barricadas.last()->setPos(i, QRandomGenerator::global()->bounded(510, 581));

        if(Barricadas.last()->pos().y() > 575)
        {
            Escena->addItem(Barricadas.last());
            Barricadas.append(new QGraphicsPixmapItem(QPixmap("Recursos/Barricada.png")));
            Barricadas.last()->setScale(1);
            Barricadas.last()->setPos(i+200, 515);
        }
        else if(Barricadas.last()->pos().y() < 515)
        {
            Escena->addItem(Barricadas.last());
            Barricadas.append(new QGraphicsPixmapItem(QPixmap("Recursos/Barricada.png")));
            Barricadas.last()->setScale(1);
            Barricadas.last()->setPos(i+200, 575);
        }

        Escena->addItem(Barricadas.last());
    }

    Jugador = new jugador();

    Escena->addItem(Jugador->GetImagen());
    Jugador->SetPosicion(450,528);

    ExtremoDerecho = 1100 - int(Jugador->GetImagen()->boundingRect().width());
    ExtremoIzquierdo = 100;

    EsperaAvion = new QTimer();
    connect(EsperaAvion, SIGNAL(timeout()), this, SLOT(GenerarAvion()));
    EsperaAvion->start(5000);

    Refresco = new QTimer();
    connect(Refresco, SIGNAL(timeout()), this, SLOT(Actualizar()));
    Refresco->start(16);
}

QGraphicsScene* Nivel2::getEscena()
{
    return Escena;
}


void Nivel2::AgregarTecla(QKeyEvent* event)
{
    if(event->key() == Qt::Key_D)
    {
        if(!event->isAutoRepeat())
        {
            Keys.insert(event->key());
        }
    }

    if(event->key() == Qt::Key_A)
    {
        if(!event->isAutoRepeat())
        {
            Keys.insert(event->key());
        }
    }

    if(event->key() == Qt::Key_W)
    {
        if(!event->isAutoRepeat())
        {
            Keys.insert(event->key());
        }
    }

    if(event->key() == Qt::Key_S)
    {
        if(!event->isAutoRepeat())
        {
            Keys.insert(event->key());
        }
    }
}

void Nivel2::RemoverTecla(QKeyEvent* event)
{
    if(event->key() == Qt::Key_D)
    {
        if(!event->isAutoRepeat())
        {
            Keys.remove(event->key());
        }
    }
    else if(event->key() == Qt::Key_A)
    {
        if(!event->isAutoRepeat())
        {
            Keys.remove(event->key());
        }
    }
    if(event->key() == Qt::Key_W)
    {
        if(!event->isAutoRepeat())
        {
            Keys.remove(event->key());
        }
    }
    else if(event->key() == Qt::Key_S)
    {
        if(!event->isAutoRepeat())
        {
            Keys.remove(event->key());
        }
    }
}

void Nivel2::Actualizar()
{
    if(!(Keys.empty()))
    {
        if(Keys.contains(Qt::Key_D))
        {
            Jugador->SetPosicion(Jugador->GetPosicionX()+3, Jugador->GetPosicionY());

            if(Jugador->GetMueveDerecha() == false)
            {
                Jugador->SeMueveDerecha();
            }
        }
        if(Keys.contains(Qt::Key_A))
        {
            Jugador->SetPosicion(Jugador->GetPosicionX()-3, Jugador->GetPosicionY());

            if(Jugador->GetMueveIzquierda() == false)
            {
                Jugador->SeMueveIzquierda();
            }
        }
        if(Keys.contains(Qt::Key_W))
        {
            if(Jugador->GetPosicionY() > Escena->sceneRect().y()+500)
            {
                Jugador->SetPosicion(Jugador->GetPosicionX()-1, Jugador->GetPosicionY()-1);

                if(Jugador->GetMueveIzquierda() == false && Jugador->GetMueveDerecha() == false)
                {
                    Jugador->SeMueveIzquierda();
                }
            }
        }
        if(Keys.contains(Qt::Key_S))
        {
            if(Jugador->GetPosicionY() < Escena->sceneRect().y()+575)
            {
                Jugador->SetPosicion(Jugador->GetPosicionX()+1, Jugador->GetPosicionY()+1);

                if(Jugador->GetMueveIzquierda() == false && Jugador->GetMueveDerecha() == false)
                {
                    Jugador->SeMueveDerecha();
                }
            }
        }
    }
    else
    {
        if(Jugador->GetMueveDerecha() != false || Jugador->GetMueveIzquierda() != false)
        {
            Jugador->NoMover();
        }
    }

    for(QGraphicsPixmapItem* Barricada : Barricadas)
    {
        if(Barricada->pos().x() < Jugador->GetPosicionX()+Jugador->GetImagen()->boundingRect().width() && Barricada->pos().x()+Barricada->boundingRect().width()+20 > Jugador->GetPosicionX())
        {
            if(Jugador->GetMueveDerecha() == true)
            {
                if(Jugador->GetPosicionX()+20 > Barricada->pos().x() && Jugador->GetPosicionX()+20 < Barricada->pos().x()+Barricada->boundingRect().width())
                {
                    if(Jugador->GetPosicionY()+Jugador->GetImagen()->boundingRect().height() <= Barricada->pos().y()+Barricada->boundingRect().height()+10 && Jugador->GetPosicionY()+Jugador->GetImagen()->boundingRect().height() >= Barricada->pos().y()+60)
                    {
                        colision = true;
                        Jugador->SetPosicion(Jugador->GetPosicionX()-3, Jugador->GetPosicionY());
                        Jugador->GetImagen()->setZValue(1);
                    }
                    else
                    {
                        colision = false;
                    }
                }
            }
            else if(Jugador->GetMueveIzquierda() == true)
            {
                if(Jugador->GetPosicionX()+20 > Barricada->pos().x() && Jugador->GetPosicionX()+20 < Barricada->pos().x()+Barricada->boundingRect().width())
                {
                    if(Jugador->GetPosicionY()+Jugador->GetImagen()->boundingRect().height() <= Barricada->pos().y()+Barricada->boundingRect().height()+10 && Jugador->GetPosicionY()+Jugador->GetImagen()->boundingRect().height() >= Barricada->pos().y()+60)
                    {
                        colision = true;
                        Jugador->SetPosicion(Jugador->GetPosicionX()+3, Jugador->GetPosicionY());
                        Jugador->GetImagen()->setZValue(-1);
                    }
                    else
                    {
                        colision = false;
                    }
                }
            }

            if(Barricada->pos().y() > Jugador->GetPosicionY() && colision == false)
            {
                if(Jugador->GetImagen()->zValue() != -1)
                {
                    Jugador->GetImagen()->setZValue(-1);
                }
            }
            else
            {
                if(Jugador->GetImagen()->zValue() != 1)
                {
                    Jugador->GetImagen()->setZValue(1);
                }
            }
        }
    }

    if(Jugador->GetPosicionX() > Escena->sceneRect().x()+1000 && Escena->sceneRect().x() < 5768)
    {
        Escena->setSceneRect(Escena->sceneRect().x()+3,0,1,1);
    }
    else if(Jugador->GetPosicionX() < Escena->sceneRect().x()+200 && Escena->sceneRect().x() > 100)
    {
        Escena->setSceneRect(Escena->sceneRect().x()-3,0,1,1);
    }
}

void Nivel2::GenerarAvion()
{
    Aviones.append(new avion(0, 1200));
    Escena->addItem(Aviones.last()->GetImagen());
}