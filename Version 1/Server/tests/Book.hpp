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
#include "Room.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>


class Book {
public:
    Book();
    Book(const Book& orig);
    virtual ~Book();
    int addNewClient(string name, vector<string> roomList);
    int removeClient(string name);
    int addClientToRoom(string clientName, string roomName);
    int removeClientFromRoom(string clientName, string roomName);
    int changeClientName(string name, string newName);
    int changeClientNamev3(string name, string newName);
    Client findClient(string name);
    Client findClientv3(string name);
    map<Client, vector<Room> > getClients();
    void setClients(map<Client, vector<Room*> > clients);
    //void setClients(vector< pair<Client, vector<Room*> > >clients);
    vector<Client> getRoomClients(string roomName);
    vector<Client> getGroupClients(string groupName);
    vector<Room> getRooms();
    int addRoom(string name);
    int addNetworkHints(string nameClient, string ipAddress, int port);
private:
    vector<pair<Client, vector<Room*> > > clients;
    vector<Room> rooms;
};

#endif  //_BOOK_H
