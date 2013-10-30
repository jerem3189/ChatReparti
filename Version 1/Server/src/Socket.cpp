/** \file Socket.cpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#include "Socket.hpp"
#include  "using namespace std;"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/*
 * Macro de messages de debug
 * S'active à la compilation avec 'gcc -D DEBUG'
 */
#ifdef DEBUG
#define _DEBUG(msg1, msg2) \
	if ((msg1) == "") \
	{ \
		cout << stderr << msg2; \
	} \
	else \
	{ \
		cout << stderr << msg1 << msg2; \
	}
#else
#define _DEBUG(msg1, msg2)
#endif


/* Constantes préprocesseur */
#define MAX_MSG 1024
#define ERR_BAD_ARGUMENTS -1
#define ERR_SOCKET -2
#define ERR_GETADDRINFO -2

typedef struct addrinfo ADDRINFO;
typedef struct sockaddr SOCKADDR;
typedef int SOCKET;

//char message[1024], listenPort[6];//defini un message de 1023 caractères, et un numéro de port sur 5 caractères
ADDRINFO infos, *infosCli;
SOCKET listenSocket;
int etat;

//variable de renvoi du message
SOCKADDR clientAddress;
socklen_t clientAddressSize = sizeof clientAddress;

int Socket::create(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Usage \"serveur [udp_listen_port]\"";
		exit(0);
	}
	else
	{
		if ((atoi(argv[1]) < 1) || (atoi(argv[1])>65535))
		{
			if(atoi(argv[1]) < 1) _DEBUG("","Port < 1");
			if(atoi(argv[1])>65535) _DEBUG("","Port > 65535");
			cout << "Erreur port" <<endl;
			exit(0);
		}
		else
		{

			memset(&infos, 0, sizeof infos);
			infos.ai_family = AF_UNSPEC;      // IPv4&6
			infos.ai_socktype = SOCK_DGRAM;  // UDP
			//infos.ai_flags = AI_PASSIVE;

			if ((etat = getaddrinfo("0.0.0.0", argv[1], &infos, &infosCli)) != 0)
			{
				cout << stderr << "getaddrinfo :" << gai_strerror(etat);
				exit(0);
			}

			if ((listenSocket = socket(	infosCli->ai_family,
			                            infosCli->ai_socktype,
			                            infosCli->ai_protocol)) == -1)
			{
				perror("socket invalid :");
				exit(ERR_GETADDRINFO);
			}


			if (bind(listenSocket, infosCli->ai_addr, infosCli->ai_addrlen) == -1)
			{
				close(listenSocket);
				perror("bind failed :");
				exit(0);
			}
			else
			{
				cout << "écoute sur le port UDP :" << argv[1];
			}

			// Libération de la mémoire
			freeaddrinfo(infosCli);
		}


void Socket::listen()
{
			while (1)
			{

				memset(cSocket.message, 0, sizeof cSocket.message)

				recvfrom(listenSocket, cSocket.message ,sizeof cSocket.message,0,&clientAddress,&clientAddressSize);
				_DEBUG("Message reçu",message);

				if (sendto(listenSocket, cSocket.message, sizeof cSocket.message,0,(SOCKADDR *) &clientAddress,clientAddressSize) == -1)
				{
					perror("send failed :");
					close(listenSocket);
					exit(0);
				}
				_DEBUG("Message renvoyé",cSocket.message);

			}


			return 1337;
		}
	}
	
}
