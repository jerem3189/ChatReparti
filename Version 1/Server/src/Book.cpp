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

Book::Book(const Book& orig) {
}

Book::~Book() {
}

int Book::addNewClient(string name, vector<string> roomList) {
	/*    TEST TEST TEST TEST TEST
	Client client1 = Client(name);
	vector<Room> liste_de_rooms;
	Room room1 = Room();
	Room room2 = Room();
	liste_de_rooms.insert(liste_de_rooms.begin(), room1);
	liste_de_rooms.insert(liste_de_rooms.begin(), room2);
	
	vector<Room*> liste_de_rooms_etoile;
	liste_de_rooms_etoile.insert(liste_de_rooms_etoile.begin(), &liste_de_rooms.at(0));
	//this->clients[client1] = liste_de_rooms_etoile;
	//this->clients[client1] = toto;
	pair<Client,vector<Room*> > paire;
	paire = make_pair(client1, liste_de_rooms_etoile);
	this->clients.insert(this->clients.begin(), paire);
	FIN TEST FIN TEST FIN TEST*/
	
	
	Client client = Client(name); // Creation de l'objet Client a partir de son nom
	vector<Room*> vector_room_list; // Vecteur de Room*
	for (vector<string>::iterator i = roomList.begin(); i != roomList.end(); ++i)
	{
		//SI *i existe dans la liste de room actuelle
		//ALORS rajouter dans le vector_room_list un pointeur vers cette  room
		cout << "Boucle for" << endl;
	}
	
	pair<Client,vector<Room*> > pair_client_roomList;
	pair_client_roomList = make_pair(client, vector_room_list);
	this->clients.insert(this->clients.begin(), pair_client_roomList);
	
	return 0;
}

int Book::removeClient(string name) {

}

int Book::addClientToRoom(string clientName, string roomName) {

}

int Book::removeClientFromRoom(string clientName, string roomName) {

}

int Book::changeClientName(string name, string newName) {

}

Client Book::findClient(string name) {

}

map<Client, vector<Room> > Book::getClients() {

}

void Book::setClients(map<Client, vector<Room*> > clients) {

}

vector<Client> Book::getRoomClients(string roomName) {

}

vector<Room> Book::getRooms() {

}

int Book::addRoom(string name) {

}

int Book::addNetworkHints(string nameClient, string ipAddress, int port) {

}
