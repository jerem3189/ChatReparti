/* 
 * File:   Book.hpp
 * Author: darkey
 *
 * Created on 28 octobre 2013, 19:22
 */
using namespace std;

#if !defined(_BOOK_HPP)
#define _BOOK_HPP

#include "Client.hpp"

class Book {
public:
        Book();
        Book(const Book& orig);
        virtual ~Book();
	int addNewClient(string name, int vector<&Room> = null);
	int addNewClientv3(string name, int vector<&Group> = null);
	int removeClient(string name);
	int addClientToRoom(string clientName, string roomName);
	int addClientToGroup(Client client);
	int removeClientFromRoom(string clientName, string roomName);
	int removeClientFromGroup(Client client);
	int changeClientName(string name, string newName);
	int changeClientNamev3(string name, string newName);
	Client findClient(string name);
	Client findClientv3(string name);
	map<Client, vector<Room>> getClients();
	map<&Group, Client> getClientsv3();
	void setClients(map<Client clients, int vector<&Room>>);
	void setClientsv3(map<&Group clients, int Client>);
	vector<Client> getRoomClients(string roomName);
	vector<Client> getGroupClients(string groupName);
	map<&Group, Client> getClientsv3();
	vector<Room> getRooms();
	vector<Group> getGroups();
	int addRoom(string name);
	int addGroup(int numero = -1);
	int addNetworkHints(string nameClient, string ipAddress, int port);
private:
	map<Client, vector<&Room>> clients;
	map<&Group, Client> clientsv3;
	vector<Room> rooms;
	vector<Group> groups;
};

#endif  //_BOOK_H