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
    BOOK_ERROR_ENUM addNewClient(string name,string addressIp,string port, vector<string> roomList);
    BOOK_ERROR_ENUM addNewClient(string name, string addressIp, string port);
    BOOK_ERROR_ENUM addNewClient(string name, SOCKADDR_IN *addr_in);
    BOOK_ERROR_ENUM removeClient(string name);
    BOOK_ERROR_ENUM addClientToRoom(string clientName, string roomName);
    BOOK_ERROR_ENUM removeClientFromRoom(string clientName, string roomName);
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
    int nbClientRooms(string clientName);
private:
    vector<Client> clients;
    vector<Room> rooms;
};

#endif  //_BOOK_H
