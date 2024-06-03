#ifndef NIVEL2_H
#define NIVEL2_H

#include <QGraphicsScene>
#include <QWidget>
#include <QList>
#include <QSet>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>

class Nivel2 : public QWidget
{
    Q_OBJECT
private:
    QGraphicsScene* Escena = new QGraphicsScene;
    QSet<int> Keys;
    QTimer* Refresco;

public:
    Nivel2();
    QGraphicsScene* getEscena();

    void AgregarTecla(QKeyEvent* event);
    void RemoverTecla(QKeyEvent* event);

public slots:
    void Actualizar();
};

#endif // NIVEL2_H
