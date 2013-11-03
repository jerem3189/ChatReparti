/*
 *
 *
 *
 */

#ifndef	_CUDPSOCKET_INCLUDED
#define	_CUDPSOCKET_INCLUDED

// ////////////////////////////
// Includes
//
// ////////////////////////////

/* System Includes */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

#include <iostream>
#include <string>
using namespace std;

#include "ErrorCodes.hpp"

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct addrinfo ADDRINFO;

class Socket
{
public:
    Socket();
    ~Socket();

    SOCKET getSocket();
    SOCKADDR *getSockaddr();
    ADDRINFO *getAddrinfo();
    string getAddressIp();
    string getPort();

    SOCK_ERROR_ENUM create(string adressIp, string port);
    SOCK_ERROR_ENUM binding();
    void setIpPort(string addressIp, string port);
    void terminate();

    //int getPort();
    //bool getAddressIp();
    //sockaddr_in getAddress();
    //bool	setPort(unsigned short nPortNumber);
    //bool	setAddress(const char * szAddress);

private:
    bool initialized;
    SOCKET sock;
    ADDRINFO hints;
    ADDRINFO *server_info;
    SOCKADDR *sockaddr;

    string addressIp;
    string port;

    //sockaddr_in	address;
};

#endif

