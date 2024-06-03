#include "Nivel2.h"

Nivel2::Nivel2()
{
    Escena->setBackgroundBrush(QImage("Recursos/Fondo.png"));
    Escena->setSceneRect(0,0,1,1);

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
}

void Nivel2::Actualizar()
{
    if(!(Keys.empty()))
    {
        if(Keys.contains(Qt::Key_D))
        {
            Escena->setSceneRect(Escena->sceneRect().x()+4,0,1,1);
        }
        if(Keys.contains(Qt::Key_A))
        {
            Escena->setSceneRect(Escena->sceneRect().x()-4,0,1,1);
        }
    }
}