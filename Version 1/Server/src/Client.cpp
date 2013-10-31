/* 
 * File:   Client.cpp
 * Author: Arnaud
 * 
 * 
 */
using namespace std;
#include "Client.hpp"
    
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

bool Client::operator==(Client & client)
{
	if (this->getName() == client.getName())
		return true;
	
	return false;
}

int Client::addNetworkHints(string addressIp, string port)
{


    return 0;
}
