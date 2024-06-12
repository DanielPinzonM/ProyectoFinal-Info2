#ifndef JUGADOR_H
#define JUGADOR_H

#include "soldado.h"

class jugador : public soldado
{
    Q_OBJECT

private:
    bool MueveDerecha;
    bool MueveIzquierda;

public:
    jugador();
    bool GetMueveDerecha();
    bool GetMueveIzquierda();

    void SeMueveDerecha();
    void SeMueveIzquierda();
    void NoMover();

    void Disparar();
    void Derrotado();

public slots:
    void Animar();
};

#endif // JUGADOR_H