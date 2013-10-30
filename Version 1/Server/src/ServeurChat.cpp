/* 
 * File:   ServeurChat.cpp
 * Author: darkey
 *
 * Created on 29 octobre 2013, 13:27
 */

#include <cstdlib>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define DEFAULT_PORT "1337"
/*
 * Macro de messages de debug
 * S'active à la compilation avec 'gcc -D DEBUG'
 */
#ifdef DEBUG
#define _DEBUG(msg1, msg2) \
	if ((msg1) == "") \
	{ \
		fprintf(stderr, "%s\n", msg2); \
	} \
	else \
	{ \
		fprintf(stderr, "%s : %s\n", msg1, msg2); \
	}
#else
#define _DEBUG(msg1, msg2)
#endif

/* Nouveaux types */
typedef struct addrinfo ADDRINFO;
typedef struct sockaddr SOCKADDR;
typedef int SOCKET;

/* Constantes préprocesseur */
#define MAX_MSG 1024
#define ERR_BAD_ARGUMENTS -1
#define ERR_SOCKET -2
#define ERR_GETADDRINFO -2

using namespace std;

/*
 * 
 */

char message[1024], listenPort[6];//defini un message de 1023 caractères, et un numéro de port sur 5 caractères
ADDRINFO infos, *infos2;
SOCKET listenSocket;
int etat;


//variable de renvoi du message
SOCKADDR clientAddress;
socklen_t clientAddressSize = sizeof clientAddress;


int main(int argc, char** argv) {


			memset(&infos, 0, sizeof infos);
			infos.ai_family = AF_UNSPEC;      // IPv4&6
			infos.ai_socktype = SOCK_DGRAM;  // UDP
			//infos.ai_flags = AI_PASSIVE;

			if ((etat = getaddrinfo("0.0.0.0", DEFAULT_PORT, &infos, &infos2)) != 0)
			{
				fprintf(stderr, "getaddrinfo : %s\n", gai_strerror(etat));
				exit(0);
			}

			if ((listenSocket = socket(	infos2->ai_family,
			                            infos2->ai_socktype,
			                            infos2->ai_protocol)) == -1)
			{
				perror("socket invalid :");
				exit(ERR_GETADDRINFO);
			}


			if (bind(listenSocket, infos2->ai_addr, infos2->ai_addrlen) == -1)
			{
				close(listenSocket);
				perror("bind failed :");
				exit(0);
			}
			else
			{
				printf("écoute sur le port UDP : %s\n", DEFAULT_PORT);
			}

			// Libération de la mémoire
			freeaddrinfo(infos2);



			while (1)
			{

				memset(message, 0, sizeof message);//vide le message

				recvfrom(listenSocket, message ,sizeof message,0,&clientAddress,&clientAddressSize);
				_DEBUG("Message reçu",message);
				//printf("Message reçu : %s \n",message);

				if (sendto(listenSocket, message, sizeof message,0,(SOCKADDR *) &clientAddress,clientAddressSize) == -1)
				{
					perror("send failed :");
					close(listenSocket);
					exit(0);
				}
				_DEBUG("Message renvoyé",message);
				//printf("Message renvoyé : %s \n",message);

			}


			return 1337;
		
}

