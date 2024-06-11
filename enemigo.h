#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QRandomGenerator>
#include "soldado.h"

class enemigo : public soldado
{
    Q_OBJECT

private:
    QTimer* TiempoMover;
    QTimer* TiempoEntreDisparos;
    short int DisparosRealizados;
    short int Velocidad;

public:
    enemigo(short int x, short int y1, short int y2);

    short int GetVelocidad();
    void SetVelocidad(short int v);

    ~enemigo();

public slots:
    void Mover();
    void Animar();
    void Disparar();

signals:
    void Disparando(short int, short int);

};

#endif // ENEMIGO_H