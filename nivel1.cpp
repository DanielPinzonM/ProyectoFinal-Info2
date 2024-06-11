#include "nivel1.h"



Nivel1::Nivel1()
{

    Escena = new QGraphicsScene;
    Escena->setSceneRect(0,0,1,1);
    Fondo = new QGraphicsPixmapItem(QPixmap("C:\\Users\\NICOLAS\\Downloads\\ivan-bandura-wQ00u_Un8Og-unsplash.jpg"));
    Escena->addItem(Fondo);
    Fondo->setPos(0,-3342);
    barco = new Barco();
    Escena->addItem(barco->GetImagen());
    barco->GetImagen()->setPos(500,400);
    agregarlimites();
    Actualizar.start(16);
    connect(&Actualizar, &QTimer::timeout, this, &Nivel1::Actualizarjuego);
    tiempocreacionbarco.start(5000);
    connect(&tiempocreacionbarco, &QTimer::timeout, this, &Nivel1::crearbarco);
    tiempocreacionavion.start(5000);
    connect(&tiempocreacionavion, &QTimer::timeout, this, &Nivel1::crearavion);
    tiempocreacionbomba.start(5000);
    connect(&tiempocreacionbomba, &QTimer::timeout, this, &Nivel1::crearbomba);
    aumentarFrecuenciaCreacion();


}

QGraphicsScene* Nivel1::GetEscena() {
    return Escena;
}


void Nivel1::agregarlimites()
{
    QPen pen (Qt::transparent,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);

    Paredes.append(Escena->addRect(0,0,1200,10,pen)); // arriba
    Paredes.append(Escena->addRect(0,640,1200,10,pen)); // abajo
    Paredes.append(Escena->addRect(0,0,10,650,pen)); // izquierda
    Paredes.append(Escena->addRect(1190,0,10,650,pen)); // derecha
}



void Nivel1::EventoTeclado(QKeyEvent* event)
{
    QPointF pos = barco->GetImagen()->pos();
    QPointF prevpos = barco->GetImagen()->pos();

    qreal rotationStep = 5; // Ángulo de rotación por paso

    switch (event->key()) {
    case Qt::Key_D:
        // Movimiento hacia la derecha
        if (barco->GetImagen()->rotation() < 20)
        {
        pos.setX(pos.x() + 7);
        }
        else if(barco->GetImagen()->rotation() > 20)
        {
        pos.setX(pos.x() + 10);
        }
        // Rotar el barco hacia la derecha (en sentido horario) con el ángulo de rotación más lento
        barco->GetImagen()->setRotation(barco->GetImagen()->rotation() + rotationStep);
        break;
    case Qt::Key_A:
        if (barco->GetImagen()->rotation() > -20)
        {
        pos.setX(pos.x() - 7);
        }
        else if(barco->GetImagen()->rotation() < -20)
        {
        pos.setX(pos.x() - 10);
        }

        barco->GetImagen()->setRotation(barco->GetImagen()->rotation() - rotationStep);
        break;
    case Qt::Key_W:
        // Movimiento hacia arriba
        pos.setY(pos.y() - 10);
        break;
    case Qt::Key_S:
        // Movimiento hacia abajo
        pos.setY(pos.y() + 10);
        break;
    }

    barco->GetImagen()->setPos(pos); // Establecer nueva posición del barco
    // Limitar la rotación dentro del rango de -45 a 45 grados
    qreal currentRotation = barco->GetImagen()->rotation();
    if (currentRotation > 45) {
        barco->GetImagen()->setRotation(45);
    } else if (currentRotation < -45) {
        barco->GetImagen()->setRotation(-45);
    }
    for (int i = 0; i < Paredes.length(); i++) {
        if (barco->GetImagen()->collidesWithItem(Paredes.at(i))) {
        // Si hay colisión, se restaura la posición previa
        barco->GetImagen()->setPos(prevpos);
        break;
        }
    }

}



void Nivel1::crearbarco()
{
    barcosaliados.append(new Barco_aliado());
    Escena->addItem(barcosaliados.last()->GetImagen());
}

void Nivel1::crearbomba()
{
    bombasE.append(new bombas);
    Escena->addItem(bombasE.last()->GetImagen());
}

void Nivel1::crearavion()
{
    aviones.append(new Aviones_Enemigos);
    Escena->addItem(aviones.last()->GetImagen());
}

void Nivel1::eliminarElementosFueraDePantalla()
{
    // Eliminar barcos aliados fuera de la pantalla
    for (int i = 0; i < barcosaliados.length(); i++) {
        if (barcosaliados[i]->GetImagen()->pos().y() > 651) {
            Escena->removeItem(barcosaliados[i]->GetImagen());
            delete barcosaliados[i];
            barcosaliados.removeAt(i);
            i--; // Ajustar el índice después de eliminar un elemento
        }
    }

    // Eliminar aviones enemigos fuera de la pantalla
    for (int i = 0; i < aviones.length(); i++) {
        if (aviones[i]->GetImagen()->pos().y() > 651) {
            Escena->removeItem(aviones[i]->GetImagen());
            delete aviones[i];
            aviones.removeAt(i);
            i--; // Ajustar el índice después de eliminar un elemento
        }
    }

    // Eliminar bombas fuera de la pantalla
    for (int i = 0; i < bombasE.length(); i++) {
        if (bombasE[i]->GetImagen()->pos().y() > 651) {
            Escena->removeItem(bombasE[i]->GetImagen());
            delete bombasE[i];
            bombasE.removeAt(i);
            i--; // Ajustar el índice después de eliminar un elemento
        }
    }
}

