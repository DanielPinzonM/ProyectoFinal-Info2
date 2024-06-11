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

    TiempoAvion = 3000;

    EsperaAvion = new QTimer();
    connect(EsperaAvion, SIGNAL(timeout()), this, SLOT(GenerarAvion()));
    EsperaAvion->start(TiempoAvion);

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

void Nivel2::EventoMouse(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(Jugador->GetMueveDerecha() == false && Jugador->GetMueveIzquierda() == false)
        {
            Jugador->Disparar();
            Proyectiles.append(new QGraphicsLineItem(Jugador->GetPosicionX()-10, Jugador->GetPosicionY()+30, Jugador->GetPosicionX()-1, Jugador->GetPosicionY()+30));
            Proyectiles.last()->setPen(QPen(Qt::yellow));
            Escena->addItem(Proyectiles.last());
        }
    }
}

void Nivel2::Actualizar()
{
    if(Jugador->GetVida() <= 0)
    {
        qDebug() << "Murio";
    }

    if(Jugador->GetPosicionX() > 7020)
    {
        qDebug() << "Gano";
    }

    if(!(Keys.empty()))
    {
        if(Keys.contains(Qt::Key_D))
        {
            Jugador->SetPosicion(Jugador->GetPosicionX()+2, Jugador->GetPosicionY());

            if(Jugador->GetMueveDerecha() == false)
            {
                Jugador->SeMueveDerecha();
            }
        }
        if(Keys.contains(Qt::Key_A))
        {
            Jugador->SetPosicion(Jugador->GetPosicionX()-2, Jugador->GetPosicionY());

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
                        Jugador->SetPosicion(Jugador->GetPosicionX()-2, Jugador->GetPosicionY());
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
                        Jugador->SetPosicion(Jugador->GetPosicionX()+2, Jugador->GetPosicionY());
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

    for(QGraphicsLineItem* Proyectil : Proyectiles)
    {
        Proyectil->setPos(Proyectil->pos().x()-9, Proyectil->pos().y());
    }

    for(avion* Avion : Aviones)
    {
        if(Avion->GetDireccionPositiva() == true)
        {
            if(Avion->GetImagen()->pos().x() > Escena->sceneRect().x()+1400)
            {
                Escena->removeItem(Avion->GetImagen());
                Aviones.removeOne(Avion);
                Avion->disconnect(Avion, SIGNAL(Lanzamiento(int,int,bool)), this, SLOT(LanzarBomba(int,int,bool)));
                Avion->~avion();

                if(TiempoAvion > 500)
                {
                    TiempoAvion -= 200;
                    EsperaAvion->start(TiempoAvion);
                }
            }
        }
        else
        {
            if(Avion->GetImagen()->pos().x() < Escena->sceneRect().x()-200)
            {
                Escena->removeItem(Avion->GetImagen());
                Aviones.removeOne(Avion);
                Avion->disconnect(Avion, SIGNAL(Lanzamiento(int,int,bool)), this, SLOT(LanzarBomba(int,int,bool)));
                Avion->~avion();

                if(TiempoAvion > 500)
                {
                    TiempoAvion -= 200;
                    EsperaAvion->start(TiempoAvion);
                }
            }
        }
    }

    for(bomba* Bomba : Bombas)
    {
        if(Bomba->GetImagen()->pos().y() > 580)
        {
            Explosiones.append(new explosion(Bomba->GetImagen()->pos().x(),Bomba->GetImagen()->pos().y()));
            Escena->addItem(Explosiones.last()->GetImagen());
            connect(Explosiones.last(), SIGNAL(Disipado(explosion*)), this, SLOT(DisiparExplosion(explosion*)));

            if(Jugador->GetPosicionX() > Explosiones.last()->GetImagen()->pos().x() && Jugador->GetPosicionX() < Explosiones.last()->GetImagen()->pos().x()+Explosiones.last()->GetImagen()->boundingRect().width())
            {
                qDebug() << "Danio recibido I";
                Jugador->SetVida(Jugador->GetVida()-40);
            }
            else if(Jugador->GetPosicionX()+Jugador->GetImagen()->boundingRect().width() > Explosiones.last()->GetImagen()->pos().x() && Jugador->GetPosicionX()+Jugador->GetImagen()->boundingRect().width() < Explosiones.last()->GetImagen()->pos().x()+Explosiones.last()->GetImagen()->boundingRect().width())
            {
                qDebug() << "Danio recibido D";
                Jugador->SetVida(Jugador->GetVida()-40);
            }

            Escena->removeItem(Bomba->GetImagen());
            Bombas.removeOne(Bomba);
            Bomba->~bomba();
        }
    }

    if(Jugador->GetPosicionX() > Escena->sceneRect().x()+1000 && Escena->sceneRect().x() < 5768)
    {
        Escena->setSceneRect(Escena->sceneRect().x()+2,0,1,1);

        for(avion* Avion : Aviones)
        {
            Avion->DesplazarLanzamiento(2);
        }
    }
    else if(Jugador->GetPosicionX() < Escena->sceneRect().x()+200 && Escena->sceneRect().x() > 100)
    {
        Escena->setSceneRect(Escena->sceneRect().x()-2,0,1,1);

        for(avion* Avion : Aviones)
        {
            Avion->DesplazarLanzamiento(-2);
        }
    }
}

void Nivel2::GenerarAvion()
{
    Aviones.append(new avion(Escena->sceneRect().x(), Escena->sceneRect().x()+1200));
    Escena->addItem(Aviones.last()->GetImagen());
    connect(Aviones.last(), SIGNAL(Lanzamiento(int,int,bool)), this, SLOT(LanzarBomba(int,int,bool)));
}

void Nivel2::LanzarBomba(int x, int y, bool MPositivo)
{
    Bombas.append(new bomba(x,y,MPositivo));
    Escena->addItem(Bombas.last()->GetImagen());
}

void Nivel2::DisiparExplosion(explosion* Explosion)
{
    Explosiones.removeOne(Explosion);
    Escena->removeItem(Explosion->GetImagen());
    Explosion->deleteLater();
}