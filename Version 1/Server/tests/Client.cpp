/* 
 * File:   Client.cpp
 * Author: Arnaud
 * 
 * 
 */
using namespace std;
#include "Client.hpp"
#include "Socket.hpp"
string name;

Socket sock;
    
Client::Client() {
}

Client::Client(string name) {
	this->name = name;
}

Client::Client(const Client& orig) {
}

Client::~Client() {
}

string Client::getName() {
    return name;

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
