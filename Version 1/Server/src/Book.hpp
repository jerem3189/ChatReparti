/*
 * File:   Book.hpp
 * Author: darkey
 *
 * Created on 28 octobre 2013, 19:22
 */
using namespace std;

#if !defined(_BOOK_HPP)
#define _BOOK_HPP

#include "Room.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>

class Client;

class Book {
public:
    Book();
    virtual ~Book();
    int addNewClient(string name,string addressIp,string port, vector<string> roomList);
    int removeClient(string name);
    int addClientToRoom(string clientName, string roomName);
    int removeClientFromRoom(string clientName, string roomName);
    int changeClientName(string name, string newName);
    Client* findClient(string name);
    //vector<Client*>::iterator findClient(string name);
    Room* findRoom(string name);
    vector<Client> getClients();
    void setClients(vector<Client> clients);
    vector<Client*> getRoomClients(string roomName);
    vector<Room*> getClientRooms(string clientName);
    vector<Room> getRooms();
    int addRoom(string name);
    int addNetworkHints(string nameClient, string ipAddress, string port);
    int nbClientRooms(string clientName);
private:
    vector<Client> clients;
    vector<Room> rooms;
};

#endif  //_BOOK_H
