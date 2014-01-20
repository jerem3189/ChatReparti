/** \file Signalisation.cpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ComClients.hpp"
#include "../../Server/src/Socket.hpp"
#include "../../Server/src/NetworkUDP.hpp"
#include "../../Server/src/RFC1664.hpp"
#include "../../Server/src/Book.hpp"
#include "mainwindow.hpp"
#include "../../Server/src/Signalisation.hpp"
#include <ui_mainwindow.h>

ComClients::ComClients(MainWindow *mainWindow, Socket *socket, Book *book)
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

void ComClients::run() {
    while(!end)
    {

        while (1) {
            cout << "ComClients() -> Attente d'un nouveau message" << endl;
            memset(this->message, 0, sizeof this->message); //vide le message

            SOCKADDR_IN addr_in;
            SOCKADDR_IN addr_in2;

            this->udp->receiveDatagrams(listenSocket->getSocket(), this->message, sizeof this->message, (SOCKADDR*)&addr_in, this->listenSocket->getAddrinfo());

            cout << "ComClients() -> Message reçu : " << this->message << endl;
            cout << "ComClients() -> Type du message reçu : " << this->rfc->type(this->message) << endl;

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

            int compare = -1;

            switch (rfc->type(message)) {
            case MSG_COM:

                /* MESSAGERIE PRIVEE

                // Si le message est pour lui de facon spécifique
                if(this->mainWindow->getUi()->label_pseudo->text().toStdString() == champ3) {
                    cout << "ComClients() -> " << champ2 << " a envoyé un message" << endl;

                    msg_com = chaine2;
                    msg_com += " - ";
                    msg_com += chaine4;
                    msg_com += "\n";

                    QTextEdit *text;

                    if (this->mainWindow->getRoomLists().contains(chaine5)) {
                        text = this->mainWindow->getRoomLists().take(chaine5);
                        text->moveCursor(QTextCursor::End);
                        text->insertPlainText(msg_com);
                    }
                }
                else { // Le message n'est pas pour ce client
                    if (this->mainWindow->getLeftNeighboor() != NULL) {
                        if (this->mainWindow->getLeftNeighboor()->getName() != champ2)
                            NetworkUDP::sendDatagrams(this->mainWindow->getSocketClients()->getSocket(), message, strlen(message), (SOCKADDR*)this->mainWindow->getLeftNeighboor()->getSockAddr(), this->mainWindow->getSocketClients()->getAddrinfo());
                    }

                    if (this->mainWindow->getRightNeighboor() != NULL) {
                        if (this->mainWindow->getRightNeighboor()->getName() != champ2)
                            NetworkUDP::sendDatagrams(this->mainWindow->getSocketClients()->getSocket(), message, strlen(message), (SOCKADDR*)this->mainWindow->getRightNeighboor()->getSockAddr(), this->mainWindow->getSocketClients()->getAddrinfo());
                    }
                }

                 FIN MESSAGERIE PRIVEE */




                // Si le message est pour un salon dans lequel il est présent
                if(this->mainWindow->getRoomLists().contains(chaine5)) {
                    cout << "ComClients() -> " << champ2 << " a envoyé un message" << endl;

                    msg_com = chaine2;
                    msg_com += " - ";
                    msg_com += chaine4;
                    msg_com += "\n";

                    QTextEdit *text;

                    text = this->mainWindow->getRoomLists().take(chaine5);
                    text->moveCursor(QTextCursor::End);
                    text->insertPlainText(msg_com);




                    // COMPARAISON DES DEUX SOCKADDR

                    if (this->mainWindow->getLeftNeighboor() != NULL) {
                        if (NetworkUDP::compareSockaddr(addr_in, *(this->mainWindow->getLeftNeighboor()->getSockAddr()))) {
                            cout << "Le message provient du voisin de gauche" << endl;
                            compare=1;
                        }
                        else {
                            cout << "Le message provient du voisin de droite" << endl;
                            compare=2;
                        }
                    }
                    else{
                        if (this->mainWindow->getRightNeighboor() != NULL) {
                            if (NetworkUDP::compareSockaddr(addr_in, *(this->mainWindow->getRightNeighboor()->getSockAddr()))) {
                                cout << "Le message provient du voisin de droite" << endl;
                                compare=2;
                            }
                            else {
                                cout << "Le message provient du voisin de gauche" << endl;
                                compare=1;
                            }
                        }
                    }



                    if (this->mainWindow->getLeftNeighboor() != NULL) {
                        if (compare==2) // Si ca vient du voisin de droite
                            NetworkUDP::sendDatagrams(this->mainWindow->getSocketClients()->getSocket(), message, strlen(message), (SOCKADDR*)this->mainWindow->getLeftNeighboor()->getSockAddr(), this->mainWindow->getSocketClients()->getAddrinfo());
                    }

                    if (this->mainWindow->getRightNeighboor() != NULL) {
                        if (compare == 1) // Si ca vient du voisin de gauche
                            NetworkUDP::sendDatagrams(this->mainWindow->getSocketClients()->getSocket(), message, strlen(message), (SOCKADDR*)this->mainWindow->getRightNeighboor()->getSockAddr(), this->mainWindow->getSocketClients()->getAddrinfo());
                    }
                }
                else { // Le message est pour un salon dans lequel le client n'est pas


                    cout << "Le message reçu est pour un salon dans lequel je ne suis pas" << endl;




                    // COMPARAISON DES DEUX SOCKADDR

                    if (this->mainWindow->getLeftNeighboor() != NULL) {
                        if (NetworkUDP::compareSockaddr(addr_in, *(this->mainWindow->getLeftNeighboor()->getSockAddr()))) {
                            cout << "Le message provient du voisin de gauche" << endl;
                            compare=1;
                        }
                        else {
                            cout << "Le message provient du voisin de droite" << endl;
                            compare=2;
                        }
                    }
                    else{
                        if (this->mainWindow->getRightNeighboor() != NULL) {
                            if (NetworkUDP::compareSockaddr(addr_in, *(this->mainWindow->getRightNeighboor()->getSockAddr()))) {
                                cout << "Le message provient du voisin de droite" << endl;
                                compare=2;
                            }
                            else {
                                cout << "Le message provient du voisin de gauche" << endl;
                                compare=1;
                            }
                        }
                    }



                    if (this->mainWindow->getLeftNeighboor() != NULL) {
                        if (compare==2) // Si ca vient du voisin de droite
                            NetworkUDP::sendDatagrams(this->mainWindow->getSocketClients()->getSocket(), message, strlen(message), (SOCKADDR*)this->mainWindow->getLeftNeighboor()->getSockAddr(), this->mainWindow->getSocketClients()->getAddrinfo());
                    }

                    if (this->mainWindow->getRightNeighboor() != NULL) {
                        if (compare == 1) // Si ca vient du voisin de gauche
                            NetworkUDP::sendDatagrams(this->mainWindow->getSocketClients()->getSocket(), message, strlen(message), (SOCKADDR*)this->mainWindow->getRightNeighboor()->getSockAddr(), this->mainWindow->getSocketClients()->getAddrinfo());
                    }
                }

                break;

            case MSG_BOOK_LIST_RESP:
                cout << "ComClients() -> j'ai reçu l'annuaire" << endl;
                this->book->addNewClient(chaine2.toStdString(), chaine3.toStdString(), chaine4.toStdString(), &addr_in);
                mainWindow->getUi()->listWidget->addItem(chaine2);

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

                if(champ2 == MSG_ACK_UNKNOWN_CLIENT)
                {
                    //this->mainWindow->getUi()->statusBar->addPermanentWidget (new QLabel ("message permanent"));
                    emit statusBarChanged(QString("Vous n'etes pas connecté"));
                }

                break;

            default:

                break;


            }
        }
    }
}



