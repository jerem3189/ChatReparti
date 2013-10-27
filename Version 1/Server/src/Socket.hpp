/** \file Socket.hpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_SOCKET_H)
#define _SOCKET_H


class Socket {
public:
	int listen();
	int connect();
	int create();
private:
	string ipAddress;
	int port;
};

#endif  //_SOCKET_H
