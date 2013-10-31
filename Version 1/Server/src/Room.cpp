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


int Room::addClient(Client *client) {
    cout << "Room::addClient() -> Ajout du client " << client->getName() << " dans la room " << this->getName() << "." << endl;
    this->clients.push_back(client);
    
    return 1;
}

int Room::delClient(Client *client) {
   vector<Client*>::iterator it = this->findClient(client->getName());
   if (it == this->clients.end())
   {
	   cout << "Room::delClient() -> Le client n'a pas été trouvé." << endl;
	   return -1;
   }
   
	cout << "Room::delClient() -> Le client a été trouvé." << endl;
	this->clients.erase(it);
	cout << "Room::delClient() -> Le client a été supprimé." << endl;
   
   return 0;
}

string Room::getName() {
    return this->name;
}

void Room::setName(string name) {
    this->name=name;
}

vector<Client*> Room::getClients() {
    return this->clients;
}

void Room::setClients(vector<Client*> clients) {
    this->clients = clients;
}

/*
Client* Room::findClient(string name) {
		vector<Client*>::iterator it;
		for(it = this->clients.begin(); it != this->clients.end(); ++it)
		{
			if((*it)->getName() == name)
			{
				cout << "Client trouvé !!!" << endl;
				return &(*it);
			}
		}
		
		return NULL;
}*/

vector<Client*>::iterator Room::findClient(string name) {
		vector<Client*>::iterator it;
		for(it = this->clients.begin(); it != this->clients.end(); ++it)
		{
			if((*it)->getName() == name)
			{
				cout << "Room::findClient() -> Client trouvé." << endl;
				return it;
			}
		}
		
		return it;
}
