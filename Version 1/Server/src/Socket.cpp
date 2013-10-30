/** \file Socket.cpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#include "Socket.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int Socket::listen() {

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

