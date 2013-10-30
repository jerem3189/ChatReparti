/* 
 * File:   Book.cpp
 * Author: darkey
 * 
 * Created on 28 octobre 2013, 19:22
 */
using namespace std;
#include "Book.hpp"
#include "Client.hpp"

#include <utility>

Book::Book() {
}

Book::~Book() {
}

int Book::addNewClient(string name, vector<string> roomList) {	
	Client client = Client(name); // Creation de l'objet Client a partir de son nom
	
	for (vector<string>::iterator i = roomList.begin(); i != roomList.end(); ++i)
	{
		vector<Room>::iterator it;
		
		bool result = false;
		for(it = this->rooms.begin(); it != this->rooms.end(); ++it)
		{
			if(it->getName() == *i)
			{
				result = true;
				it->addClient(&client);
				cout << "La room existe et le client a été ajouté" << endl;
				break;
			}
		}
	}
	
	this->clients.push_back(client);
	
	return 0;
}

int Book::removeClient(string name) {
	vector<Client>::iterator it;
		for(it = this->clients.begin(); it != this->clients.end(); ++it)
		{
			if(it->getName() == name)
			{
				cout << "Client trouvé !!!" << endl;
				this->clients.erase(it);
				cout << "Client supprimé !!!" << endl;
				break;
			}
		}
		
		return 0;
}

int Book::addClientToRoom(string clientName, string roomName) {
	Room *room = findRoom(roomName);
	Client *client = findClient(clientName);
	
	room->addClient(client);
}

int Book::removeClientFromRoom(string clientName, string roomName) {

}

int Book::changeClientName(string name, string newName) {

}

Client* Book::findClient(string name) {
		vector<Client>::iterator it;
		for(it = this->clients.begin(); it != this->clients.end(); ++it)
		{
			cout << "nom : " << it->getName() << endl;
			if(it->getName() == name)
			{
				cout << "Client trouvé !!!" << endl;
				return &(*it);
			}
		}
		
		return NULL;
}

Room* Book::findRoom(string name) {
		vector<Room>::iterator it;
		for(it = this->rooms.begin(); it != this->rooms.end(); ++it)
		{
			cout << "nom : " << it->getName() << endl;
			if(it->getName() == name)
			{
				cout << "room trouvée !!!" << endl;
				return &(*it);
			}
		}
		
		return NULL;
}

vector<Client> Book::getClients() {
	return this->clients;
}

void Book::setClients(vector<Client> clients) {

}

vector<Client> Book::getRoomClients(string roomName) {

}

vector<Room> Book::getRooms() {
	return this->rooms;
}

int Book::addRoom(string name) {
	Room room = Room(name);
	this->rooms.push_back(room);
}

int Book::addNetworkHints(string nameClient, string ipAddress, int port) {

}
