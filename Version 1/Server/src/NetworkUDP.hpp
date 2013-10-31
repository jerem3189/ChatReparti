/** \file SendingUDP.hpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_SENDINGUDP_H)
#define _SENDINGUDP_H

#include "Thread.hpp"
#include "Socket.hpp"

class NetworkUDP {
public:
    int sendDatagrams(SOCKET sock, char *data, size_t len, SOCKADDR *address);
    int receiveDatagrams(SOCKET sock, char *data, size_t maxLen, SOCKADDR *address);
};

#endif  //_SENDINGUDP_H