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
#include <sys/unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <string.h>
using namespace std;

class NetworkUDP {
public:
    static int sendDatagrams(SOCKET sock, char *data, size_t len, SOCKADDR *address, ADDRINFO *infos);
    static int receiveDatagrams(SOCKET sock, char *data, size_t maxLen, SOCKADDR *address, ADDRINFO *infos);
    static bool compareSockaddr(sockaddr_in const &a, sockaddr_in const &b) {
        if ((a.sin_addr.s_addr == b.sin_addr.s_addr) && (a.sin_port == b.sin_port)) {
           return true;
        }
        return false;
    }
    static string getIp_static();
    static string getIp_interface(string interface);
};

#endif  //_SENDINGUDP_H
