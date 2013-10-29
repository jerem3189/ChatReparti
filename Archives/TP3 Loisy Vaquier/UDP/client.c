#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

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
#define ERR_CONNECT -3
#define ERR_SEND -4

/* Nouveaux types */
typedef int SOCKET;
typedef struct addrinfo ADDRINFO;
typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;

/* Fonction principale */
int main(int argc, char *argv[])
{
	if((argc <= 1) || (argc > 3))
	{
		fprintf(stdout, "Usage \"client_echo [adresse_serveur] [num_port]\"\n");
		exit(ERR_BAD_ARGUMENTS);
	}

	/* Déclaration des structures décrivant les informations du serveur */
	ADDRINFO hints, *server_info;

	/* Mise à zéro de la structure hints */
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; /* IPV4 ou V6 */
	hints.ai_socktype = SOCK_DGRAM; /* Mode Datagramme */

	/* Récupération des informations du serveur */
	_DEBUG("getaddrinfo()", "Récupération des informations du serveur");
	int retour = 0;
	retour = getaddrinfo(argv[1], argv[2], &hints, &server_info);

	if(retour != 0)
	{
		_DEBUG("gai_strerror()", gai_strerror(retour));
		exit(ERR_GETADDRINFO);
	}
	else _DEBUG("getaddrinfo()", "Informations du serveur récupérées");

	/* Déclaration du descripteur de fichier de la socket */
	SOCKET sockfd;

	/* Création de la socket */
	_DEBUG("socket()", "Création de la socket");
	sockfd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if(sockfd == -1)
	{
		_DEBUG("socket()", "Erreur de création de la socket");
		exit(ERR_SOCKET);
	}
	else _DEBUG("socket()", "Socket créée");

	/* Invite de saisie du message à envoyer */
	fprintf(stdout, "Veuillez saisir le message à envoyer :\n");
	char msg[MAX_MSG];
	memset(msg, 0, sizeof msg);
	fgets(msg, 1024, stdin);
	*strchr(msg, '\n') = '\0';
	_DEBUG("message saisi", msg);

	if (sendto(sockfd, msg, strlen(msg), 0, server_info->ai_addr, server_info->ai_addrlen) == -1)
	{
		_DEBUG("send()", "Erreur d'envoi des données vers le serveur");
		close(sockfd);
		exit(ERR_SEND);
	}
	else _DEBUG("send()", "Données envoyées vers le serveur avec succès");

	_DEBUG("recvfrom()", "Attente de réception des données du serveur");
	memset(msg, 0, sizeof msg);

	if (recvfrom(sockfd,msg,1024,0,server_info->ai_addr,&server_info->ai_addrlen) == -1)
	{
		_DEBUG("redvfrom()", "Erreur de réception des données");
		_DEBUG("close()", "Fermeture de la socket");
		close(sockfd);
	}
	else
	{
		_DEBUG("recvfrom()", "Données reçues");
		fprintf(stdout, "Message reçu : %s\n", msg);
	}

	_DEBUG("close()", "Fermeture de la socket");
	close(sockfd);

	return EXIT_SUCCESS;
}
