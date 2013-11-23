/*
 * File:   Client.cpp
 * Author: Arnaud
 *
 *
 */
using namespace std;
#include "Client.hpp"
#include "Socket.hpp"

#include <stdio.h>
#include <string.h>


Client::Client() {
}

Client::Client(const Client &client) : name(client.name), addr_in(client.addr_in), lastalive(client.lastalive)
{

}
/**
 * constructeur de client à partir de son nom
 * @param name le nom du client a creer
 */
Client::Client(string name) {
    this->name = name;
}

Client::~Client() {
}
/**
 * getter du nom d'un client
 * @return name le nom du client
 */
string Client::getName() {
    return this->name;
}
/**
 * setter du nom d'un client
 * @param newName le nouveau nom attribué
 */
void Client::setName(string newName) {
    name=newName;
}

bool Client::isMaster() {

}

void Client::setMaster(bool type) {

}

SOCKADDR_IN *Client::getSockAddr()
{
    return &this->addr_in;
}

bool Client::operator==(Client & client)
{
    if (this->getName() == client.getName())
        return true;

    return false;
}

void Client::setLastalive(time_t lastalive) {
    this->lastalive = lastalive;
}

time_t Client::getLastalive() const {
    return lastalive;
}

SOCK_ERROR_ENUM Client::addNetworkHints(SOCKADDR_IN *addr_in)
{
    void * retour = memcpy(&this->addr_in, addr_in, sizeof(*addr_in));

    if (retour == NULL)
        return NETWORK_HINTS_NOK;

    return NETWORK_HINTS_OK;
}
