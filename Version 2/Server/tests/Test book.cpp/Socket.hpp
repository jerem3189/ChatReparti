/** \file Socket.hpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */
using namespace std;

#if !defined(_SOCKET_H)
#define _SOCKET_H

#include <string>


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
