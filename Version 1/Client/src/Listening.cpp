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

            cout << "Main() -> Message reçu : " << this->message << endl;
    }
}
}
