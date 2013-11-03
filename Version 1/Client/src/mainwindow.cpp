#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "../../Server/src/Signalisation.hpp"
#include "../../Server/src/RFC1664.hpp"
#include "../../Server/src/NetworkUDP.hpp"
#include "../../Server/src/Socket.hpp"

#include <QInputDialog>


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

void MainWindow::on_action_Connexion_au_serveur_triggered()
{
    RFC1664 rfc;
    NetworkUDP udp;

    QString pseudo = QInputDialog::getText(this, "Connexion au serveur", "Veuillez saisir votre pseudo");
    if ((pseudo == "Veuillez saisir votre pseudo") || (pseudo == ""))
        return;

    ui->label_pseudo->setText(pseudo);

    string msgcon = rfc.createMsgCon(ui->label_pseudo->text().toStdString(), NetworkUDP::getIp_static());
    udp.sendDatagrams(this->socket->getSocket(),(char*)msgcon.c_str(), strlen(msgcon.c_str()),socket->getSockaddr());
}

void MainWindow::on_action_Lancer_le_KeepAlive_triggered()
{
    Signalisation *keepalive = new Signalisation(ui->label_pseudo->text().toStdString(), this->socket);
    keepalive->start();
}

void MainWindow::on_pushButton_clicked()
{
    cout << "Envoi du message au serveur !" << endl;
}

void MainWindow::on_action_Cr_er_un_nouveau_salon_triggered()
{
    RFC1664 rfc;
    NetworkUDP udp;

    QString roomName = QInputDialog::getText(this, "Création d'un salon", "Veuillez saisir le nom du salon");
    if ((roomName == "Veuillez saisir le nom du salon") || (roomName == ""))
        return;

    string msg = rfc.createMsgRoomCreate(ui->label_pseudo->text().toStdString(),roomName.toStdString());
    udp.sendDatagrams(this->socket->getSocket(),(char*)msg.c_str(), strlen(msg.c_str()),socket->getSockaddr());
}

void MainWindow::on_action_Joindre_un_salon_triggered()
{
    RFC1664 rfc;
    NetworkUDP udp;

    QString roomName = QInputDialog::getText(this, "Création d'un salon", "Veuillez saisir le nom du salon");
    if ((roomName == "Veuillez saisir le nom du salon") || (roomName == ""))
        return;

    string msg = rfc.createMsgRoomJoin(ui->label_pseudo->text().toStdString(), roomName.toStdString());
    udp.sendDatagrams(this->socket->getSocket(),(char*)msg.c_str(), strlen(msg.c_str()),socket->getSockaddr());
}