void Nivel1::Mostrarvida()
{
    // Buscar si ya existe un texto de vida en la escena
    QGraphicsTextItem* vidaText = nullptr;
    QList<QGraphicsItem*> items = Escena->items();
    for (int i = 0; i < items.size(); i++) {
        QGraphicsTextItem* item = dynamic_cast<QGraphicsTextItem*>(items[i]);
        if (item != nullptr && item->data(0) == "vida") {
            vidaText = item;
            break;
        }
    }

    // Si no existe un texto de vida, crear uno nuevo
    if (!vidaText) {
        vidaText = new QGraphicsTextItem();
        Escena->addItem(vidaText);
    }

    // Configurar la fuente del marcador
    QFont fuente;
    fuente.setPointSize(15);
    fuente.setWeight(QFont::Bold);
    vidaText->setFont(fuente);

    // Configurar el texto y su posición
    vidaText->setPlainText("Vida: " + QString::number(barco->getVida()));
    vidaText->setPos(1000, 20); // Ajustar la posición según tus necesidades

    // Configurar el color del texto
    vidaText->setDefaultTextColor(Qt::black);

    // Marcar el texto de vida para identificarlo
    vidaText->setData(0, "vida");
}



void Nivel1::manejarColisiones()
{
    // Colisiones con barcos aliados
    for (int i = 0; i < barcosaliados.length(); i++) {
        if (barco->GetImagen()->collidesWithItem(barcosaliados[i]->GetImagen())) {
            // Restar daño del barco aliado a la vida del barco
            int danioBarcoAliado = barcosaliados[i]->getdanio();
            barco->setVida(barco->getVida() - danioBarcoAliado);

        }
    }

    // Colisiones con aviones enemigos
    for (int i = 0; i < aviones.length(); i++) {
        if (barco->GetImagen()->collidesWithItem(aviones[i]->GetImagen())) {
            // Restar daño del avión enemigo a la vida del barco
            int danioAvion = aviones[i]->Getdanio();
            barco->setVida(barco->getVida() - danioAvion);

        }
    }

    // Colisiones con bombas
    for (int i = 0; i < bombasE.length(); i++) {
        if (barco->GetImagen()->collidesWithItem(bombasE[i]->GetImagen())) {
            // Restar daño de la bomba a la vida del barco
            int danioBomba = bombasE[i]->getdanio();
            barco->setVida(barco->getVida() - danioBomba);

            // Eliminar la bomba de la escena
            Escena->removeItem(bombasE[i]->GetImagen());
            delete bombasE[i];
            bombasE.removeAt(i);

        }
    }
}


void Nivel1::aumentarFrecuenciaCreacion()

{
    int tiempoCrecimiento = 3000; // Intervalo de tiempo en milisegundos para reducir la frecuencia de creación
    tiempocreacionbarco.setInterval(tiempocreacionbarco.interval() - tiempoCrecimiento);
    tiempocreacionbomba.setInterval(tiempocreacionbomba.interval() - tiempoCrecimiento);
}


void Nivel1::Actualizarjuego()

{
    Fondo->setPos(Fondo->pos().x(),Fondo->pos().y()+1);
    Fondo->setZValue(-1);

    if (barco->getVida() <= 0 || Fondo->pos().y() == 0)
    {
        Actualizar.stop();
        tiempocreacionbarco.stop();
        tiempocreacionavion.stop();
        tiempocreacionbomba.stop();

        for (int i = 0; i < barcosaliados.length(); i++)
        {
            Escena->removeItem(barcosaliados[i]->GetImagen());
            delete barcosaliados[i];
            barcosaliados.removeAt(i);
        }


        for (int i = 0; i < aviones.length(); i++)
        {
            Escena->removeItem(aviones[i]->GetImagen());
            delete aviones[i];
            aviones.removeAt(i);
        }


        for (int i = 0; i < bombasE.length(); i++)
        {
            Escena->removeItem(bombasE[i]->GetImagen());
            delete bombasE[i];
            bombasE.removeAt(i);

        }


        Fondofinal = new QGraphicsPixmapItem(QPixmap("C:\\Users\\NICOLAS\\Downloads\\fin del juego.jpg"));
        Escena->addItem(Fondofinal);
        Fondofinal->setPos(0,0);
        Fondofinal->setZValue(1);

        if(barco->getVida() <= 0)
        {
            QMessageBox::information(nullptr, "Fin del Juego", "PERDISTE, SUERTE PARA LA PROXIMA");
        }
        else
        {
            QMessageBox::information(nullptr, "Fin del Juego", "GANASTE FELICITACIONES");
            emit juegoTerminado();
        }
    }

    eliminarElementosFueraDePantalla();
    manejarColisiones();
    Mostrarvida();


}










