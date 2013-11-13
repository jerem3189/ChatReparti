/*
 * File:   Client.hpp
 * Author: Arnaud
 *
 * Created on 28 octobre 2013, 18:56
 */

#ifndef CLIENT_HPP
#define	CLIENT_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

#include <vector>
#include <string>
#include "../../Server/src/ErrorCodes.hpp"

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct addrinfo ADDRINFO;

class Socket;

class Client {
public:
    Client();
    Client(string name);
    virtual ~Client();
    string getName();
    void setName(string newName);
    bool isMaster();
    void setMaster(bool type);
    SOCKADDR_IN *getSockAddr();

    SOCK_ERROR_ENUM addNetworkHints(SOCKADDR_IN *addr_in);
    bool operator==(Client & client);
    void setLastalive(time_t lastalive);
    time_t getLastalive() const;
private:
    string name;
    time_t lastalive;
    SOCKADDR_IN addr_in;
};

#endif	/* CLIENT_HPP */

