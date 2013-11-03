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
#include "mainwindow.hpp"
#include <ui_mainwindow.h>

Listening::Listening(MainWindow *mainWindow)
{
    this->mainWindow = mainWindow;
    this->listenSocket = new Socket();

    cout << listenSocket->create("NULL", DEFAULT_PORT) << endl;
    cout << listenSocket->binding() << endl;

    //this->listenSocket = mainWindow->getSocket();



    this->udp = new NetworkUDP();
    this->rfc = new RFC1664();
}

void Listening::run() {
    while(!end)
    {

        while (1) {
            cout << "Main() -> Attente d'un nouveau message" << endl;
            memset(this->message, 0, sizeof this->message); //vide le message

            this->udp->receiveDatagrams(this->listenSocket->getSocket(), this->message, sizeof this->message, this->listenSocket->getSockaddr());

            cout << "Main() -> Message reçu : " << this->message << endl;
            cout << "Main() -> Type du message reçu : " << this->rfc->type(this->message) << endl;
            string testString(message);
            string champ1(rfc->fieldFromMesg(testString, 1, '§'));
            string champ2(rfc->fieldFromMesg(testString, 2, '§'));
            string champ3(rfc->fieldFromMesg(testString, 3, '§'));
            string champ4(rfc->fieldFromMesg(testString, 4, '§'));
            string champ5(rfc->fieldFromMesg(testString, 5, '§'));
            QString chaine(champ2.c_str());
            switch (rfc->type(message)) {
                case MSG_COM:
                    cout << "Debug :" << champ2 << " à envoyé un message" << endl;

                   // MainWindow->getUi()->textEdit->insertPlainText(champ3);
                  //  MainWindow->getUi()->textEdit->insertPlainText(champ3);
                  //  MainWindow->getUi()->textEdit->insertPlainText(champ3);
                  //  MainWindow->getUi()->textEdit->insertPlainText(champ3);


                    chaine += " - ";
                    chaine += champ4.c_str();
                    chaine += "\n";

                    mainWindow->getUi()->textEdit->insertPlainText(chaine);
                break;

                case MSG_BOOK_LIST_RESP:
                    cout << "Debug :j'ai reçu l'annuaire" << endl;
                    mainWindow->getUi()->listWidget->addItem(chaine);
                    break;


                default:

                    break;


            }

            cout << "Main() -> Message reçu : " << this->message << endl;
    }
}
}
