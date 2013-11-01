/* 
 * File:   ServeurChat.cpp
 * Author: darkey
 *
 * Created on 29 octobre 2013, 13:27
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;

#include "ErrorCodes.hpp"
#include "Socket.hpp"
#include "NetworkUDP.hpp"
#include "RFC1664.hpp"



#define MAX_MSG 1024
#define DEFAULT_PORT "1337"

char message[4096];


int main(int argc, char** argv) {
    Socket listenSocket;
    NetworkUDP udp;
    RFC1664 rfc;

    cout << listenSocket.create("0.0.0.0", DEFAULT_PORT);
    cout << listenSocket.binding();

			while (1)
			{
                cout << "Main() -> Attente d'un nouveau message" << endl;
                memset(message, 0, sizeof message);//vide le message

                udp.receiveDatagrams(listenSocket.getSocket(), message, sizeof message, listenSocket.getSockaddr());
				
				cout << "Main() -> Message reçu : " << message << endl;
                cout << "Main() -> Type du message reçu : " << rfc.type(message) << endl;

				/* TRAITEMENT DU MESSAGE
				if (sendto(listenSocket, message, sizeof message,0,(SOCKADDR *) &clientAddress,clientAddressSize) == -1)
				{
					perror("send failed :");
					close(listenSocket);
					exit(0);
				}*/
				
				cout << "Main() -> Traitement du message" << endl;
				cout << "Main() -> Traitement du terminé" << endl;
			}

			return 1337;		
}

