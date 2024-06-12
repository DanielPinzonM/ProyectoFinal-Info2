#include "Nivel2.h"
#include <QScrollArea>

Nivel2::Nivel2()
{
    Escena->setBackgroundBrush(QImage("Recursos/Fondo.png"));

    Jugador = new jugador();
    Escena->addItem(Jugador->GetImagen());

    MarcadorVida = new QGraphicsTextItem;
    EsperaAvion = new QTimer();
    EsperaEnemigos = new QTimer();
    Refresco = new QTimer();

    Aviso = nullptr;

    Iniciar();
}

QGraphicsScene* Nivel2::getEscena()
{
    return Escena;
}

void Nivel2::CrearMarcador()
{
    QFont Fuente;
    Fuente.setPointSize(30);
    Fuente.setWeight(QFont::Bold);

    MarcadorVida->setPos(10,10);
    MarcadorVida->setPlainText(QString::number(Jugador->GetVida()));
    MarcadorVida->setFont(Fuente);
    MarcadorVida->setDefaultTextColor(Qt::white);
    Escena->addItem(MarcadorVida);
}

void Nivel2::Iniciar()
{
    if(Aviso != nullptr)
    {
        Escena->removeItem(Aviso);
        delete Aviso;
    }

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

    Jugador->SetPosicion(450,528);
    Jugador->SetVida(100);
    Jugador->NoMover();

    ExtremoDerecho = 1100 - int(Jugador->GetImagen()->boundingRect().width());
    ExtremoIzquierdo = 100;

    CrearMarcador();

    TiempoAvion = 3000;

    connect(EsperaAvion, SIGNAL(timeout()), this, SLOT(GenerarAvion()));
    EsperaAvion->start(TiempoAvion);

    connect(EsperaEnemigos, SIGNAL(timeout()), this, SLOT(GenerarEnemigos()));
    EsperaEnemigos->start(5000);

    connect(Refresco, SIGNAL(timeout()), this, SLOT(Actualizar()));
    Refresco->start(16);

    Derrotado = false;
    Victorioso = false;
}

void Nivel2::AgregarTecla(QKeyEvent* event)
{
    if(Derrotado == false)
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
}

void Nivel2::RemoverTecla(QKeyEvent* event)
{
    if(Derrotado == false)
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
}

void Nivel2::EventoMouse(QMouseEvent *event)
{
    if(Derrotado == false)
    {
        if(event->button() == Qt::LeftButton)
        {
            if(Jugador->GetMueveDerecha() == false && Jugador->GetMueveIzquierda() == false)
            {
                Jugador->Disparar();

                Proyectiles.append(new proyectil(Jugador->GetPosicionX()-20, Jugador->GetPosicionY()+20, false));
                connect(Proyectiles.last(), SIGNAL(TerminarVuelo(proyectil*)), this, SLOT(EliminarProyectil(proyectil*)));
                Escena->addItem(Proyectiles.last()->GetImagen());
            }
        }
    }
    else
    {
        if(event->position().x() > 600 && event->position().x() < 660 && event->position().y() > 450  && event->position().y() < 530)
        {
            Iniciar();
        }
    }
}

void Nivel2::LimpiarEscena()
{
    Refresco->stop();
    Refresco->disconnect(Refresco, SIGNAL(timeout()), this, SLOT(Actualizar()));

    EsperaAvion->stop();
    EsperaAvion->disconnect(EsperaAvion, SIGNAL(timeout()), this, SLOT(GenerarAvion()));

    EsperaEnemigos->stop();
    EsperaEnemigos->disconnect(EsperaEnemigos, SIGNAL(timeout()), this, SLOT(Derrota()));

    for(QGraphicsPixmapItem* Barricada : Barricadas)
    {
        Escena->removeItem(Barricada);
        Barricadas.removeOne(Barricada);
        delete Barricada;
    }

    for(avion* Avion : Aviones)
    {
        Escena->removeItem(Avion->GetImagen());
        Aviones.removeOne(Avion);
        Avion->deleteLater();
    }

    for(bomba* Bomba : Bombas)
    {
        Escena->removeItem(Bomba->GetImagen());
        Bombas.removeOne(Bomba);
        Bomba->deleteLater();
    }

    for(proyectil* Proyectil : Proyectiles)
    {
        Escena->removeItem(Proyectil->GetImagen());
        Proyectiles.removeOne(Proyectil);
        Proyectil->deleteLater();
    }

    for(proyectil* Proyectil : ProyectilesEnemigos)
    {
        Escena->removeItem(Proyectil->GetImagen());
        ProyectilesEnemigos.removeOne(Proyectil);
        Proyectil->deleteLater();
    }

    for(enemigo* Enemigo : Enemigos)
    {
        Escena->removeItem(Enemigo->GetImagen());
        Enemigos.removeOne(Enemigo);
        Enemigo->deleteLater();
    }

    Escena->removeItem(MarcadorVida);
}

