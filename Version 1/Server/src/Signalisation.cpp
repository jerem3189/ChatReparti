/** \file Signalisation.cpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Signalisation.hpp"
#include "NetworkUDP.hpp"
#include "RFC1664.hpp"
#include "Socket.hpp"

Signalisation::Signalisation()
{
    this->socket = new Socket();
    this->socket->create("127.0.0.1", "1337");
}

int Signalisation::sendKeepAlive() {
    RFC1664 rfc;
    NetworkUDP udp;

    string keepalive = rfc.createMsgKeepAlive("Jeremy");

    cout << "Signalisation::sendKeepAlive() -> message a envoyer : " << keepalive << endl;

    udp.sendDatagrams(this->socket->getSocket(), (char*)keepalive.c_str(), strlen(keepalive.c_str()),this->socket->getSockaddr());

    return 0;
}

void Signalisation::sleep(int nbr_seconds)
{
    clock_t goal;
    goal = (nbr_seconds * CLOCKS_PER_SEC) + clock();
    while(goal > clock())
    {
        ;
    }
}

void Signalisation::run() {
    while(!end)
    {
        //printf("Il vous reste %ld secondes.\n", i);
        this->sendKeepAlive();
        sleep(KEEP_ALIVE_TIMEOUT);
    }
}

