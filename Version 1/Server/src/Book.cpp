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
/**
 * Constructeur par défaut de l'annuaire
 * créé un salon global
 */
Book::Book() {
    Room room("global");

    this->rooms.push_back(room);
}

Book::~Book() {
}
/** ajoute un client à l'annuaire
 *  
 * @param name le nom du client a ajouter
 * @param addr_in le socket du client
 * @return un numéro d'erreur d'ajout à l'annuaire 
 */
BOOK_ERROR_ENUM Book::addNewClient(string name, SOCKADDR_IN *addr_in) {
    Client *client = new Client(name); // Creation de l'objet Client a partir de son nom
    //Client client(name);

    SOCK_ERROR_ENUM retour = client->addNetworkHints(addr_in);
    //SOCK_ERROR_ENUM retour = client.addNetworkHints(addr_in);

    if (retour != NETWORK_HINTS_OK)
        return CLIENT_ADD_NOK;

    this->rooms.at(0).addClient(client);
    this->clients.push_back(*client);

    return CLIENT_ADD_OK;
}
/**
 * Ajoute un client à l'annuaire
 * @param name le nom du client à ajouter
 * @param addressIp son adresse IP
 * @param port son port d'écoute
 * @param roomList sa liste de salon
 * @return un numéro d'erreur d'ajout à l'annuaire
 */
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
/**
 * retire un client de l'annuaire
 * @param name le nom du client à retirer
 * @return 0
 */
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
/**
 * ajout d'un client à un salon
 * @param clientName le nom du client 
 * @param roomName le nom du salon
 * @return 0 
 */
int Book::addClientToRoom(string clientName, string roomName) {
    Room *room = findRoom(roomName);
    Client *client = findClient(clientName);

    room->addClient(client);

    return 0;
}
/**
 * retire un client d'un salon
 * @param clientName le nom du client
 * @param roomName le nom du salon
 * @return 0
 */
int Book::removeClientFromRoom(string clientName, string roomName) {
    Client *client = findClient(clientName);
    Room *room = findRoom(roomName);

    room->delClient(client);

    return 0;
}

/**
 * change le nom d'un client
 * @param name le nom actuel du client
 * @param newName son nouveau nom
 * @return 0
 */
int Book::changeClientName(string name, string newName) {
    //A CODER MAIS PAS IMPORTANT
    return 0;
}

/**
 * cherche un client dans l'annuaire
 * @param name le nom du cient à chercher
 * @return un pointeur vers le client trouvé
 * @return NULL si aucun client correspond au nom recherché
 */
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
/**
 * cherche un salon dans l'annuaire
 * @param name le nom du salon à chercher
 * @return un pointeur vers le salon trouvé
 * @return NULL si aucun salon trouvé avec le nom donné
 */
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
/**
 * renvoie la liste des clients presents dans l'annuaire
 * @return un vector des clients de l'annuaire
 */
vector<Client> Book::getClients() {
    return this->clients;
}
/**charge dans l'annuaire une liste de clients
 * @param clients le vector de client a charger dans l'annuaire
 */
void Book::setClients(vector<Client> clients) {
    this->clients = clients;
}
/**
 * 
 * @param roomName 
 * @return 
 */
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
    vector<Room>::iterator it;

    string tempName = "";

    for(it = this->rooms.begin(); it != this->rooms.end(); ++it)
    {
        for(int i=0; i<it->getClients().size(); i++)
        {
            cout << "avant tempName " << endl;
            tempName = it->getClients().at(i)->getName();
            cout << "tempName :  " << tempName << endl;
            if (tempName == clientName)
            {
                cout << "proutiproutproutiprout" << endl;
                Room *room = &(*it);
                cout << "proutidazfazfgazfazf" << endl;
                vector_roomList.push_back(room);
                cout << "proutgeeeeeeegggggggggggggr" << endl;
                break;
            }
        }
    }
    cout << "YAAAAAAAAAAAA" << endl;

    cout << "TAILLE DE LA ROOMLIST" << vector_roomList.size() << endl;
    cout << "element at (1) [" << vector_roomList.at(0)->getName() << "]" << endl;

    return vector_roomList;
}
