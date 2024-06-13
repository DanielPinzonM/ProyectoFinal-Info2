#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "Nivel2.h"
#include "nivel1.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QGraphicsScene* Menu;
    Nivel1* nivel1;
    Nivel2* nivel2;
    bool Nivel1Activo;
    bool Nivel2Activo;
    ~MainWindow();

public slots:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *e);
    void IniciarNivel1();
    void IniciarNivel2();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H