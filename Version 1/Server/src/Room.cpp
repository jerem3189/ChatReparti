/*
* prout file
*
*
*
*
*/
using namespace std;
#include "Room.hpp"
#include "Client.hpp"

 string name;
 vector<Client> clients;

int Room::addClient(Client client) {
    clients.insert(clients.end(),client);
     
}

int Room::delClient(Client client) {
    std::vector<int>::iterator it;

  // iterator pour trouver l'element correspondant au client
  it = find (clients.begin(), clients.end(), client);
    clients.erase(it);

}

string Room::getName() {
    return this->name;

}

void Room::setName(string newName) {
    this->name=newName;
}

vector<Client> Room::getClients() {
    return this->clients;
    
}

void Room::setClients(vector<Client> clients) {
    this->clients = clients;
}