void Nivel2::Actualizar()
{
    if(Jugador->GetVida() <= 0)
    {
        qDebug() << Jugador->GetVida();

        if(Derrotado == false)
        {
            Jugador->NoMover();
            Jugador->Derrotado();

            EsperaEnemigos->stop();
            EsperaEnemigos->setSingleShot(true);
            EsperaEnemigos->disconnect(EsperaEnemigos, SIGNAL(timeout()), this, SLOT(GenerarEnemigos()));
            connect(EsperaEnemigos, SIGNAL(timeout()), this, SLOT(Derrota()));
            EsperaEnemigos->start(2000);

            Derrotado = true;
        }
    }

    if(Jugador->GetPosicionX() > 7020)
    {
        if(Victorioso == false)
        {
            EsperaEnemigos->stop();
            EsperaEnemigos->setSingleShot(true);
            EsperaEnemigos->disconnect(EsperaEnemigos, SIGNAL(timeout()), this, SLOT(GenerarEnemigos()));
            connect(EsperaEnemigos, SIGNAL(timeout()), this, SLOT(Victoria()));
            EsperaEnemigos->start(2000);

            Victorioso = true;
        }
    }

    if(MarcadorVida->toPlainText() != QString::number(Jugador->GetVida()))
    {
        MarcadorVida->setPlainText(QString::number(Jugador->GetVida()));
    }

    for(enemigo* Enemigo : Enemigos)
    {
        if(Enemigo->GetVida() <= 0)
        {
            Escena->removeItem(Enemigo->GetImagen());
            Enemigos.removeOne(Enemigo);
            Enemigo->deleteLater();
        }
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
                    if(Jugador->GetPosicionY()+Jugador->GetImagen()->boundingRect().height() <= Barricada->pos().y()+Barricada->boundingRect().height()+10 && Jugador->GetPosicionY()+Jugador->GetImagen()->boundingRect().height() >= Barricada->pos().y()+55)
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
                    if(Jugador->GetPosicionY()+Jugador->GetImagen()->boundingRect().height() <= Barricada->pos().y()+Barricada->boundingRect().height()+10 && Jugador->GetPosicionY()+Jugador->GetImagen()->boundingRect().height() >= Barricada->pos().y()+55)
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

        for(proyectil* Proyectil : Proyectiles)
        {
            if(Proyectil->GetImagen()->pos().x() > Barricada->pos().x()+10 && Proyectil->GetImagen()->pos().x() < Barricada->pos().x()+Barricada->boundingRect().width()-10)
            {
                if(Proyectil->GetImagen()->pos().y() > Barricada->pos().y()+5 && Proyectil->GetImagen()->pos().y() < Barricada->pos().y()+Barricada->boundingRect().height()-40)
                {
                    Proyectil->Rebotar();
                }
            }
        }

        for(proyectil* ProyectilEnemigo : ProyectilesEnemigos)
        {
            if(ProyectilEnemigo->GetImagen()->pos().x() > Barricada->pos().x()+10 && ProyectilEnemigo->GetImagen()->pos().x() < Barricada->pos().x()+Barricada->boundingRect().width()-10)
            {
                if(ProyectilEnemigo->GetImagen()->pos().y() > Barricada->pos().y()+5 && ProyectilEnemigo->GetImagen()->pos().y() < Barricada->pos().y()+Barricada->boundingRect().height()-5)
                {
                    ProyectilEnemigo->Rebotar();
                }
            }
        }
    }


    for(enemigo* Enemigo : Enemigos)
    {
        if(Enemigo->GetImagen()->pos().x() < Jugador->GetImagen()->pos().x()-500)
        {
            if(Enemigo->GetVelocidad() != 4)
            {
                Enemigo->SetVelocidad(4);
            }
        }
        else if(Enemigo->GetImagen()->pos().x() >= Jugador->GetImagen()->pos().x()-500 && Enemigo->GetImagen()->pos().x() <= Jugador->GetImagen()->pos().x()-200)
        {
            if(Enemigo->GetVelocidad() != 2)
            {
                Enemigo->SetVelocidad(2);
            }
        }
        else if(Enemigo->GetImagen()->pos().x() > Jugador->GetImagen()->pos().x()-200)
        {
            if(Enemigo->GetVelocidad() != 0)
            {
                Enemigo->SetVelocidad(0);
            }
        }
    }

    for(proyectil* Proyectil : Proyectiles)
    {
        for(enemigo* Enemigo : Enemigos)
        {
            if(Proyectil->GetImagen()->pos().x() > Enemigo->GetImagen()->pos().x() && Proyectil->GetImagen()->pos().x() < Enemigo->GetImagen()->pos().x()+60)
            {
                if(Proyectil->GetImagen()->pos().y() > Enemigo->GetImagen()->pos().y() && Proyectil->GetImagen()->pos().y() < Enemigo->GetImagen()->pos().y()+Enemigo->GetImagen()->boundingRect().height()-10)
                {
                    Enemigo->SetVida(Enemigo->GetVida()-25);
                    Escena->removeItem(Proyectil->GetImagen());
                    Proyectiles.removeOne(Proyectil);
                    Proyectil->deleteLater();
                }
            }
        }
    }

    for(proyectil* ProyectilEnemigo : ProyectilesEnemigos)
    {
        if(ProyectilEnemigo->GetImagen()->pos().x() > Jugador->GetImagen()->pos().x() && ProyectilEnemigo->GetImagen()->pos().x() < Jugador->GetImagen()->pos().x()+Jugador->GetImagen()->boundingRect().width())
        {
            if(ProyectilEnemigo->GetImagen()->pos().y() > Jugador->GetImagen()->pos().y()+15 && ProyectilEnemigo->GetImagen()->pos().y() < Jugador->GetImagen()->pos().y()+Jugador->GetImagen()->boundingRect().width()-15)
            {
                Jugador->SetVida(Jugador->GetVida()-10);
                ProyectilesEnemigos.removeOne(ProyectilEnemigo);
                Escena->removeItem(ProyectilEnemigo->GetImagen());
                ProyectilEnemigo->deleteLater();
            }
        }
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
                    TiempoAvion -= 60;
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
                    TiempoAvion -= 60;
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
                Jugador->SetVida(Jugador->GetVida()-40);
            }
            else if(Jugador->GetPosicionX()+Jugador->GetImagen()->boundingRect().width() > Explosiones.last()->GetImagen()->pos().x() && Jugador->GetPosicionX()+Jugador->GetImagen()->boundingRect().width() < Explosiones.last()->GetImagen()->pos().x()+Explosiones.last()->GetImagen()->boundingRect().width())
            {
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
        MarcadorVida->setPos(MarcadorVida->pos().x()+2, MarcadorVida->pos().y());

        for(avion* Avion : Aviones)
        {
            Avion->DesplazarLanzamiento(2);
        }
    }
    else if(Jugador->GetPosicionX() < Escena->sceneRect().x()+200 && Escena->sceneRect().x() > 100)
    {
        Escena->setSceneRect(Escena->sceneRect().x()-2,0,1,1);
        MarcadorVida->setPos(MarcadorVida->pos().x()+2, MarcadorVida->pos().y());

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

void Nivel2::EliminarProyectil(proyectil* Proyectil)
{
    if(Proyectiles.contains(Proyectil))
    {
        Proyectiles.removeOne(Proyectil);
    }
    else
    {
        ProyectilesEnemigos.removeOne(Proyectil);
    }

    Escena->removeItem(Proyectil->GetImagen());
    Proyectil->deleteLater();
}

void Nivel2::GenerarEnemigos()
{
    for(short int i=0; i<1; i++)
    {
        Enemigos.append(new enemigo(Escena->sceneRect().x()-100, Escena->sceneRect().y()+500, Escena->sceneRect().y()+575));
        Escena->addItem(Enemigos.last()->GetImagen());
        connect(Enemigos.last(), SIGNAL(Disparando(short int, short int)), this, SLOT(ProyectilEnemigo(short int, short int)));
    }
}

void Nivel2::ProyectilEnemigo(short int x, short int y)
{
    ProyectilesEnemigos.append(new proyectil(x, y, true));
    connect(ProyectilesEnemigos.last(), SIGNAL(TerminarVuelo(proyectil*)), this, SLOT(EliminarProyectil(proyectil*)));
    Escena->addItem(ProyectilesEnemigos.last()->GetImagen());
}

void Nivel2::Victoria()
{
    LimpiarEscena();

    Aviso = new QGraphicsPixmapItem(QPixmap("Recursos/Victoria.png"));
    Aviso->setPos(Escena->sceneRect().x()+160, -130);

    Escena->addItem(Aviso);
}

void Nivel2::Derrota()
{
    LimpiarEscena();

    Aviso = new QGraphicsPixmapItem(QPixmap("Recursos/Derrota.png"));
    Aviso->setPos(Escena->sceneRect().x()+160, -130);

    Escena->addItem(Aviso);
}