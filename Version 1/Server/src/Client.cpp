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

SOCKADDR_IN *Client::getSockAddr()
{
    return this->addr_in;
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
    this->addr_in = addr_in;

    return NETWORK_HINTS_OK;
}
