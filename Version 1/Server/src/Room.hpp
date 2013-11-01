/*
* prout file
*
*
*
*
*/

#if !defined(_ROOM_H)
#define _ROOM_H

#include "Client.hpp"
#include <iostream>
#include <vector>

class Room {
public:
    Room(string name) {
        this->name = name;
    }
    int addClient(Client *client);
    int delClient(Client *client);
    string getName();
    void setName(string name);
    vector<Client*> getClients();
    void setClients(vector<Client*> clients);
    vector<Client*>::iterator findClient(string name);
    //Client* findClient(string name);
private:
    string name;
    vector<Client*> clients;
};

#endif  //_ROOM_H
