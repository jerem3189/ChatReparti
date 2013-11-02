/** \file SendingUDP.hpp
 * Description breve du fichier.
 * Description plus elaboree et detaillee du fichier.
 */

#if !defined(_SENDINGUDP_H)
#define _SENDINGUDP_H

#include "Thread.hpp"
#include "Socket.hpp"
#include <sys/types.h>
#include <ifaddrs.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class NetworkUDP {
public:
    int sendDatagrams(SOCKET sock, char *data, size_t len, SOCKADDR *address);
    int receiveDatagrams(SOCKET sock, char *data, size_t maxLen, SOCKADDR *address);
    int getIp_static();
    int getIp_interface();
};

#endif  //_SENDINGUDP_H
