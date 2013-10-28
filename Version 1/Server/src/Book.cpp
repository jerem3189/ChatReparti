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


int Book::addNewClient(string name, int Vector<&Room> = null) {

}

int Book::addNewClientv3(string name, int Vector<&Group> = null) {

}

int Book::removeClient(string name) {

}

int Book::addClientToRoom(string clientName, string roomName) {

}

int Book::addClientToGroup(Client client) {

}

int Book::removeClientFromRoom(string clientName, string roomName) {

}

int Book::removeClientFromGroup(Client client) {

}

int Book::changeClientName(string name, string newName) {

}

int Book::changeClientNamev3(string name, string newName) {

}

Client Book::findClient(string name) {

}

Client Book::findClientv3(string name) {

}

map<Client, vector<Room>> Book::getClients() {

}

map<&Group, Client> Book::getClientsv3() {

}

void Book::setClients(map<Client clients, int vector<&Room>>) {

}

void Book::setClientsv3(map<&Group clients, int Client>) {

}

vector<Client> Book::getRoomClients(string roomName) {

}

vector<Client> Book::getGroupClients(string groupName) {

}

map<&Group, Client> Book::getClientsv3() {

}

vector<Room> Book::getRooms() {

}

vector<Group> Book::getGroups() {

}

int Book::addRoom(string name) {

}

int Book::addGroup(int numero = -1) {

}

int Book::addNetworkHints(string nameClient, string ipAddress, int port) {

}