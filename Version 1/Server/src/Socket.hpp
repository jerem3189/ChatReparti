/** \file Socket.hpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */
using namespace std;

#if !defined(_SOCKET_H)
#define _SOCKET_H

#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <ioctl.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

class Socketdef {
public:

	Socket();
	Socket(unsigned short port);
	~Socket();
	
	char message[1024], listenPort[6];
	
	int connect(unsigned short = 0);
	int create(unsigned short = 0);
	int listen();
	
	sockaddr_in	get_read_addr();
	
	void	terminate();
	
	
private:
	string ipAddress;
	int port;
	bool		m_connect;
	SOCKET		m_sock;
	sockaddr_in	m_readaddr;
	sockaddr_in	m_writeaddr;
	
};

class cSocket {
	Socketdef cSocket;
};

#endif  //_SOCKET_H
