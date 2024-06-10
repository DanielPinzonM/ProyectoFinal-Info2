#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nivel1.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    nivel = new Nivel1(); // Inicializa correctamente el puntero nivel
    ui->graphicsView->setScene(nivel->GetEscena());
    ui->graphicsView->scale(1,1);
    ui->graphicsView->show();
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    nivel->EventoTeclado(event);
}


