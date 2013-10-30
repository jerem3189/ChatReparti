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
#include <vector>


 string roomName;
 vector<Client> clients;

int Room::addClient(Client client) {
    
    //clients.insert(clients.end(),it,client);
    return 1;
}

int Room::delClient(Client client) {
    vector<Client*>::iterator it;
    
   bool result = false;
   for(it = this->clients.begin(); it != this->clients.end(); ++it)
   {
	   if(*(*it) == client)
		result = true;
   }
   
   return 0;
}

string Room::getName() {
    return name;

}

void Room::setName(string newName) {
    roomName=newName;
}
/*
vector<Client> Room::getClients() {
    //return clients&;
    
}*/

void Room::setClients(vector<Client> newClients) {
    //clients = newClients;
}

