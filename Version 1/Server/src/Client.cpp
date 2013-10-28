/* 
 * File:   Client.cpp
 * Author: Arnaud
 * 
 * 
 */
using namespace std;
#include "Client.hpp"

string name;

Socket sock;
    

Client::Client() {
}

Client::Client(const Client& orig) {
}

Client::~Client() {
}

Client::getName() {
    return name;
}

Client::setName(string newName) {
    name=newName;
    
}

