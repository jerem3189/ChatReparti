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

    SOCK_ERROR_ENUM retour = client->addNetworkHints(addr_in);

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
BOOK_ERROR_ENUM Book::removeClient(string name) {
    Client *client = findClient(name);
    bool success = false;

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
            success = true;
            break;
        }
    }

    if (!success)
        return CLIENT_DEL_NOK;

    return CLIENT_DEL_OK;
}
/**
 * ajout d'un client à un salon
 * @param clientName le nom du client
 * @param roomName le nom du salon
 * @return 0
 */
BOOK_ERROR_ENUM Book::addClientToRoom(string clientName, string roomName) {
    Room *room = findRoom(roomName);
    Client *client = findClient(clientName);

    if (client == NULL)
        return ERR_UNKNOWN_CLIENT;

    if (room == NULL)
        return ERR_UNKNOWN_ROOM;

    room->addClient(client);

    return CLIENT_ADD_TO_ROOM_OK;
}
/**
 * retire un client d'un salon
 * @param clientName le nom du client
 * @param roomName le nom du salon
 * @return 0
 */
BOOK_ERROR_ENUM Book::removeClientFromRoom(string clientName, string roomName) {
    Client *client = findClient(clientName);
    Room *room = findRoom(roomName);

    if (room == NULL)
    {
        return ERR_REMOVE_CLIENT_FROM_ROOM;
    }

    room->delClient(client);

    return REMOVE_CLIENT_FROM_ROOM_OK;
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
 * renvoi les clients d'un salon
 * @param roomName le nom du salon
 * @return les clients (pointeurs) présent dans un salon
 */
vector<Client*> Book::getRoomClients(string roomName) {
    Room *room = findRoom(roomName);

    return room->getClients();
}
/**
 * retourne la liste de salons de l'annuaire
 * @return un vector de salons
 */
vector<Room> Book::getRooms() {
    return this->rooms;
}
/**
 * Ajoute un salon à l'annuaire
 * @param name le nom d'un salon a ajouter à l'annuaire
 * @return 0
 */
int Book::addRoom(string name) {
    Room room = Room(name);
    this->rooms.push_back(room);
    cout << "Book::addRoom() -> le salon " << name << " a été ajouté à l'annuaire" << endl;

    return 0;
}
/**
 * retourne le nombre de salons d'un client
 * @param clientName le nom d'un client
 * @return le nombre de salons d'un client
 */
int Book::nbClientRooms(string clientName)
{
    vector<Room*> roomList = this->getClientRooms(clientName);

    int nb = roomList.size();

    return nb;
}
/**
 * retourne un tableau de pointeurs sur les salons d'un client
 * @param clientName le nom du client
 * @return vector_roomList un vector de pointeur sur les salons d'un client
 */
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
