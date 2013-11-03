#include "Socket.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


Socket::Socket() {
    this->initialized = false;

    memset(&this->hints, 0, sizeof this->hints);
    this->hints.ai_family = AF_INET; /* IPV4 ou V6 */
    this->hints.ai_socktype = SOCK_DGRAM; /* Mode Datagramme */
    //this->hints.ai_flags = AI_PASSIVE;
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
        cout << "retour de getaddrinfo" << gai_strerror(ret) << endl;
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


void Socket::terminate() {
    close(this->sock);
}

SOCKADDR *Socket::getSockaddr() {
    return this->server_info->ai_addr;
}

ADDRINFO *Socket::getAddrinfo()
{
    return this->server_info;
}

SOCKET Socket::getSocket() {
    return this->sock;
}

/*
bool Socket::setPort(u_short port)
{
	this->address.sin_port	= ntohs(port);

	return true;
}

bool Socket::setAddress(const char * szAddress)
{

    return true;
}

int Socket::getPort(){
	return 1;
}

bool Socket::getAddressIp()
{
	 cout << inet_ntoa(this->address.sin_addr);

	 return true;
}

sockaddr_in Socket::getAddress()
{
	 return this->address;
}
*/
