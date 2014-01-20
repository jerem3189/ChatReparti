/** \file Room.cpp
 *
 */
//using namespace std;
#include "Room.hpp"
#include "Client.hpp"
#include <vector>


Room::Room(const Room &room): name(room.name),clients(room.clients){
    
}

/**
 * Fonction d'ajout de client dans l'annuaire
 * @param *client informations sur le client
 */
int Room::addClient(Client *client) {
    cout << "Room::addClient() -> Ajout du client " << client->getName() << " dans la room " << this->getName() << "." << endl;
    this->clients.push_back(client);

    return ROOM_CLIENT_ADD_OK;
}

/**
 * Fonction de suppression de client dans l'annuaire
 * @param *client informations sur le client
 */
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
/**
 * getter du nom d'un client
 * @return name le nom du client
 */
string Room::getName() {
    return this->name;
}
/**
 * setter du nom d'un client
 * @param newName le nouveau nom attribué
 */
void Room::setName(string name) {
    this->name=name;
}
/**
 */
vector<Client*> Room::getClients() {
    return this->clients;
}
/**
 */
void Room::setClients(vector<Client*> clients) {
    this->clients = clients;
}

/**
 */
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
