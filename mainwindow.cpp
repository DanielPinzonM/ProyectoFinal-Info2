#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    Menu = new QGraphicsScene();
    Menu->setBackgroundBrush(QImage("Recursos/FondoMenu.png"));
    Menu->setSceneRect(0,0,1,1);

    Nivel1Activo = false;
    Nivel2Activo = false;

    ui->graphicsView->setScene(Menu);

    /*nivel2 = new Nivel2();

    Nivel1Activo = false;
    Nivel2Activo = true;

    ui->graphicsView->setScene(nivel2->getEscena());

----------------------------------------------------------------------------

    nivel1 = new Nivel1();

    connect(nivel1, SIGNAL(juegoTerminado()), this, SLOT(IniciarNivel2()));

    Nivel1Activo = true;
    Nivel2Activo = false;

    ui->graphicsView->setScene(nivel1->GetEscena());*/

    ui->graphicsView->scale(1,1);
    ui->graphicsView->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(Nivel1Activo == false && Nivel2Activo == false)
    {
        if(event->position().x() > 975 && event->position().x() < 1065 && event->position().y() > 370  && event->position().y() < 460)
        {
            IniciarNivel1();
        }
    }
    else if(Nivel2Activo == true)
    {
        nivel2->EventoMouse(event);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(Nivel1Activo == true)
    {
        nivel1->EventoTeclado(event);
    }

    if(Nivel2Activo == true)
    {
        nivel2->AgregarTecla(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(Nivel2Activo == true)
    {
        nivel2->RemoverTecla(event);
    }
}

void MainWindow::IniciarNivel1()
{
    Menu->deleteLater();

    nivel1 = new Nivel1();
    connect(nivel1, SIGNAL(juegoTerminado()), this, SLOT(IniciarNivel2()));
    Nivel1Activo = true;

    ui->graphicsView->setScene(nivel1->GetEscena());
}

void MainWindow::IniciarNivel2()
{
    disconnect(nivel1, SIGNAL(juegoTerminado()), this, SLOT(IniciarNivel2()));
    nivel1->deleteLater();
    Nivel1Activo = false;

    nivel2 = new Nivel2();
    Nivel2Activo = true;

    ui->graphicsView->setScene(nivel2->getEscena());
}

MainWindow::~MainWindow()
{
    delete ui;
}
