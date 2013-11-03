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
#include "../../Server/src/ErrorCodes.hpp"

Book::Book() {
    Room room("global");

    this->rooms.push_back(room);
}

Book::~Book() {
}

BOOK_ERROR_ENUM Book::addNewClient(string name,string addressIp, string port) {
    Client *client = new Client(name); // Creation de l'objet Client a partir de son nom

    //SOCK_ERROR_ENUM retour = client->addNetworkHints(addressIp,port);

    //if (retour != NETWORK_HINTS_OK)
    //    return CLIENT_ADD_NOK;

    this->rooms.at(0).addClient(client);
    this->clients.push_back(*client);

    return CLIENT_ADD_OK;
}

BOOK_ERROR_ENUM Book::addNewClient(string name,string addressIp, string port, vector<string> roomList) {
    /*Client client = Client(name); // Creation de l'objet Client a partir de son nom
    int test = -1;

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
                test++;

                SOCK_ERROR_ENUM retour = client.addNetworkHints(addressIp,port);

                if (retour != NETWORK_HINTS_OK)
                {
                    it->delClient(&client);
                    return CLIENT_ADD_NOK;
                }

                cout << "Book::addNewClient() -> La room existe et le client a été ajouté" << endl;
                break;
            }
        }
    }

    if (test < 0)
    {
        this->rooms.at(0).addClient(&client);
        this->clients.push_back(client);
        return CLIENT_ADD_OK;
    }
    else
        this->clients.push_back(client);
        */

    return CLIENT_ADD_OK;
}

int Book::removeClient(string name) {
    Client *client = findClient(name);

    vector<Client>::iterator it;
    for(it = this->clients.begin(); it != this->clients.end(); ++it)
    {
        if(it->getName() == name)
        {
            cout << "Book::removeClient() -> Client trouvé !" << endl;
            vector<Room*> roomList = this->getClientRooms(name);
            vector<Room*>::iterator it2;
            // supprimer le client de chaque room dans lequel il est
            for(it2 = roomList.begin(); it2 != roomList.end(); ++it2)
            {
                (*it2)->delClient(client);
            }
            this->clients.erase(it);
            cout << "Book::removeClient() -> Client supprimé !!!" << endl;
            break;
        }
    }

    return 0;
}

int Book::addClientToRoom(string clientName, string roomName) {
    Room *room = findRoom(roomName);
    Client *client = findClient(clientName);

    room->addClient(client);

    return 0;
}

int Book::removeClientFromRoom(string clientName, string roomName) {
    Client *client = findClient(clientName);
    Room *room = findRoom(roomName);

    room->delClient(client);

    return 0;
}

int Book::changeClientName(string name, string newName) {
    //A CODER MAIS PAS IMPORTANT
    return 0;
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
    this->clients = clients;
}

vector<Client*> Book::getRoomClients(string roomName) {
    Room *room = findRoom(roomName);

    return room->getClients();
}

vector<Room> Book::getRooms() {
    return this->rooms;
}

int Book::addRoom(string name) {
    Room room = Room(name);
    this->rooms.push_back(room);
    cout << "Book::addRoom() -> le salon " << name << " a été ajouté à l'annuaire" << endl;

    return 0;
}

int Book::nbClientRooms(string clientName)
{
    vector<Room*> roomList = this->getClientRooms(clientName);

    int nb = roomList.size();

    return nb;
}

vector<Room*> Book::getClientRooms(string clientName) {
    vector<Room*> vector_roomList;
    //cout << "test1" << endl;

    vector<Room>::iterator it;
    //cout << "test1" << endl;
    for(it = this->rooms.begin(); it != this->rooms.end(); ++it)
    {
        //cout << "test2" << endl;
        //vector<Client*>::iterator it2;
        //cout << "test2" << endl;
        /*
        for(it2 = it->getClients().begin(); it2 != it->getClients().end(); ++it2)
        {
            cout << "test3" << endl;
            cout << "Nombre de clients dans la room " << it->getName() << " : " << it->getClients().size() << endl;
            Client *client = *it2;
            cout << "nom du client" << client->getName() << endl;
            if ((*it2)->getName() == clientName)
            {
                vector_roomList.push_back(&(*it));
                break;
            }
        }
        */

        for(int i=0; i<it->getClients().size(); i++)
        {
            if (it->getClients().at(i)->getName() == clientName)
            {
                Room *room = &(*it);
                vector_roomList.push_back(room);
                break;
            }
        }

    }

    return vector_roomList;
}
