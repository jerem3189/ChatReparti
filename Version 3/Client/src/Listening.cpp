/** \file Signalisation.cpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Listening.hpp"
#include "../../Server/src/Socket.hpp"
#include "../../Server/src/NetworkUDP.hpp"
#include "../../Server/src/RFC1664.hpp"
#include "../../Server/src/Book.hpp"
#include "mainwindow.hpp"
#include "../../Server/src/Signalisation.hpp"
#include <ui_mainwindow.h>

Listening::Listening(MainWindow *mainWindow, Socket *socket, Book *book)
{
    this->mainWindow = mainWindow;
    this->listenSocket = socket;
    this->book = book;

    this->udp = new NetworkUDP();
    this->rfc = new RFC1664();

    QString global_room_name(this->book->getRooms().at(0).getName().c_str());
    this->mainWindow->getUi()->QTabWidget_onglets->setTabText(0, global_room_name);
    this->keepalive = NULL;

    QObject::connect(this, SIGNAL(statusBarChanged(QString)),this->mainWindow->getUi()->statusBar, SLOT(showMessage(QString)));
}

void Listening::run() {
    while(!end)
    {

        while (1) {
            cout << "Listening() -> Attente d'un nouveau message" << endl;
            memset(this->message, 0, sizeof this->message); //vide le message

            SOCKADDR_IN addr_in;
            SOCKADDR_IN addr_client;

            this->udp->receiveDatagrams(listenSocket->getSocket(), this->message, sizeof this->message, (SOCKADDR*)&addr_in, this->listenSocket->getAddrinfo());

            cout << "Listening() -> Message reçu : " << this->message << endl;
            cout << "Listening() -> Type du message reçu : " << this->rfc->type(this->message) << endl;

            string testString(message);
            string champ1(rfc->fieldFromMesg(testString, 1, "§"));
            string champ2(rfc->fieldFromMesg(testString, 2, "§"));
            string champ3(rfc->fieldFromMesg(testString, 3, "§"));
            string champ4(rfc->fieldFromMesg(testString, 4, "§"));
            string champ5(rfc->fieldFromMesg(testString, 5, "§"));

            QString chaine1(champ1.c_str());
            QString chaine2(champ2.c_str());
            QString chaine3(champ3.c_str());
            QString chaine4(champ4.c_str());
            QString chaine5(champ5.c_str());

            QString msg_com = "";

            Client *client = NULL;

            switch (rfc->type(message)) {

            case MSG_NEIGHBOOR:
                cout << "ComClients() -> j'ai reçu un nouveau voisin" << endl;

                // Si je suis le premier client
                if (this->book->getClients().at(0).getName() == this->mainWindow->getUi()->label_pseudo->text().toStdString()) {
                    if(this->mainWindow->getRightNeighboor() == NULL) {
                        cout << "Je suis le premier client, je n'ai pas de voisin a droite, donc je me le rajoute" << endl;
                        this->mainWindow->setRightNeighboor(this->book->findClient(champ2));
                        cout << "VOISIN DE DROITE : " << this->mainWindow->getRightNeighboor()->getName().c_str() << endl;
                    }
                }
                else {
                    // Si je n'ai pas de voisin de gauche
                    if(this->mainWindow->getLeftNeighboor() == NULL) {
                        cout << "Je n'ai pas de voisin à gauche donc je me le rajoute" << endl;
                        this->mainWindow->setLeftNeighboor(this->book->findClient(champ2));
                        cout << "VOISIN DE GAUCHE : " << this->mainWindow->getLeftNeighboor()->getName().c_str() << endl;
                    }
                    else {
                        if(this->mainWindow->getRightNeighboor() == NULL) {
                            cout << "Je n'ai pas de voisin à droite donc je me le rajoute" << endl;
                            this->mainWindow->setRightNeighboor(this->book->findClient(champ2));
                            cout << "VOISIN DE DROITE : " << this->mainWindow->getRightNeighboor()->getName().c_str() << endl;
                        }
                    }
                }

                break;

            case MSG_COM:
                cout << "Listening() -> " << champ2 << " a envoyé un message" << endl;

                msg_com = chaine2;
                msg_com += " - ";
                msg_com += chaine4;
                msg_com += "\n";

                mainWindow->getUi()->textEdit->moveCursor(QTextCursor::End);
                mainWindow->getUi()->textEdit->insertPlainText(msg_com);

                break;

            case MSG_BOOK_LIST_RESP:
                cout << "Listening() -> j'ai reçu l'annuaire" << endl;

                memset(&addr_client, 0, sizeof(addr_client));

                addr_client.sin_family = AF_INET;
                addr_client.sin_addr.s_addr = inet_addr(chaine3.toStdString().c_str());
                addr_client.sin_port = htons(chaine4.toInt());

                client = NULL;
                client = this->book->findClient(champ2);

                if(client == NULL) { // Le client n'est pas dans l'annuaire
                    cout << "le client n'est pas dans l'annuaire" << endl;
                    this->book->addNewClient(chaine2.toStdString(), chaine3.toStdString(), chaine4.toStdString(), &addr_client);
                    mainWindow->getUi()->listWidget->addItem(chaine2);
                }
                else { // Le client est dans l'annuaire
                    cout << "le client est deja dans l'annuaire" << endl;

                    champ1 = rfc->fieldFromMesg(testString, 5+chaine5.toInt(), "§");

                    if(this->book->findRoom(champ1) == NULL)
                        this->book->addRoom(champ1);

                    this->book->addClientToRoom(client->getName(), champ1);
                }

                break;

            case MSG_ACK:
                if(champ2 == MSG_ACK_CONNEXION_FAILED)
                {
                    this->mainWindow->setConnected(false);
                }

                if(champ2 == MSG_ACK_CONNEXION_SUCCESS)
                {
                    this->mainWindow->setConnected(true);
                    this->mainWindow->getUi()->action_Cr_er_un_nouveau_salon->setEnabled(true);
                    this->mainWindow->getUi()->action_Joindre_un_salon->setEnabled(true);
                    this->mainWindow->getUi()->label_pseudo->setEnabled(true);
                    this->mainWindow->getUi()->lineEdit->setEnabled(true);
                    this->mainWindow->getUi()->pushButton->setEnabled(true);
                    this->mainWindow->getUi()->action_Connexion_au_serveur->setEnabled(false);

                    keepalive = new Signalisation(mainWindow->getUi()->label_pseudo->text().toStdString(), mainWindow->getSocket());
                    this->mainWindow->setSig(keepalive);

                    keepalive->start();
                }

                if(champ2 == MSG_ACK_REMOVE_CLIENT_FAILED)
                {

                }

                if(champ2 == MSG_ACK_REMOVE_CLIENT_SUCCESS)
                {
                    this->keepalive->stop();
                }

                if(champ2 == MSG_ACK_ADD_CLIENT_TO_ROOM_FAILED)
                {

                }

                if(champ2 == MSG_ACK_ADD_CLIENT_TO_ROOM_SUCCESS)
                {

                }

                if(champ2 == MSG_ACK_REMOVE_CLIENT_TO_ROOM_FAILED)
                {

                }

                if(champ2 == MSG_ACK_REMOVE_CLIENT_TO_ROOM_SUCCESS)
                {

                }

                if(champ2 == MSG_ACK_ROOM_CREATE_FAILED)
                {

                }

                if(champ2 == MSG_ACK_ROOM_CREATE_SUCCESS)
                {
                    this->book->addRoom(this->mainWindow->getUi()->QTabWidget_onglets->tabText(this->mainWindow->getUi()->QTabWidget_onglets->count()-1).toStdString());
                }

                if(champ2 == MSG_ACK_UNKNOWN_CLIENT)
                {
                    emit statusBarChanged(QString("Vous n'etes pas connecté"));
                }

                break;

            default:

                break;


            }
        }
    }
}
