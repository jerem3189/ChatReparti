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

Listening::Listening(MainWindow *mainWindow, Socket *socket)
{
    this->mainWindow = mainWindow;
    //this->listenSocket = new Socket();
    this->listenSocket = socket;

    mainWindow->getUi()->textEdit->insertPlainText("toto");

    this->udp = new NetworkUDP();
    this->rfc = new RFC1664();
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
    }
}
}
