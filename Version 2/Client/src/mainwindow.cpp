#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "../../Server/src/Book.hpp"
#include "../../Server/src/Signalisation.hpp"
#include "../../Server/src/RFC1664.hpp"
#include "../../Server/src/NetworkUDP.hpp"
#include "../../Server/src/Socket.hpp"

#include <QInputDialog>

MainWindow::MainWindow(QString listenPortClient, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    cout << "PORT DECOUTE " << listenPortClient.toStdString() << endl;
    this->listenPortClient = listenPortClient;

    ui->setupUi(this);
    this->socket = new Socket();
    this->socket->create("NULL", "1337");
    this->connected = false;

    this->socketClients = new Socket();
    this->socketClients->create("NULL", listenPortClient.toStdString());
    this->socketClients->binding();

    this->show();
    this->hide();
    this->on_action_Connexion_au_serveur_triggered();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->socket = new Socket();
    this->socket->create("NULL", "1337");
    this->connected = false;

    this->show();
    this->hide();
    this->on_action_Connexion_au_serveur_triggered();
}

Socket *MainWindow::getSocket()
{
    return this->socket;
}

bool MainWindow::getConnected()
{
    return this->connected;
}

void MainWindow::setConnected(bool connected)
{
    this->connected = connected;
}

void MainWindow::addMessageToStatusBar(QString msg)
{
    this->ui->statusBar->addPermanentWidget(new QLabel(msg));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Connexion_au_serveur_triggered()
{
    RFC1664 rfc;

    QString pseudo = QInputDialog::getText(this, "Connexion au serveur", "Veuillez saisir votre pseudo");
    if ((pseudo == "Veuillez saisir votre pseudo") || (pseudo == ""))
        return;

    ui->label_pseudo->setText(pseudo);

    string msgcon = rfc.createMsgCon(ui->label_pseudo->text().toStdString(), "127.0.0.1", this->listenPortClient.toStdString());
    NetworkUDP::sendDatagrams(this->socket->getSocket(),(char*)msgcon.c_str(), strlen(msgcon.c_str()),socket->getSockaddr(), this->socket->getAddrinfo());
}

void MainWindow::on_action_Lancer_le_KeepAlive_triggered()
{
    Signalisation *keepalive = new Signalisation(ui->label_pseudo->text().toStdString(), this->socket);
    keepalive->start();

}
void MainWindow::setBook(Book *botin){
    this->book=botin;
}

void MainWindow::on_pushButton_clicked()
{
    RFC1664 rfc;
    cout << "Envoi du message au serveur !" << endl;
    int i;
    QString msg = ui->lineEdit->text();
    string msgCom = rfc.createMsgCom(ui->label_pseudo->text().toStdString(), "", msg.toStdString(), ui->QTabWidget_onglets->tabText(ui->QTabWidget_onglets->currentIndex()).toStdString());

    for (i=0; i<book->getClients().size(); i++)
    {

        NetworkUDP::sendDatagrams(this->socketClients->getSocket(), (char*)msgCom.c_str(), strlen(msgCom.c_str()), (SOCKADDR*)book->getClients().at(i).getSockAddr(), this->socketClients->getAddrinfo());
        cout << "PORT D'ENVOI DU MSG : [" << book->getClients().at(i).getSockAddr()->sin_port << "]" << endl;
    }
    //NetworkUDP::sendDatagrams(this->socket->getSocket(),(char*)msgCom.c_str(), strlen(msgCom.c_str()),socket->getSockaddr(), this->socket->getAddrinfo());

    this->ui->lineEdit->clear();
}

void MainWindow::on_action_Cr_er_un_nouveau_salon_triggered()
{
    RFC1664 rfc;

    QString roomName = QInputDialog::getText(this, "Création d'un salon", "Veuillez saisir le nom du salon");
    if ((roomName == "Veuillez saisir le nom du salon") || (roomName == ""))
        return;

    string msg = rfc.createMsgRoomCreate(ui->label_pseudo->text().toStdString(),roomName.toStdString());
    NetworkUDP::sendDatagrams(this->socket->getSocket(),(char*)msg.c_str(), strlen(msg.c_str()),socket->getSockaddr(), this->socket->getAddrinfo());
}

void MainWindow::on_action_Joindre_un_salon_triggered()
{
    RFC1664 rfc;

    QString roomName = QInputDialog::getText(this, "Création d'un salon", "Veuillez saisir le nom du salon");
    if ((roomName == "Veuillez saisir le nom du salon") || (roomName == ""))
        return;

    string msg = rfc.createMsgRoomJoin(ui->label_pseudo->text().toStdString(), roomName.toStdString());
    NetworkUDP::sendDatagrams(this->socket->getSocket(),(char*)msg.c_str(), strlen(msg.c_str()),socket->getSockaddr(), this->socket->getAddrinfo());
}

void MainWindow::on_actionD_connexion_triggered()
{
    RFC1664 rfc;
    string msg =rfc.createMsgDeco(ui->label_pseudo->text().toStdString());
    NetworkUDP::sendDatagrams(this->socket->getSocket(),(char*)msg.c_str(),strlen(msg.c_str()),socket->getSockaddr(), this->socket->getAddrinfo());
}


Signalisation *MainWindow::getSig() const
{
    return sig;
}

void MainWindow::setSig(Signalisation *value)
{
    sig = value;
}

Socket *MainWindow::getSocketClients() const
{
    return socketClients;
}

void MainWindow::setSocketClients(Socket *value)
{
    socketClients = value;
}

void MainWindow::on_pushButton_2_clicked()
{
    SOCKADDR_IN sendhost;
    RFC1664 rfc;

    memset(&sendhost, 0, sizeof(sendhost));

    sendhost.sin_family = AF_INET;
    sendhost.sin_addr.s_addr = inet_addr("127.0.0.1");
    sendhost.sin_port = htons(1338);

    string msg = rfc.createMsgCom("jeremy", "arnaud", "SALUT LA COMPAGNIE", "global");
    NetworkUDP::sendDatagrams(this->socketClients->getSocket(),(char*)msg.c_str(),strlen(msg.c_str()),(SOCKADDR*)&sendhost, this->socketClients->getAddrinfo());
}
