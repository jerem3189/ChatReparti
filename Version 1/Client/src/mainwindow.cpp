#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "../../Server/src/Signalisation.hpp"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_keep_alive_clicked()
{
    Signalisation *keepalive = new Signalisation();
    keepalive->start();
}
