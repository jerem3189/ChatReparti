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
}

void Listening::run() {
    while(!end)
    {

        while (1) {
            cout << "Main() -> Attente d'un nouveau message" << endl;
            memset(this->message, 0, sizeof this->message); //vide le message

            SOCKADDR_IN addr_in;

            this->udp->receiveDatagrams(listenSocket->getSocket(), this->message, sizeof this->message, (SOCKADDR*)&addr_in, this->listenSocket->getAddrinfo());

            cout << "Main() -> Message reçu : " << this->message << endl;
            cout << "Main() -> Type du message reçu : " << this->rfc->type(this->message) << endl;

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
            Signalisation *keepalive = new Signalisation(mainWindow->getUi()->label_pseudo->text().toStdString(), mainWindow->getSocket());

            switch (rfc->type(message)) {
                case MSG_COM:
                    cout << "Debug :" << champ2 << " a envoyé un message" << endl;

                    msg_com = chaine2;
                    msg_com += " - ";
                    msg_com += chaine4;
                    msg_com += "\n";

                    mainWindow->getUi()->textEdit->moveCursor(QTextCursor::End);
                    mainWindow->getUi()->textEdit->insertPlainText(msg_com);

                break;

                case MSG_BOOK_LIST_RESP:
                    cout << "Debug :j'ai reçu l'annuaire" << endl;

                    this->book->addNewClient(chaine2.toStdString(), &addr_in);
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

                        keepalive->start();
                    }

                    if(champ2 == MSG_ACK_REMOVE_CLIENT_FAILED)
                    {

                    }

                    if(champ2 == MSG_ACK_REMOVE_CLIENT_SUCCESS)
                    {

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
                        this->mainWindow->getUi()->statusBar->addPermanentWidget(new QLabel ("message permanent", this->mainWindow->getUi()->statusBar));
                        QWidget *widget = new QWidget();
                        widget->setObjectName(QStringLiteral("TAB_TOTO"));

                        QVBoxLayout *vertLayout = new QVBoxLayout(widget);
                        vertLayout->setSpacing(6);
                        vertLayout->setContentsMargins(11, 11, 11, 11);
                        vertLayout->setObjectName(QStringLiteral("verticalLayout_14"));

                        QTextEdit *textEdit = new QTextEdit(widget);
                        textEdit->setObjectName(QStringLiteral("textEdit2"));
                        textEdit->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

                        vertLayout->addWidget(textEdit);

                        widget->show();

                        this->mainWindow->getUi()->QTabWidget_onglets->addTab(widget, QString(champ3.c_str()));
                    }

                    if(champ2 == MSG_ACK_UNKNOWN_CLIENT)
                    {
                        this->mainWindow->getUi()->statusBar->addPermanentWidget (new QLabel ("message permanent", this->mainWindow->getUi()->statusBar,(QMainWindow)this->mainWindow));
                    }

                    break;

                default:

                    break;


            }
    }
}
}



