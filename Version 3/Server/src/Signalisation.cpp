/** \file Signalisation.cpp
 * Fonctions d'envoi périodique de keep alive.
 * Description plus elaboree et detaillee du fichier.
 *
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Signalisation.hpp"
#include "NetworkUDP.hpp"
#include "RFC1664.hpp"
#include "Socket.hpp"
/**
 * Constructeur de signalisation à partir du nom du client et d'un socket
 * @param clientName nom du client envoyant le keepalive
 * @param *socket pointeur sur un socket
 */
Signalisation::Signalisation(string clientName, Socket *socket)
{
    this->socket = socket;
    this->clientName =clientName;
}

/**
 * Envoi du keep alive
 * @return 0
 */
int Signalisation::sendKeepAlive() {
    RFC1664 rfc;

    string keepalive = rfc.createMsgKeepAlive(this->clientName);

    cout << "Signalisation::sendKeepAlive() -> message a envoyer : " << keepalive << endl;

    NetworkUDP::sendDatagrams(this->socket->getSocket(), (char*)keepalive.c_str(), strlen(keepalive.c_str()), this->socket->getSockaddr(), this->socket->getAddrinfo());

    return 0;
}

/**
 * Lancement de la boucle d'envoi de keep alive espacé d'un temps égal à KEEP_ALIVE_TIMEOUT
 */
void Signalisation::run() {
    while(!end)
    {
        this->sendKeepAlive();
        sleep(KEEP_ALIVE_TIMEOUT);

    }
}

