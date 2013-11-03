#include "Socket.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sstream>

#include "../../Server/src/NetworkUDP.hpp"


Socket::Socket() {
    this->initialized = false;

    memset(&this->hints, 0, sizeof this->hints);
    this->hints.ai_family = AF_INET; /* IPV4 ou V6 */
    this->hints.ai_socktype = SOCK_DGRAM; /* Mode Datagramme */
    this->hints.ai_flags = AI_PASSIVE;
}

Socket::~Socket() {
    close(this->sock);
}

SOCK_ERROR_ENUM Socket::create(string addressIp, string port) {
    int ret = 0;

    if(addressIp == "NULL")
        ret = getaddrinfo(NULL, port.c_str(), &this->hints, &this->server_info);
    else
        ret = getaddrinfo(addressIp.c_str(), port.c_str(), &this->hints, &this->server_info);

    if (ret != 0)
    {
        cout << "Socket::create() -> Erreur lors de la récupération des informations du serveur" << endl;
        cout << "Socket::create() -> Retour de getaddrinfo : " << gai_strerror(ret) << endl;
        return ERR_SOCK_HINTS;
    }

    this->sock = socket(this->server_info->ai_family, this->server_info->ai_socktype, this->server_info->ai_protocol);

    if (this->sock == -1)
    {
        cout << "Socket::create() -> Erreur lors de la création de la socket" << endl;
        return ERR_SOCK_CREATE;
    }

    this->initialized = true;
    this->addressIp = addressIp;
    this->port = port;

    cout << "Socket::create() -> Socket creation OK" << endl;

    return SOCK_OK;
}

SOCK_ERROR_ENUM Socket::binding() {
    if (bind(this->sock, this->server_info->ai_addr, this->server_info->ai_addrlen) == -1)
    {
        cout << "Socket::bind() -> Erreur lors du bind" << endl;
        return SOCK_BIND_NOK;
    }
    else
    {
        cout << "Socket::bind() -> Bind des informations reseau ok" << endl;
    }

    return SOCK_BIND_OK;
}

void Socket::setIpPort(string addressIp, string port)
{
    this->addressIp = addressIp;
    this->port = port;
}


void Socket::terminate() {
    close(this->sock);
}

SOCKADDR *Socket::getSockaddr() {
    if (this->initialized)
        return this->server_info->ai_addr;

    return this->sockaddr;
}

ADDRINFO *Socket::getAddrinfo()
{
    return this->server_info;
}

SOCKET Socket::getSocket() {
    return this->sock;
}

string Socket::getPort()
{
    return this->port;
}

string Socket::getAddressIp()
{
    return this->addressIp;
}
