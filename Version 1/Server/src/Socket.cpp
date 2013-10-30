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
		cout << stderr << "%s\n" << msg2; \
	} \
	else \
	{ \
		cout << stderr << "%s : %s\n" << msg1 << msg2; \
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
ADDRINFO infos, *infos2;
SOCKET listenSocket;
int etat;

//variable de renvoi du message
SOCKADDR clientAddress;
socklen_t clientAddressSize = sizeof clientAddress;

//Foction principale
int Socket(int argc, char *argv[])
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

			if ((etat = getaddrinfo("0.0.0.0", argv[1], &infos, &infos2)) != 0)
			{
				cout << stderr << "getaddrinfo :" << gai_strerror(etat);
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
				cout << "écoute sur le port UDP : %s\n" << argv[1];
			}

			// Libération de la mémoire
			freeaddrinfo(infos2);



			while (1)
			{

				memset(cSocket.message, 0, sizeof cSocket.message);//vide le message

				recvfrom(listenSocket, cSocket.message ,sizeof cSocket.message,0,&clientAddress,&clientAddressSize);
				_DEBUG("Message reçu",message);
				//printf("Message reçu : %s \n",message);

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

/*int Socket::listen() {

}

int Socket::connect(SOCKET *csock, SOCKET *sock)
 { 
	
}

int Socket::create(unsigned short = 0) {
	
	 SOCKADDR_IN sin; 
		 
		if ( (*sock = socket (AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		   {
			 return(m_create = false);
			  return 1; 
		   }
}
*/
