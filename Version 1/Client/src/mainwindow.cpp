#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "../../Server/src/Signalisation.hpp"
#include "../../Server/src/RFC1664.hpp"
#include "../../Server/src/NetworkUDP.hpp"
#include "../../Server/src/Socket.hpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->socket = new Socket();
    this->socket->create("127.0.0.1", "1337");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_keep_alive_clicked()
{
    Signalisation *keepalive = new Signalisation("jérémy", this->socket);
    keepalive->start();
}

void MainWindow::on_button_connect_clicked()
{
    RFC1664 rfc;
    NetworkUDP udp;

    string msgcon = rfc.createMsgCon("Jeroumy", "127.0.0.1");
    udp.sendDatagrams(this->socket->getSocket(),(char*)msgcon.c_str(), strlen(msgcon.c_str()),socket->getSockaddr());
}
