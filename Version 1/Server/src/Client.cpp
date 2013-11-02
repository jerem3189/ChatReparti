/*
 * File:   Client.cpp
 * Author: Arnaud
 *
 *
 */
using namespace std;
#include "Client.hpp"
#include "Socket.hpp"


Client::Client() {
    this->socket = new Socket();
}

Client::Client(string name) {
    this->name = name;
}

Client::~Client() {
}

string Client::getName() {
    return this->name;
}
void Client::setName(string newName) {
    name=newName;
}

bool Client::isMaster() {

}

void Client::setMaster(bool type) {

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

SOCK_ERROR_ENUM Client::addNetworkHints(string addressIp, string port)
{
    SOCK_ERROR_ENUM retour;

    retour = this->socket->create(addressIp, port);

    if (retour != SOCK_OK)
        return retour;

    retour = this->socket->binding();

    if (retour != SOCK_BIND_OK)
        return retour;

    return NETWORK_HINTS_OK;
}
Socket* Client::getSocket(){
    return this->socket;
}
