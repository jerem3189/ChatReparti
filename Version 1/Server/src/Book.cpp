/* 
 * File:   Book.cpp
 * Author: darkey
 * 
 * Created on 28 octobre 2013, 19:22
 */
using namespace std;
#include "Book.hpp"
#include "Client.hpp"
Book::Book() {
}

Book::Book(const Book& orig) {
}

Book::~Book() {
}


int Book::addNewClient(string name, vector<Room*> roomList) {

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

//void Book::setClients(map<Client client, vector<Room*> roomList> clients) {

//}

vector<Client> Book::getRoomClients(string roomName) {

}

vector<Room> Book::getRooms() {

}

int Book::addRoom(string name) {

}

int Book::addNetworkHints(string nameClient, string ipAddress, int port) {

}
