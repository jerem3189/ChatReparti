#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

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


/* Constantes préprocesseur */
#define MAX_MSG 1024
#define ERR_BAD_ARGUMENTS -1
#define ERR_SOCKET -2
#define ERR_GETADDRINFO -2

/* Nouveaux types */
typedef struct addrinfo ADDRINFO;
typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;
typedef int SOCKET;

char message[1024], listenPort[6];//defini un message de 1023 caractères, et un numéro de port sur 5 caractères
ADDRINFO infos, *infos2;
SOCKET listenSocket;
int etat;

//variable de renvoi du message
SOCKADDR clientAddress;
socklen_t clientAddressSize = sizeof clientAddress;

//Foction principale
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		puts("Usage \"serveur [tcp_listen_port]\"\n");
		exit(0);
	}
	else
	{
		if ((atoi(argv[1]) < 1) || (atoi(argv[1])>65535))
		{
			if(atoi(argv[1]) < 1)
			{
				_DEBUG("","Port < 1");
			}

			if(atoi(argv[1])>65535)
			{
				_DEBUG("","Port > 65535");
			}
			puts("Merci de saisir un port compris entre 1 et 65535");
			exit(0);
		}
		else
		{
			/* Structures permettant la configuration du serveur */
			SOCKADDR_IN server_info;
			SOCKET server_sock;

			/* Structures permettant la configuration du client */
			SOCKADDR_IN client_info;
			SOCKET client_sock;

			int retour;


			/* Création de la socket serveur */
			_DEBUG("socket()", "Création de la socket serveur");
			server_sock = socket(AF_INET, SOCK_STREAM, 0);

			/* Si la socket est valide */
			if(server_sock != -1)
			{
				_DEBUG("socket()", "OK");
				printf("La socket %d est maintenant ouverte en mode TCP/IP\n", server_sock);

				/* Configuration */
				_DEBUG("debug", "Configuration des informations du serveur");
				server_info.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
				server_info.sin_family = AF_INET;                 /* Protocole familial (IP) */
				server_info.sin_port = htons(atoi(argv[1]));               /* Listage du port */

				_DEBUG("bind()", "bind des infos du serveur");
				retour = bind(server_sock, (SOCKADDR*)&server_info, sizeof(server_info));

				/* Si la socket fonctionne */
				if(retour != -1)
				{
					while(1) {
						_DEBUG("bind()", "OK");
						/* Démarrage du listage (mode server) */
						retour = listen(server_sock, 5);
						printf("Listage du port %d...\n", atoi(argv[1]));

						/* Si la socket fonctionne */
						if(retour != -1)
						{
							_DEBUG("listen()", "OK");
							/* Attente pendant laquelle le client se connecte */
							printf("Patientez pendant que le client se connecte sur le port %d...\n", atoi(argv[1]));
							socklen_t taille_adresse_client = sizeof(client_info);
							client_sock = accept(server_sock, (SOCKADDR*)&client_info, & taille_adresse_client);
							printf("Un client se connecte de %s:%d\n", inet_ntoa(client_info.sin_addr), htons(client_info.sin_port));
						}
						else
						{
							perror("listen");
							_DEBUG("listen()", "erreur lors du listen()");
						}


						memset(message, 0, sizeof message);
						_DEBUG("recv()", "réception du message du client...");
						retour = recv(client_sock, message, 1024, 0);
						_DEBUG("recv(), message reçu", message);

						_DEBUG("send()", "Envoi du message au client");
						if(send(client_sock, message, strlen(message), 0) < 0)
						{
							perror("send()");
							_DEBUG("send()", "Erreur lors de l'envoi du message au client");
							exit(-2);
						}
						_DEBUG("send()", "Message bien envoyé au client");

					}
				}
				else
				{
					perror("bind");
					_DEBUG("bind()", "erreur lors du bind");
				}

				/* Fermeture de la socket client et de la socket serveur */
				printf("Fermeture de la socket client\n");
				close(client_sock);
				printf("Fermeture de la socket serveur\n");
				close(server_sock);
				printf("Fermeture du serveur terminée\n");
			}
			else
				perror("socket");


			return 1337;

		}
	}
}
